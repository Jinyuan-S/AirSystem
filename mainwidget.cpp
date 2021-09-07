#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>
#include <vector>

MainWidget::MainWidget(QWidget *parent, Buyer *buyerTemp) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    if(buyerTemp == nullptr)
    {
        QMessageBox::critical(this, "账户登录", "用户没有成功登录！");
        close();
    }

    buyer = buyerTemp;

    order = new Order();

    //1.设置自动填充背景
    this->setAutoFillBackground(true);
    ui->widget_2->setAutoFillBackground(true);
    ui->widget_4->setAutoFillBackground(true);
    ui->widget_5->setAutoFillBackground(true);
    ui->stackedWidget_3->setAutoFillBackground(true);
    ui->scrollAreaWidgetContents->setAutoFillBackground(true);

    //初始化时为购票界面
    ui->stackedWidget->setCurrentIndex(2);


    qDebug() << ui->widget_5->geometry() << "That's widget_5";

    //初始化widget_5(底部选择栏)界面 :/general/images/edging100_30.jpg
    QPalette palette1;
    palette1.setBrush(QPalette::Window, QBrush(QPixmap(":/general/images/edging500_50.jpg")));
    ui->widget_5->setPalette(palette1);

    //初始化标题
    setWindowTitle("航空购票系统");

    //初始化背景图片
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(QPixmap(":/main/images/main_background.jpg")));
    setPalette(palette);


    //connect 把一级菜单和对应stackedWidget中的page联系起来
    connect(ui->pushButton_query, &QPushButton::clicked, [=](){
        //当切换到其他页面时，个人页面询问是否更改
        if(ui->widget_3->statusOfLabel == 1)
        {
            if(ui->widget_3->changeToNormal())
            {
                ui->stackedWidget->setCurrentIndex(2);
            }
        }
        else
        {
            ui->stackedWidget->setCurrentIndex(2);
        }
    });
    connect(ui->pushButton_order, &QPushButton::clicked, [=](){
        //当切换到其他页面时，个人页面询问是否更改
        if(ui->widget_3->statusOfLabel == 1)
        {
            if(ui->widget_3->changeToNormal())
            {
                ui->stackedWidget->setCurrentIndex(0);
            }
        }
        else
        {
            ui->stackedWidget->setCurrentIndex(0);
        }
    });
    connect(ui->pushButton_mine, &QPushButton::clicked, [=](){
        ui->stackedWidget->setCurrentIndex(1);
    });

    buyInit();
    orderInit();
    mineInit();

}

MainWidget::~MainWidget()
{
    delete ui;
}


void MainWidget::newQueryWidget()  //TODO: 这里要航班的信息
{
    QueryWidget *widget = new QueryWidget();
    widget->setWindowModality(Qt::ApplicationModal);
    widget->show();
}

//购买初始化
void MainWidget::buyInit()
{
    //connect 把查询方式和对应的stack联系起来
    connect(ui->pushButton_queryByNumber, &QPushButton::clicked, [=](){
        ui->stackedWidget_3->setCurrentIndex(0);
    });
    connect(ui->pushButton_queryByCity, &QPushButton::clicked, [=](){
        ui->stackedWidget_3->setCurrentIndex(1);
    });

    //交换按钮
    connect(ui->pushButton_change, &QPushButton::clicked, [=](){
        QString fromText = ui->lineEdit_from->text();
        QString toText = ui->lineEdit_to->text();
        ui->lineEdit_from->setText(toText);
        ui->lineEdit_to->setText(fromText);
    });


    //connect 把完成和进入查询界面连接起来
    connect(ui->pushButton_city_complete, &QPushButton::clicked, [=](){
        newQueryWidget();
    });
    connect(ui->pushButton_number_complete, &QPushButton::clicked, [=](){
        newQueryWidget();
    });
}

//订单初始化
void MainWidget::orderInit()
{
    ui->scrollArea->setWidgetResizable(false);
    //添加订单
    std::vector<Mother_order> motherVec;
    int orderNum = order->get_all_order(buyer->ID, motherVec);
    if(orderNum == 0)
    {
        ui->label_noOrder->show();
    }
    else
    {
        ui->label_noOrder->hide();

        //420是item宽度 11是宽度间的间隙 200是item长度 10是长度间的间隙 50是最底下多留点地
        ui->scrollAreaWidgetContents->resize((420 + 11), orderNum * (200 + 10) + 50);
        qDebug() << ui->scrollAreaWidgetContents->geometry();
        for(int i = 0; i < orderNum; ++i)
        {
            OrdersItem *item = new OrdersItem(ui->scrollAreaWidgetContents, &motherVec.at(i));
//            item->setParent(ui->scrollAreaWidgetContents);
    //        qDebug() << item->geometry();
            item->move(5, i * (200 + 10) + 10); //5让item和左边有点间隙
        }
    }

}

//个人信息初始化
void MainWidget::mineInit()
{
    ui->widget_3->setBuyer(buyer);
}
