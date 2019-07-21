#include "node.h"
#include "ui_node.h"
#include <iostream>
#include <UDPReceiver.h>

Node::Node(int id, std::string ip, int baseport, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Node),
    id(id),
    ipAddress(ip),
    baseport(baseport)
{
    ui->setupUi(this);
    this->receiver = std::make_unique<UDPReceiver>(ip,id+baseport);
    connect(this->receiver.get(),&UDPReceiver::dataReady,this, &Node::dataReturn);
//    this->receiver->setCallback(std::bind(&Node::dataReturn,this,std::placeholders::_1));
//    this->receiver->run();
}

Node::~Node()
{
    delete ui;
}

void Node::dataReturn(H264Packet packet)
{
    std::cout << packet.timestamp << std::endl;
}

