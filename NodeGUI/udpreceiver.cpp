#include "udpreceiver.h"
#include <iostream>
#include <QNetworkDatagram>
#include <QByteArray>
#include <iostream>
#include <memory>

UDPReceiver::UDPReceiver(const QHostAddress address, const unsigned short port) : ipAddress(address), port(port)
{
    this->socket.bind(address, port);
}

void UDPReceiver::setCallback(std::function<void (H264Packet)> usrCallback)
{
    this->callback = usrCallback;
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

void UDPReceiver::receiveData()
{
    //todo: recieve data and push to callback.
    while (this->socket.isValid())
    {
        H264Packet packet;
        char* pPacket = reinterpret_cast<char*>(&packet);
        this->socket.readDatagram(pPacket,1024);
        this->callback(std::move(packet));
    }
}

