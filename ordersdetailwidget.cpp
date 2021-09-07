#include "ordersdetailwidget.h"
#include "ui_ordersdetailwidget.h"
#include <QMessageBox>

OrdersDetailWidget::OrdersDetailWidget(QWidget *parent, Mother_order *orderTemp) :
    QWidget(parent),
    motherOrder(orderTemp),
    ui(new Ui::OrdersDetailWidget)
{
    ui->setupUi(this);
    qDebug() << "OrdersDetail";
    motherOrder = orderTemp;
    order = new Order();

    //connect 支付功能
    connect(ui->label_pay, &ClickableLabel::clicked, [=](){
        if(QMessageBox::Ok
                == QMessageBox::question(this, "订单信息", "您确定要付款吗？", QMessageBox::Ok|QMessageBox::Cancel))
        {
            motherOrder->Is_paid = "1";
            if(order->renew(*motherOrder))
            {
                QMessageBox::information(this, "订单信息", "支付成功！");
                qDebug() << QString::fromLocal8Bit(motherOrder->Is_cancel) << "beforeCancel";
                qDebug() << QString::fromLocal8Bit(motherOrder->Is_paid) << "beforePaid";
                basicInit();
                qDebug() << QString::fromLocal8Bit(motherOrder->Is_cancel) << "afterCancel";
                qDebug() << QString::fromLocal8Bit(motherOrder->Is_paid) << "afterPaid";
            }
            else
            {
                QMessageBox::warning(this, "订单信息", "支付失败！");
            }
        }
    });

    //connect 取消功能
    connect(ui->label_refund, &ClickableLabel::clicked, [=](){
        if(QMessageBox::Ok
                == QMessageBox::question(this, "订单信息", "您确定要取消订单吗？", QMessageBox::Ok|QMessageBox::Cancel))
        {
            motherOrder->Is_cancel = "1";
            if(order->renew(*motherOrder))
            {
                QMessageBox::information(this, "订单信息", "取消成功！");
                basicInit();
            }
            else
            {
                QMessageBox::warning(this, "订单信息", "取消失败！");
            }
        }
    });
    basicInit();
}

OrdersDetailWidget::~OrdersDetailWidget()
{
    delete ui;
}

void OrdersDetailWidget::basicInit()
{
    qDebug() << "OrdersBasicInit";

    //如果订单已经完成支付或者已经退票，则不显示退票和支付
    if(motherOrder->Is_paid == "1" || motherOrder->Is_cancel == "1")
    {
        ui->widget_pay->hide();
    }


    qDebug() << "OrdersBasicStatus";
    //订单状态显示
    QPalette palette;
    if(motherOrder->Is_cancel == "1")
    {
        ui->label_status->setText("已取消"); //灰色
        palette.setColor(QPalette::WindowText, QColor(128, 128, 128));
        ui->label_status->setPalette(palette);
    }
    else if(motherOrder->Is_paid == "0")
    {
        ui->label_status->setText("未支付"); //红色
        palette.setColor(QPalette::WindowText, QColor(171, 5, 13));
        ui->label_status->setPalette(palette);
    }
    else if(motherOrder->Is_paid == "1")
    {
        ui->label_status->setText("待出发"); //橙色
        palette.setColor(QPalette::WindowText, QColor(217, 123, 16));
        ui->label_status->setPalette(palette);
    }
    else if(0)
    {
        ui->label_status->setText("已出发"); //蓝色
        palette.setColor(QPalette::WindowText, QColor(20, 14, 206));
        ui->label_status->setPalette(palette);

    }
    else if(0)
    {
        ui->label_status->setText("已到达"); //绿色
        palette.setColor(QPalette::WindowText, QColor(17, 165, 17));
        ui->label_status->setPalette(palette);
    }
    qDebug() << "OrdersBasicPersonB";
    qDebug() << QString::fromLocal8Bit(motherOrder->Contain);

    qDebug() << "OrdersBasicPersonA";
    qDebug() << QString::fromLocal8Bit(motherOrder->Contain);

    //订单号显示
    ui->label_num->setText("订单号：" + QString::fromLocal8Bit(motherOrder->Mother));
    qDebug() << "OrdersBasicPerson";

    //下单时间显示
    ui->label_time->setText("下单时间：" + QString::fromLocal8Bit(motherOrder->Time));
    qDebug() << QString::fromLocal8Bit(motherOrder->Time);

    //购票人数显示
    QString qstr = "共";
    qstr += QString::fromLocal8Bit(motherOrder->Contain);
    qstr += "人";
    ui->label_total->setText(qstr);

    qDebug() << "OrdersBasicPerson";
}

void OrdersDetailWidget::childrenInit()
{

}
