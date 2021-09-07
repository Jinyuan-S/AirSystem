#ifndef ORDERSITEM_H
#define ORDERSITEM_H

#include <QWidget>
#include "Order.h"
#include "Mother_order.h"
#include "Children_order.h"

#include "ordersdetailwidget.h"

namespace Ui {
class OrdersItem;
}

class OrdersItem : public QWidget
{
    Q_OBJECT

public:
    explicit OrdersItem(QWidget *parent = nullptr, Mother_order *orderTemp = nullptr);
    ~OrdersItem();

private:
    Ui::OrdersItem *ui;
    OrdersDetailWidget *detailWidget;
    Mother_order *motherOrder;
    Order *order;
    void updateOrderInUi();
};

#endif // ORDERSITEM_H
