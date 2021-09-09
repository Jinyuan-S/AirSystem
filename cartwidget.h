#ifndef CARTWIDGET_H
#define CARTWIDGET_H

#include <QWidget>
#include <QResizeEvent>
#include "Order.h"
#include "Mother_order.h"
#include "Children_order.h"
#include "cartitem.h"
#include "Buyer.h"
#include "File.h"
#include <vector>
using std::vector;

namespace Ui {
class CartWidget;
}

class CartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CartWidget(QWidget *parent = nullptr, Buyer *buyer = nullptr);
    ~CartWidget();
    bool addOrder(vector<Children_order> vec);
    int five = 0;

private:
    vector<vector<Children_order>> allOrderVec;
    vector<CartItem *> itemVec;
    void loadAllOrder(/*vector<vector<Children_order>> allOrder*/);
    void deleteAllOrder();
    Ui::CartWidget *ui;
    Read *read;
    Write *write;
    Buyer *buyerNew;

protected:
    void resizeEvent(QResizeEvent *event);

signals:
    void closed();
};

#endif // CARTWIDGET_H
