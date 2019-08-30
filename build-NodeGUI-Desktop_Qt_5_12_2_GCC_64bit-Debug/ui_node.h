/********************************************************************************
** Form generated from reading UI file 'node.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NODE_H
#define UI_NODE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_Node
{
public:
    QPushButton *deleteButton;
    QLabel *id;
    QTextBrowser *nodeConsoleOutput;
    QGraphicsView *frameDisplay;

    void setupUi(QDialog *Node)
    {
        if (Node->objectName().isEmpty())
            Node->setObjectName(QString::fromUtf8("Node"));
        Node->resize(515, 127);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Node->sizePolicy().hasHeightForWidth());
        Node->setSizePolicy(sizePolicy);
        Node->setMinimumSize(QSize(0, 127));
        deleteButton = new QPushButton(Node);
        deleteButton->setObjectName(QString::fromUtf8("deleteButton"));
        deleteButton->setGeometry(QRect(10, 10, 21, 21));
        id = new QLabel(Node);
        id->setObjectName(QString::fromUtf8("id"));
        id->setGeometry(QRect(40, 10, 67, 17));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(id->sizePolicy().hasHeightForWidth());
        id->setSizePolicy(sizePolicy1);
        nodeConsoleOutput = new QTextBrowser(Node);
        nodeConsoleOutput->setObjectName(QString::fromUtf8("nodeConsoleOutput"));
        nodeConsoleOutput->setGeometry(QRect(10, 40, 321, 71));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(nodeConsoleOutput->sizePolicy().hasHeightForWidth());
        nodeConsoleOutput->setSizePolicy(sizePolicy2);
        frameDisplay = new QGraphicsView(Node);
        frameDisplay->setObjectName(QString::fromUtf8("frameDisplay"));
        frameDisplay->setGeometry(QRect(340, 10, 171, 111));

        retranslateUi(Node);

        QMetaObject::connectSlotsByName(Node);
    } // setupUi

    void retranslateUi(QDialog *Node)
    {
        Node->setWindowTitle(QApplication::translate("Node", "Dialog", nullptr));
        deleteButton->setText(QApplication::translate("Node", "x", nullptr));
        id->setText(QApplication::translate("Node", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Node: public Ui_Node {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NODE_H
