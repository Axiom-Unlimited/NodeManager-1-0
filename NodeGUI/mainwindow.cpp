#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <node.h>
#include <QTableWidgetItem>
#include <string>
#include <sstream>
#include <QtUiTools/QUiLoader>
#include <QFile>
#include <iostream>
#include <QVBoxLayout>
#include <memory>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString consoleInput = ui->consoleInput->text();
    ui->consoleInput->setPlaceholderText("Enter console command and press enter");
    ui->nodeContainer->setLayout(new QVBoxLayout());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addNode_clicked()
{
    auto id = ui->nodeContainer->layout()->children().length();
    auto node = std::make_unique<Node>(id, "192.168.1.255", 65500 + id, this);
    ui->nodeContainer->layout()->addWidget(node.get());
    this->nodes.push_back(std::move(node));
}

void MainWindow::on_saveConfig_clicked()
{
    //todo: should save all of the relevent node data to be loaded in later such as calibration data and desingations etc.
}

void MainWindow::on_loadConfig_clicked()
{
    //todo: load a previously saved config
}
