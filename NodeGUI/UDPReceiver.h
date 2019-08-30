#ifndef UDPRECEIVER_H
#define UDPRECEIVER_H

#include <memory>
#include <QHostAddress>
#include <QUdpSocket>
#include <future>
#include <QObject>


struct H264Packet
{
    quint64 timestamp;
    quint64 datasize;
    std::vector<unsigned char> pData;
};

class UDPReceiver : public QObject
{
    Q_OBJECT
public:

    ~UDPReceiver(){}
    UDPReceiver(){}

    UDPReceiver(std::string address,const unsigned short port);

    bool run();

    bool isValid();

private:
    void receiveData();

    void processData(char* data, int dataLength, std::vector<unsigned char>& outdata);

private:
    std::unique_ptr<QUdpSocket>     socket;
    std::string ipAddress;
    qint16 port;
    std::future<void> _futureTask;
signals:
    void dataReady(H264Packet packet);
};

#endif // UDPRECEIVER_H
