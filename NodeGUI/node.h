#ifndef NODE_H
#define NODE_H

#include <QWidget>


namespace Ui {
class node;
}

class node : public QWidget
{
    Q_OBJECT

public:
    explicit node(QWidget *parent = nullptr);
    ~node();

private:
    Ui::node *ui;

};

#endif // NODE_H
