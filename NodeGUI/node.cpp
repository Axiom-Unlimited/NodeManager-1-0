#include "node.h"
#include "ui_node.h"
#include <iostream>
#include <UDPReceiver.h>
#include <cuda.h>
#include <cuda_runtime_api.h>
#include <cuda_runtime.h>
#include "opencv4/opencv2/imgproc.hpp"
#include "opencv4/opencv2/highgui.hpp"
#include "NvDecoder.h"
#include "NvCodecUtils.h"
#include "ColorSpace.h"
#include <QtEndian>
#include <QGraphicsPixmapItem>

Node::Node(int id, std::string ip, int baseport, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Node),
    id(id),
    ipAddress(ip),
    baseport(baseport)
{
    ui->setupUi(this);
    this->receiver = std::make_unique<UDPReceiver>(ip,id+baseport);
    this->ui->frameDisplay->setScene(new QGraphicsScene(this));

    connect(this->receiver.get(),&UDPReceiver::dataReady,this, &Node::dataReturn);

    try {

        this->_futureTask = std::async(std::launch::async | std::launch::deferred, &Node::decode, this);
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

Node::~Node()
{
    delete ui;
}

void Node::dataReturn(H264Packet packet)
{
    std::pair<unsigned long long, std::pair<unsigned long long, std::vector<unsigned char>>> dataPair(packet.timestamp, std::pair(packet.datasize,packet.pData));
    // lock the map so that no concurrent operations are done on it
    this->mtx.lock();
    this->frames.insert(dataPair);
    this->mtx.unlock();
}

void Node::decode()
{
    CUdevice device;
    CUcontext context;

    auto cret = cuInit(0);
    if (cret != cudaError_enum::CUDA_SUCCESS){ std::cout << "failed to initialize cuda device!" << std::endl; throw cret;}
    cret = cuDeviceGet(&device, 0);
    if (cret != cudaError_enum::CUDA_SUCCESS){ std::cout << "failed to get device!" << std::endl; throw cret;}
    cret = cuCtxCreate(&context,0, device);
    if (cret != cudaError_enum::CUDA_SUCCESS){ std::cout << "failed to create cuda context!" << std::endl; throw cret;}

    // initialize the nvDecoder
    std::cout << "creating decoder" << std::endl;
    NvDecoder decoder(context,640,480,true,cudaVideoCodec_H264,NULL,false,false);

    int  nFrameReturned = 0, nFrame = 0;
    uint8_t **ppFrame;
    int64_t timestamp;
    int64_t datasize;
    std::unique_ptr<uint8_t[]> pImage(new uint8_t[640*480*4]);
    CUdeviceptr pTmpImage = 0;
    cuMemAlloc(&pTmpImage, 640 * 480 * 4);

     auto width = ui->frameDisplay->width();
     auto height = ui->frameDisplay->height();

    while(this->receiver->isValid())
    {
        if(this->frames.size() < 30 ){continue;}
        // lock frames so that no concurrent operations can be done on it
        this->mtx.lock();
        auto packet = this->frames.begin();

        if(this->frames.begin()->first  == 0){continue;}
        timestamp = this->frames.begin()->first;
        datasize = this->frames.begin()->first;
        std::cout << "timestamp: " << timestamp << " datasize: " << datasize << std::endl;
        std::vector<unsigned char> data(this->frames.begin()->second.second);
//        std::cout << timestamp << std::endl;
//        std::cout << "payload #################################################################" << std::endl;
//        for (auto&& var : data)
//        {
//            std::cout << static_cast<int>(var) << std::endl;
//        }
//        std::cout << "#########################################################################" << std::endl;
        uint8_t * pVideo = reinterpret_cast<uint8_t *>(data.data());

        decoder.Decode(pVideo,datasize,&ppFrame,&nFrameReturned);
        this->frames.erase(this->frames.begin());
        this->mtx.unlock();

        if (nFrameReturned > 0)
        {
            auto tmp = decoder.GetVideoInfo();
            std::cout << tmp << std::endl;
            auto format = decoder.GetVideoFormatInfo();
            auto outputFormat = decoder.GetOutputFormat();
            std::cout << outputFormat << std::endl;
        }
        for (int i = 0; i < nFrameReturned; i++)
        {
            std::cout << 'frameDecoded' << std::endl;
            Nv12ToColor32<BGRA32>((uint8_t *)ppFrame[i], decoder.GetWidth(), (uint8_t*)pTmpImage, 4 * decoder.GetWidth(), decoder.GetWidth(), decoder.GetHeight());

            this->getImage(pTmpImage, reinterpret_cast<uint8_t*>(pImage.get()), 4 * decoder.GetWidth(), decoder.GetHeight());
            cv::Mat decFrame(480,640,CV_8UC4,reinterpret_cast<char*>(pImage.get()));
            cv::cvtColor(decFrame,decFrame,cv::COLOR_BGRA2RGB,CV_8UC3);
//            std::stringstream ss;
//            ss << "/media/mfigueroa/Data/outputs/";
//            ss << packet->first;
//            ss << ".png";
//            cv::imwrite(ss.str(),decFrame);
//            cv::imshow("test",decFrame);
//            cv::waitKey(1);
//            cv::resize(decFrame,decFrame,cv::Size(width,height));

//            QImage pixmap = QPixmap::fromImage(QImage((unsigned char*)decFrame.data,decFrame.cols,decFrame.rows,QImage::Format_RGBA8888));
//            QImage qimg(decFrame.data,decFrame.cols,decFrame.rows,decFrame.step,QImage::Format_RGB888);
//            QGraphicsPixmapItem pixmap;
//            pixmap.setPixmap(QPixmap::fromImage(qimg));
//            this->ui->frameDisplay->scene()->addItem(&pixmap);
//            this->ui->frameDisplay->fitInView(&pixmap,Qt::KeepAspectRatio);
        }

        nFrame += nFrameReturned;
    }

    free(ppFrame);
}

void Node::getImage(CUdeviceptr dpSrc, uint8_t *pDst, int nWidth, int nHeight)
{
    CUDA_MEMCPY2D m = { 0 };
    m.WidthInBytes = nWidth;
    m.Height = nHeight;
    m.srcMemoryType = CU_MEMORYTYPE_DEVICE;
    m.srcDevice = (CUdeviceptr)dpSrc;
    m.srcPitch = m.WidthInBytes;
    m.dstMemoryType = CU_MEMORYTYPE_HOST;
    m.dstDevice = (CUdeviceptr)(m.dstHost = pDst);
    m.dstPitch = m.WidthInBytes;
    cuMemcpy2D(&m);
}
