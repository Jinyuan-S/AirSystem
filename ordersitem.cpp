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

    motherOrder = new Mother_order();

    *motherOrder = *orderTemp;

//    qDebug() << "items NOW!";
//    qDebug() << motherOrder;
//    qDebug() << QString::fromLocal8Bit(motherOrder->Contain);
//    qDebug() << QString::fromLocal8Bit(motherOrder->Is_paid);
//    qDebug() << QString::fromLocal8Bit(motherOrder->Is_cancel);
//    qDebug() << QString::fromLocal8Bit(motherOrder->Time);
//    qDebug() << QString::fromLocal8Bit(motherOrder->Sub1);
//    qDebug() << QString::fromLocal8Bit(motherOrder->Sub5);
////            item->setParent(ui->scrollAreaWidgetContents);

//    qDebug() << QString::fromLocal8Bit(motherOrder->Is_cancel);
//    qDebug() << QString::fromLocal8Bit(motherOrder->Is_paid);

    order = new Order();

    //初始化背景图片
    setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(QPixmap(":/general/images/edging420_200.jpg")));
    setPalette(palette);


    detailWidget = new OrdersDetailWidget(nullptr, motherOrder/*, this*/);

    //当detail界面关闭时，刷新状态
    connect(detailWidget, &OrdersDetailWidget::closed, [=](){
        qDebug() << "You are running now.";
        updateOrderInUi();
    });

    //connect 连接详细信息label与详细信息Widget
    connect(ui->label_detail, &ClickableLabel::clicked, [=](){
        if(detailWidget)
        {
            delete detailWidget;
            detailWidget = new OrdersDetailWidget(nullptr, motherOrder/*, this*/);
        }
        detailWidget->setWindowModality(Qt::ApplicationModal);
        detailWidget->show();
    });

    //connect 支付功能
    connect(ui->label_pay, &ClickableLabel::clicked, [=](){
        qDebug() << "item支付准备";
        if(QMessageBox::Ok
                == QMessageBox::question(this, "订单信息", "您确定要付款吗？", QMessageBox::Ok|QMessageBox::Cancel))
        {
            qDebug() << "item支付准备2";
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
        qDebug() << "item取消准备";
        if(QMessageBox::Ok
                == QMessageBox::question(this, "订单信息", "您确定要取消订单吗？", QMessageBox::Ok|QMessageBox::Cancel))
        {

            qDebug() << "item取消准备2";
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
    updateOrderInUi();

}

OrdersItem::~OrdersItem()
{
    delete ui;
}

void OrdersItem::updateOrderInUi()
{

    qDebug() << "itemsUpdating NOW!";
    qDebug() << motherOrder;
    qDebug() << QString::fromLocal8Bit(motherOrder->Mother);
    qDebug() << QString::fromLocal8Bit(motherOrder->Contain);
    qDebug() << QString::fromLocal8Bit(motherOrder->Is_paid);
    qDebug() << QString::fromLocal8Bit(motherOrder->Is_cancel);
    qDebug() << QString::fromLocal8Bit(motherOrder->Time);
    qDebug() << QString::fromLocal8Bit(motherOrder->Sub1);
    qDebug() << QString::fromLocal8Bit(motherOrder->Sub5);
//            item->setParent(ui->scrollAreaWidgetContents);

    qDebug() << QString::fromLocal8Bit(motherOrder->Is_cancel);
    qDebug() << QString::fromLocal8Bit(motherOrder->Is_paid);


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
    else if(0) //TODO: 判断时间
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

    //如果为1人，则不显示“等订单”
    if(motherOrder->Contain == "1")
    {
        ui->label_etc->hide();
    }
    else
    {
        ui->label_etc->show();
    }

    //订单号显示
    ui->label_dynamic->setText("订单号：" + QString::fromLocal8Bit(motherOrder->Mother));

    //下单时间显示
    ui->label_time->setText("下单时间：" + QString::fromLocal8Bit(motherOrder->Time));
    qDebug() << QString::fromLocal8Bit(motherOrder->Time);

    //始发地、目的地显示
    vector<Children_order> childVec;
    order->get_sub_order(*motherOrder, childVec);
    vector<std::string> childNumberVec;
    vector<vector<std::string>> childFromAndToVec;
    for(auto i = childVec.begin(); i != childVec.end(); ++i)
    {
        childNumberVec.push_back(i->Airline);
    }
    order->where2where(childNumberVec, childFromAndToVec);
    ui->label_from->setText(QString::fromLocal8Bit(childFromAndToVec.at(0).at(0)));
    ui->label_to->setText(QString::fromLocal8Bit(childFromAndToVec.at(0).at(1)));
    ui->label_fromTime->setText(QString::fromLocal8Bit(childFromAndToVec.at(0).at(2)));
    ui->label_toTime->setText(QString::fromLocal8Bit(childFromAndToVec.at(0).at(3)));
}
