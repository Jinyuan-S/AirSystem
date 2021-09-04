#include "ordersdetailwidget.h"
#include "ui_ordersdetailwidget.h"

OrdersDetailWidget::OrdersDetailWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrdersDetailWidget)
{
    ui->setupUi(this);
}

OrdersDetailWidget::~OrdersDetailWidget()
{
    delete ui;
}
