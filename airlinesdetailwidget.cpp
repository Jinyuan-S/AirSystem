#include "airlinesdetailwidget.h"
#include "ui_airlinesdetailwidget.h"


AirlinesDetailWidget::AirlinesDetailWidget(QWidget *parent, Flight *flightTemp) :
    QWidget(parent),
    ui(new Ui::AirlinesDetailWidget)
{
    ui->setupUi(this);
    flight = new Flight();
    *flight = *flightTemp;

    setWindowTitle("航班具体信息及购票");

    //初始化背景图片
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(QPixmap(":/main/images/edging863_83.jpg")));
    ui->widget_A->setPalette(palette);
    ui->widget_B->setPalette(palette);
    ui->widget_C->setPalette(palette);

    //TODO: 价格待定
    int price = stoi(flight->Price);

    //加载全部信息
    ui->label_from->setText(QString::fromLocal8Bit(flight->Origin));
    ui->label_to->setText(QString::fromLocal8Bit(flight->Destination));
    ui->label_fromTime->setText(QString::fromLocal8Bit(flight->Time_on.substr(0, 5)));
    ui->label_toTime->setText(QString::fromLocal8Bit(flight->Time_off.substr(0, 5)));
    ui->label_airline->setText(QString::fromLocal8Bit(flight->Airline));
    ui->label_date->setText(QString::fromLocal8Bit(flight->Date));
    ui->label_com->setText("航空公司:" + QString::fromLocal8Bit(flight->Company));
    ui->label_model->setText("机型:" + QString::fromLocal8Bit(flight->Model));
    ui->label_att->setText("上座率:" + QString::fromLocal8Bit(flight->Attendance) + "%");
    ui->label_rate->setText("准点率:" + QString::fromLocal8Bit(flight->Rate) + "%");
    ui->label_pilot1->setText("飞行员1:" + QString::fromLocal8Bit(flight->Pilot));
    ui->label_pilot2->setText("飞行员2:" + QString::fromLocal8Bit(flight->Pilot)); //TODO: 修改这里
    ui->label_remain_A->setText("剩余票数:" + QString::fromLocal8Bit(flight->A_remain));
    ui->label_remain_B->setText("剩余票数:" + QString::fromLocal8Bit(flight->B_remain));
    ui->label_remain_C->setText("剩余票数:" + QString::fromLocal8Bit(flight->C_remain));
    ui->label_sold_A->setText("已卖出票数:" + QString::fromLocal8Bit(flight->A_sold));
    ui->label_sold_B->setText("已卖出票数:" + QString::fromLocal8Bit(flight->B_sold));
    ui->label_sold_C->setText("已卖出票数:" + QString::fromLocal8Bit(flight->C_sold));
    ui->label_price_A->setText("￥" + QString::number((int)(price * 2.121 + 12)));
    ui->label_price_B->setText("￥" + QString::number((int)(price * 1.741 + 2)));
    ui->label_price_C->setText("￥" + QString::number((int)(price)));
}

AirlinesDetailWidget::~AirlinesDetailWidget()
{
    delete ui;
}


