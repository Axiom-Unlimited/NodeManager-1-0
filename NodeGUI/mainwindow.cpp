#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->nodeList->addItem("Node1");
    ui->nodeList->addItem("Node2");
    QString consoleInput = ui->consoleInput->text();
    ui->consoleInput->setPlaceholderText("Enter console command and press enter");
}

MainWindow::~MainWindow()
{
    delete ui;
}

