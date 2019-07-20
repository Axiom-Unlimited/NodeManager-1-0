#include "node.h"
#include "ui_node.h"

Node::Node(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Node)
{
    ui->setupUi(this);
}

Node::~Node()
{
    delete ui;
}
