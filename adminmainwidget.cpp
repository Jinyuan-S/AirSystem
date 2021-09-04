#include "adminmainwidget.h"
#include "ui_adminmainwidget.h"

#include <QStringList>

AdminMainWidget::AdminMainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminMainWidget)
{
    ui->setupUi(this);

    //初始化标题
    setWindowTitle("航空管理系统");

    //初始化自动设置背景
    this->setAutoFillBackground(true);
    ui->widget_2->setAutoFillBackground(true);
    ui->widget->setAutoFillBackground(true);

    //初始化背景图片
    QPalette palette2;
    palette2.setBrush(QPalette::Window, QBrush(QPixmap(":/main/images/admin_main_background.jpg")));
    setPalette(palette2);

    //初始化时把按钮和对应的一级菜单连接起来
    connect(ui->pushButton_order, &QPushButton::clicked, [=](){
        ui->stackedWidget->setCurrentIndex(1);
    });
    connect(ui->pushButton_flight, &QPushButton::clicked, [=](){
        ui->stackedWidget->setCurrentIndex(2);
    });
    connect(ui->pushButton_mine, &QPushButton::clicked, [=](){
        ui->stackedWidget->setCurrentIndex(0);
    });

    //初始化订单tabelView
//    ui->tableView_order->setHorizontalHeaderLabels(QStringList() << "航班号" << "购买用户ID" << "座位号");

    //初始化航班tabelView
//    ui->tableView_flight->setHorizontalHeader();

    //3.我的部分
    ui->widget_3->setUserType(1);


}

AdminMainWidget::~AdminMainWidget()
{
    delete ui;
}
