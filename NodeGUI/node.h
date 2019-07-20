#ifndef NODE_H
#define NODE_H

#include <QDialog>

namespace Ui {
class Node;
}

class Node : public QDialog
{
    Q_OBJECT

public:
    explicit Node(QWidget *parent = nullptr);
    ~Node();

private:
    Ui::Node *ui;
};

#endif // NODE_H
