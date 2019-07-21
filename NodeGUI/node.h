#ifndef NODE_H
#define NODE_H

#include <QDialog>
#include <UDPReceiver.h>

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
    Ui::Node *ui;
    std::unique_ptr<UDPReceiver> receiver;
    int id;
    std::string ipAddress;
    int baseport;

private slots :
     void dataReturn(H264Packet packet);
};

#endif // NODE_H
