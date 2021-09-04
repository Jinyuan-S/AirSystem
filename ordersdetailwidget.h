#ifndef ORDERSDETAILWIDGET_H
#define ORDERSDETAILWIDGET_H

#include <QWidget>

namespace Ui {
class OrdersDetailWidget;
}

class OrdersDetailWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OrdersDetailWidget(QWidget *parent = nullptr);
    ~OrdersDetailWidget();

private:
    Ui::OrdersDetailWidget *ui;
};

#endif // ORDERSDETAILWIDGET_H
