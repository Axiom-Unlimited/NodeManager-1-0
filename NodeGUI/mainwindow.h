#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <node.h>
#include <memory>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addNode_clicked();

    void on_saveConfig_clicked();

    void on_loadConfig_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<std::unique_ptr<Node>> nodes;
};

#endif // MAINWINDOW_H
