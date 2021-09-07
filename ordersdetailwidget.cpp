#include "ordersdetailwidget.h"
#include "ui_ordersdetailwidget.h"
#include <QMessageBox>
using std::vector;
using std::stoi;
#include <vector>
#include <string>
#include <QString>
#include <QCloseEvent>
#include <QMessageBox>

OrdersDetailWidget::OrdersDetailWidget(QWidget *parent, Mother_order *orderTemp) :
    QWidget(parent),
    motherOrder(orderTemp),
    ui(new Ui::OrdersDetailWidget)
{
    ui->setupUi(this);
    setWindowTitle("订单具体信息");
    qDebug() << "OrdersDetail";

    qDebug() << "details temp NOW!";
    qDebug() << orderTemp;
    qDebug() << QString::fromLocal8Bit(orderTemp->Contain);
    qDebug() << QString::fromLocal8Bit(orderTemp->Is_paid);
    qDebug() << QString::fromLocal8Bit(orderTemp->Is_cancel);
    qDebug() << QString::fromLocal8Bit(orderTemp->Time);
    qDebug() << QString::fromLocal8Bit(orderTemp->Sub1);
    qDebug() << QString::fromLocal8Bit(orderTemp->Sub5);
    motherOrder = new Mother_order();
    *motherOrder = *orderTemp;
    order = new Order();

    qDebug() << "details motherOrder NOW!";
    qDebug() << motherOrder;
    qDebug() << QString::fromLocal8Bit(motherOrder->Contain);
    qDebug() << QString::fromLocal8Bit(motherOrder->Is_paid);
    qDebug() << QString::fromLocal8Bit(motherOrder->Is_cancel);
    qDebug() << QString::fromLocal8Bit(motherOrder->Time);
    qDebug() << QString::fromLocal8Bit(motherOrder->Sub1);
    qDebug() << QString::fromLocal8Bit(motherOrder->Sub5);

    //connect 支付功能
    connect(ui->label_pay, &ClickableLabel::clicked, [=](){
        qDebug() << "detail支付准备";
        if(QMessageBox::Ok
                == QMessageBox::question(this, "订单信息", "您确定要付款吗？", QMessageBox::Ok|QMessageBox::Cancel))
        {
            qDebug() << "detail支付准备1";
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
    qDebug() << "detailsUpdating NOW!";
    qDebug() << QString::fromLocal8Bit(motherOrder->Contain);
    qDebug() << QString::fromLocal8Bit(motherOrder->Is_paid);
    qDebug() << QString::fromLocal8Bit(motherOrder->Is_cancel);
    qDebug() << QString::fromLocal8Bit(motherOrder->Time);
    qDebug() << QString::fromLocal8Bit(motherOrder->Sub1);
    qDebug() << QString::fromLocal8Bit(motherOrder->Sub5);

    qDebug() << "OrdersBasicInit";



    //如果订单已经完成支付或者已经退票，则不显示退票和支付
    if(motherOrder->Is_paid == "1" || motherOrder->Is_cancel == "1")
    {
        ui->widget_pay->hide();
    }
    else
    {
        ui->widget_pay->hide();
    }

    //订单金额显示
    ui->label_price->setText("￥" + QString::fromLocal8Bit(motherOrder->Money));


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

    childrenInit();
}

void OrdersDetailWidget::childrenInit()
{
//    int personNum = stoi(motherOrder->Contain);
    vector<Children_order> childVec;
    int childNum = order->get_sub_order(*motherOrder, childVec);

    //把不需要的widget都隐藏
    if(childNum == 1)
    {
        ui->widget_a1->show();
        ui->widget_a2->hide();
        ui->widget_a3->hide();
        ui->widget_a4->hide();
        ui->widget_a5->hide();
    }
    else if(childNum == 2)
    {
        ui->widget_a1->show();
        ui->widget_a2->show();
        ui->widget_a3->hide();
        ui->widget_a4->hide();
        ui->widget_a5->hide();
    }
    else if(childNum == 3)
    {
        ui->widget_a1->show();
        ui->widget_a2->show();
        ui->widget_a3->show();
        ui->widget_a4->hide();
        ui->widget_a5->hide();
    }
    else if(childNum == 4)
    {
        ui->widget_a1->show();
        ui->widget_a2->show();
        ui->widget_a3->show();
        ui->widget_a4->show();
        ui->widget_a5->hide();
    }
    else if(childNum == 5)
    {
        ui->widget_a1->show();
        ui->widget_a2->show();
        ui->widget_a3->show();
        ui->widget_a4->show();
        ui->widget_a5->show();
    }

    //加载子订单信息, TODO:目的地显示
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(QPixmap(":/main/images/edging270_170.jpg")));
    if(childNum >= 1)
    {
        ui->label_air1->setText("--" + QString::fromLocal8Bit(childVec.at(0).Airline) + "->");
        ui->label_cabin1->setText(QString::fromLocal8Bit(childVec.at(0).Cabin));
        ui->label_pass1->setText(QString::fromLocal8Bit(childVec.at(0).Who));
        ui->label_price1->setText("￥" + QString::fromLocal8Bit(childVec.at(0).Money));
        ui->label_seat1->setText("座位:" + QString::fromLocal8Bit(childVec.at(0).Seat));
        ui->label_date1->setText("日期:" + QString::fromLocal8Bit(childVec.at(0).Date));
        ui->widget_a1->setPalette(palette);
    }
    if(childNum >= 2)
    {
        ui->label_air1_2->setText("--" + QString::fromLocal8Bit(childVec.at(1).Airline) + "->");
        ui->label_cabin1_2->setText(QString::fromLocal8Bit(childVec.at(1).Cabin));
        ui->label_pass1_2->setText(QString::fromLocal8Bit(childVec.at(1).Who));
        ui->label_price1_2->setText("￥" + QString::fromLocal8Bit(childVec.at(1).Money));
        ui->label_seat1_2->setText("座位:" + QString::fromLocal8Bit(childVec.at(1).Seat));
        ui->label_date1_2->setText("日期:" + QString::fromLocal8Bit(childVec.at(1).Date));
        ui->widget_a2->setPalette(palette);
    }
    if(childNum >= 3)
    {
        ui->label_air1_3->setText("--" + QString::fromLocal8Bit(childVec.at(2).Airline) + "->");
        ui->label_cabin1_3->setText(QString::fromLocal8Bit(childVec.at(2).Cabin));
        ui->label_pass1_3->setText(QString::fromLocal8Bit(childVec.at(2).Who));
        ui->label_price1_3->setText("￥" + QString::fromLocal8Bit(childVec.at(2).Money));
        ui->label_seat1_3->setText("座位:" + QString::fromLocal8Bit(childVec.at(2).Seat));
        ui->label_date1_3->setText("日期:" + QString::fromLocal8Bit(childVec.at(2).Date));
        ui->widget_a3->setPalette(palette);
    }
    if(childNum >= 4)
    {
        ui->label_air1_4->setText("--" + QString::fromLocal8Bit(childVec.at(3).Airline) + "->");
        ui->label_cabin1_4->setText(QString::fromLocal8Bit(childVec.at(3).Cabin));
        ui->label_pass1_4->setText(QString::fromLocal8Bit(childVec.at(3).Who));
        ui->label_price1_4->setText("￥" + QString::fromLocal8Bit(childVec.at(3).Money));
        ui->label_seat1_4->setText("座位:" + QString::fromLocal8Bit(childVec.at(3).Seat));
        ui->label_date1_4->setText("日期:" + QString::fromLocal8Bit(childVec.at(3).Date));
        ui->widget_a4->setPalette(palette);
    }
    if(childNum >= 5)
    {
        ui->label_air1_5->setText("--" + QString::fromLocal8Bit(childVec.at(0).Airline) + "->");
        ui->label_cabin1_5->setText(QString::fromLocal8Bit(childVec.at(4).Cabin));
        ui->label_pass1_5->setText(QString::fromLocal8Bit(childVec.at(4).Who));
        ui->label_price1_5->setText("￥" + QString::fromLocal8Bit(childVec.at(4).Money));
        ui->label_seat1_5->setText("座位:" + QString::fromLocal8Bit(childVec.at(4).Seat));
        ui->label_date1_5->setText("日期:" + QString::fromLocal8Bit(childVec.at(4).Date));
        ui->widget_a5->setPalette(palette);
    }
}

void OrdersDetailWidget::closeEvent(QCloseEvent *event)
{
    emit closed();
    close();
//    QMessageBox::information(this, "asd", "sdfdfsfsd");
//    event->accept();
}
