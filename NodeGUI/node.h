#ifndef NODE_H
#define NODE_H

#include <QDialog>
#include <UDPReceiver.h>
#include <NvDecoder.h>
#include <map>
#include <opencv2/core.hpp>
#include <future>
#include <mutex>

namespace Ui {
class Node;
}

class Node : public QDialog
{
    Q_OBJECT

public:
    explicit Node(int id, std::string ip, int baseport, QWidget *parent = nullptr);
    ~Node();

private:
    void decode();
    void getImage(CUdeviceptr dpSrc, uint8_t *pDst, int nWidth, int nHeight);
private:
    Ui::Node *ui;
    std::unique_ptr<UDPReceiver> receiver;
    int id;
    std::string ipAddress;
    int baseport;
    std::map<unsigned long long, std::pair<unsigned long long, std::vector<unsigned char>>> frames;
    std::future<void> _futureTask;
    std::mutex mtx;

private slots :
     void dataReturn(H264Packet packet);
};

#endif // NODE_H
