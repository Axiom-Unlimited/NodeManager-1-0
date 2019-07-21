#ifndef UDPRECEIVER_H
#define UDPRECEIVER_H

#include <memory>
#include <QHostAddress>
#include <QUdpSocket>
#include <future>
#include <QObject>


struct H264Packet
{
    unsigned long long timestamp;
    char pData[1016];
};

class UDPReceiver : public QObject
{
    Q_OBJECT
public:

    ~UDPReceiver(){}
    UDPReceiver(){}

    UDPReceiver(std::string address,const unsigned short port);

//    void setCallback(const std::function<void(std::shared_ptr<H264Packet>)> usrCallback);

    bool run();


private:
    void receiveData();

private:
    std::unique_ptr<QUdpSocket>                         socket;
    std::string                                         ipAddress;
    qint16                                              port;
//    std::function<void(std::shared_ptr<H264Packet>)>    callback;
    std::future<void>                                   _futureTask;
signals:
    void dataReady(H264Packet packet);
};

#endif // UDPRECEIVER_H
