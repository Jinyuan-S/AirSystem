#include "cartitem.h"
#include "ui_cartitem.h"
#include "Order.h"
#include <QMessageBox>

CartItem::CartItem(QWidget *parent, vector<Children_order> *order) :
    QWidget(parent),
    ui(new Ui::CartItem)
{
    ui->setupUi(this);
    int size = order->size();
    ui->widget_2->hide();
    ui->widget_3->hide();
    ui->widget_4->hide();
    ui->widget_5->hide();
    ui->widget_6->hide();

    ui->label_del->hide();

    ui->label_total->setText("共" + QString::number(size) + "人");

    //加载每一位乘客的具体信息
    if(size >= 1)
    {
        ui->widget_2->show();
        Children_order cOrder = order->at(0);
        ui->label_p1->setText("乘客1:" + QString::fromLocal8Bit(cOrder.Who));
        ui->label_cabin1->setText(whichCabin(cOrder.Cabin));
        ui->label_seat1->setText(QString::fromLocal8Bit(cOrder.Seat));
    }
    if(size >= 2)
    {
        ui->widget_3->show();
        Children_order cOrder = order->at(1);
        ui->label_p1_2->setText("乘客2:" + QString::fromLocal8Bit(cOrder.Who));
        ui->label_cabin1_2->setText(whichCabin(cOrder.Cabin));
        ui->label_seat1_2->setText(QString::fromLocal8Bit(cOrder.Seat));
    }
    if(size >= 3)
    {
        ui->widget_4->show();
        Children_order cOrder = order->at(2);
        ui->label_p1_3->setText("乘客3:" + QString::fromLocal8Bit(cOrder.Who));
        ui->label_cabin1_3->setText(whichCabin(cOrder.Cabin));
        ui->label_seat1_3->setText(QString::fromLocal8Bit(cOrder.Seat));
    }
    if(size >= 4)
    {
        ui->widget_5->show();
        Children_order cOrder = order->at(3);
        ui->label_p1_4->setText("乘客4:" + QString::fromLocal8Bit(cOrder.Who));
        ui->label_cabin1_4->setText(whichCabin(cOrder.Cabin));
        ui->label_seat1_4->setText(QString::fromLocal8Bit(cOrder.Seat));
    }
    if(size >= 5)
    {
        ui->widget_6->show();
        Children_order cOrder = order->at(4);
        ui->label_p1_5->setText("乘客5:" + QString::fromLocal8Bit(cOrder.Who));
        ui->label_cabin1_5->setText(whichCabin(cOrder.Cabin));
        ui->label_seat1_5->setText("座位:" + QString::fromLocal8Bit(cOrder.Seat));
    }

    Children_order first = order->at(0);
    //加载航班基本信息
    ui->label_num->setText(QString::fromLocal8Bit(first.Airline));
    ui->label_price->setText("￥" + QString::number(stoi(first.Money) * size));
    ui->label_date->setText(QString::fromLocal8Bit(first.Date));

    //始发地、目的地显示
    vector<Children_order> childVec;
    Order *orderQuery = new Order();
    vector<std::string> childNumberVec;
    childNumberVec.push_back(first.Airline);
    vector<vector<std::string>> childFromAndToVec;
    orderQuery->where2where(childNumberVec, childFromAndToVec);
    ui->label_from->setText(QString::fromLocal8Bit(childFromAndToVec.at(0).at(0)));
    ui->label_to->setText(QString::fromLocal8Bit(childFromAndToVec.at(0).at(1)));
    ui->label_fromTime->setText(QString::fromLocal8Bit(childFromAndToVec.at(0).at(2)));
    ui->label_toTime->setText(QString::fromLocal8Bit(childFromAndToVec.at(0).at(3)));

    //删除键
    connect(ui->label_del, &ClickableLabel::clicked, [=](){
        if(QMessageBox::Ok == QMessageBox::question(this, "购物车", "您确定要删除订单吗？", QMessageBox::Ok | QMessageBox::Cancel))
        {
            emit deleted();
        }
    });
}

CartItem::~CartItem()
{
    delete ui;
}

QString CartItem::whichCabin(string str)
{
    if(str == "A") return "头等舱";
    else if(str == "B") return "商务舱";
    else return "经济舱";
}
