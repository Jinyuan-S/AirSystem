#ifndef CARTWIDGET_H
#define CARTWIDGET_H

#include <QWidget>
#include <QResizeEvent>
#include "Order.h"
#include "Mother_order.h"
#include "Children_order.h"
#include "cartitem.h"
#include "Buyer.h"
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
    void addOrder(vector<Children_order> vec);

private:
    vector<vector<Children_order>> allOrderVec;
    vector<CartItem *> itemVec;
    void loadAllOrder(/*vector<vector<Children_order>> allOrder*/);
    void deleteAllOrder();
    Ui::CartWidget *ui;

protected:
    void resizeEvent(QResizeEvent *event);

signals:
    void closed();
};

#endif // CARTWIDGET_H
