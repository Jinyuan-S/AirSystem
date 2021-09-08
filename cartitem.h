#ifndef CARTITEM_H
#define CARTITEM_H

#include <QWidget>
#include "Children_order.h"
#include <vector>
#include <QString>
using std::vector;

namespace Ui {
class CartItem;
}

class CartItem : public QWidget
{
    Q_OBJECT

public:
    explicit CartItem(QWidget *parent = nullptr, vector<Children_order> *order = nullptr);
    ~CartItem();

private:
    Ui::CartItem *ui;
    QString whichCabin(string str);

signals:
    void changed();
    void deleted();
};

#endif // CARTITEM_H
