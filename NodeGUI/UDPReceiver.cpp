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


UDPReceiver::UDPReceiver(std::string address, const unsigned short port) : ipAddress(address), port(port)
{
    qRegisterMetaType<H264Packet>("H264Packet");
    QHostAddress qAddress(QString::fromStdString(this->ipAddress));
    this->socket = std::make_unique<QUdpSocket>(this);
    auto ret = this->socket->bind(qAddress, 65500);
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

//void UDPReceiver::setCallback(std::function<void (std::shared_ptr<H264Packet>)> usrCallback)
//{
//    this->callback = usrCallback;
//    if(this->run())
//    {
//        std::cout << "failed to start data accuisition thread" << std::endl;
//    }
//}


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

void UDPReceiver::receiveData()
{
    while (this->socket->isValid())
    {
        if (this->socket->hasPendingDatagrams())
        {
            H264Packet packet;
            auto datagram = this->socket->receiveDatagram();
            mempcpy(&packet,datagram.data().data(),1024);
            emit this->dataReady(packet);
        }
    }
}

