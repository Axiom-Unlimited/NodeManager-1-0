#ifndef UDPRECEIVER_H
#define UDPRECEIVER_H

#include <memory>
#include <QHostAddress>
#include <QUdpSocket>
#include <future>


struct H264Packet
{
    unsigned long long timestamp;
    std::unique_ptr<char[1024]> pData;
};

class UDPReceiver
{
public:
    UDPReceiver(const QHostAddress address,const unsigned short port);

    void setCallback(std::function<void(H264Packet)> usrCallback);

    bool run();

private:
    void receiveData();

private:
    QUdpSocket                                      socket;
    QHostAddress                                    ipAddress;
    int                                             port;
    std::function<void(H264Packet)>   callback;
    std::future<void>                               _futureTask;
};

#endif // UDPRECEIVER_H
