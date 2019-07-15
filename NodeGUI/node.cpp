#include "node.h"
#include "ui_node.h"

node::node(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::node)
{
    ui->setupUi(this);
}

node::~node()
{
    delete ui;
}
