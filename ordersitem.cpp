#include "ordersitem.h"
#include "ui_ordersitem.h"

#include <QMessageBox>
#include <QPalette>
#include <QString>

OrdersItem::OrdersItem(QWidget *parent, Mother_order *orderTemp) :
    QWidget(parent),
    ui(new Ui::OrdersItem)
{
    ui->setupUi(this);

    motherOrder = orderTemp;

    qDebug() << QString::fromLocal8Bit(motherOrder->Is_cancel);
    qDebug() << QString::fromLocal8Bit(motherOrder->Is_paid);

    order = new Order();

    updateOrderInUi();

    //初始化背景图片
    setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(QPixmap(":/general/images/edging420_200.jpg")));
    setPalette(palette);

    //connect 连接详细信息label与详细信息Widget
    connect(ui->label_detail, &ClickableLabel::clicked, [=](){
        detailWidget = new OrdersDetailWidget(nullptr, motherOrder);
        detailWidget->setWindowModality(Qt::ApplicationModal);
        detailWidget->show();
    });

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
                updateOrderInUi();
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
                updateOrderInUi();
            }
            else
            {
                QMessageBox::warning(this, "订单信息", "取消失败！");
            }
        }
    });
}

OrdersItem::~OrdersItem()
{
    delete ui;
}

void OrdersItem::updateOrderInUi()
{


    //如果订单已经完成支付或者已经退票，则不显示退票和支付
    if(motherOrder->Is_paid == "1" || motherOrder->Is_cancel == "1")
    {
        ui->label_pay->hide();
        ui->label_refund->hide();
    }

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

    //购票人数显示
    QString qstr = "共";
    qstr += QString::fromLocal8Bit(motherOrder->Contain);
    qstr += "人";
    ui->label_total->setText(qstr);

    //订单号显示
    ui->label_dynamic->setText("订单号：" + QString::fromLocal8Bit(motherOrder->Mother));

    //下单时间显示
    ui->label_time->setText("下单时间：" + QString::fromLocal8Bit(motherOrder->Time));
    qDebug() << QString::fromLocal8Bit(motherOrder->Time);
}
