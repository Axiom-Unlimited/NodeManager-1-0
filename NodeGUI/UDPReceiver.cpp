#include <UDPReceiver.h>
#include <iostream>
#include <QNetworkDatagram>
#include <QByteArray>
#include <iostream>
#include <memory>
#include <QHostAddress>
#include <QString>
#include <QtEndian>
#include <algorithm>
#include <QDataStream>
#include <netinet/in.h>
#include <endian.h>


UDPReceiver::UDPReceiver(std::string address, const unsigned short port) : ipAddress(address), port(port)
{
    qRegisterMetaType<H264Packet>("H264Packet");
    QHostAddress qAddress(QString::fromStdString(this->ipAddress));
    this->socket = std::make_unique<QUdpSocket>(this);
    auto ret = this->socket->bind(qAddress, port);
    if(!ret)
    {
        std::cout << "failed to bind to socket" << std::endl;
        throw "failed to bind to socket";
    }

    if( !this->run())
    {
        std::cout << "failed to start data accuisition thread" << std::endl;
    }
}


bool UDPReceiver::run()
{
    try {

        this->_futureTask = std::async(std::launch::async | std::launch::deferred, &UDPReceiver::receiveData, this);
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return false;
    }
    return true;
}

bool UDPReceiver::isValid()
{
    return this->socket->isValid();
}

void UDPReceiver::receiveData()
{
    while (this->socket->isValid())
    {
        if (this->socket->hasPendingDatagrams())
        {
            H264Packet packet;
            auto datagram = this->socket->receiveDatagram();
            auto pchar = datagram.data();
            auto count = pchar.count();
            packet.timestamp = be64toh( *reinterpret_cast<uint64_t*>(pchar.data()));
            packet.datasize = be64toh(*reinterpret_cast<uint64_t*>(pchar.data()+8));
//            std::cout << "timestamp: " << packet.timestamp << " datasize: " << packet.datasize << std::endl;
            // we are shifting the pchar by 8 bytes because we already pulled the timestamp out so we only want the h264 payload
            this->processData(pchar.data()+16,count-16,packet.pData);
            emit this->dataReady(packet);
        }
    }
}

void UDPReceiver::processData(char *data, int dataLength, std::vector<unsigned char>& outdata)
{
    for (int idx = 0; idx < dataLength/2; ++idx) // data by 2 because we will process these in shorts
    {
        // reinterpret the data as unsigned short since that the smallest version of ntohs there is
        uint16_t* val = &reinterpret_cast<uint16_t*>(data)[idx];
        // convert to host byte order (little endien) from network byte order (big endien)
        uint16_t newval = ntohs(*val);
        // shift the bits to get the upper and lower nibbles of the shorts and push them into the output vector
        auto upper = static_cast<unsigned char>((newval >> 8) & 0x00ff);
        auto lower = static_cast<unsigned char>(newval & 0x00ff);
        outdata.push_back(upper);
        outdata.push_back(lower);
    }
}


