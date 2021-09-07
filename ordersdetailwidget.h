#ifndef ORDERSDETAILWIDGET_H
#define ORDERSDETAILWIDGET_H

#include <QWidget>
#include "Mother_order.h"
#include "Order.h"
#include "Children_order.h"

namespace Ui {
class OrdersDetailWidget;
}

class OrdersDetailWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OrdersDetailWidget(QWidget *parent = nullptr, Mother_order *orderTemp = nullptr);
    ~OrdersDetailWidget();

private:
    Mother_order *motherOrder;
    Order *order;
    Ui::OrdersDetailWidget *ui;
};

#endif // ORDERSDETAILWIDGET_H
