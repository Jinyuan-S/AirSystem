#ifndef ORDERSDETAILWIDGET_H
#define ORDERSDETAILWIDGET_H

#include <QWidget>
#include "Mother_order.h"
#include "Order.h"
#include "Children_order.h".

namespace Ui {
class OrdersDetailWidget;
}

class OrdersDetailWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OrdersDetailWidget(QWidget *parent = nullptr, Mother_order *orderTemp = nullptr/*, OrdersItem *fatherItemTemp = nullptr*/);
    ~OrdersDetailWidget();
//    OrdersItem *fatherItem;

private:
    Mother_order *motherOrder;
    Order *order;
    void basicInit();
    void childrenInit();
    Ui::OrdersDetailWidget *ui;

protected:
    void closeEvent(QCloseEvent *event);

signals:
    void closed();
};

#endif // ORDERSDETAILWIDGET_H
