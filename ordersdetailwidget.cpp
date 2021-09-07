#include "ordersdetailwidget.h"
#include "ui_ordersdetailwidget.h"

OrdersDetailWidget::OrdersDetailWidget(QWidget *parent, Mother_order *orderTemp) :
    QWidget(parent),
    ui(new Ui::OrdersDetailWidget)
{
    ui->setupUi(this);
}

OrdersDetailWidget::~OrdersDetailWidget()
{
    delete ui;
}
