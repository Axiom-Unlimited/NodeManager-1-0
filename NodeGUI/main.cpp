#include "mainwindow.h"
#include <QApplication>
#include "opencv4/opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    auto img = cv::imread("/home/mfigueroa/Desktop/img.png");
    cv::imshow("test",img);
    w.show();

    return a.exec();
}
