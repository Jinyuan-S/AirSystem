#ifndef ORDERSITEM_H
#define ORDERSITEM_H

#include <QWidget>

#include "ordersdetailwidget.h"

namespace Ui {
class OrdersItem;
}

class OrdersItem : public QWidget
{
    Q_OBJECT

public:
    explicit OrdersItem(QWidget *parent = nullptr);
    ~OrdersItem();

private:
    Ui::OrdersItem *ui;
    OrdersDetailWidget *detailWidget;
};

#endif // ORDERSITEM_H
