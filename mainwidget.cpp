#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>

MainWidget::MainWidget(QWidget *parent, Buyer *buyer) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    if(buyer == nullptr)
    {
        QMessageBox::critical(this, "严重错误", "用户没有成功登录！");
    }


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

    //初始化widget_5界面 :/general/images/edging100_30.jpg
    QPalette palette1;
    palette1.setBrush(QPalette::Window, QBrush(QPixmap(":/general/images/edging500_50.jpg")));
    ui->widget_5->setPalette(palette1);


    if(1)
    {
        //购票用户部分----------------

        //初始化标题
        setWindowTitle("航空购票系统");

        //初始化背景图片
        QPalette palette;
        palette.setBrush(QPalette::Window, QBrush(QPixmap(":/main/images/main_background.jpg")));
        setPalette(palette);


        //connect 把一级菜单和对应stackedWidget中的page联系起来
        connect(ui->pushButton_query, &QPushButton::clicked, [=](){//当切换到其他页面时，个人页面询问是否更改
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
        connect(ui->pushButton_order, &QPushButton::clicked, [=](){//当切换到其他页面时，个人页面询问是否更改
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


        //1.购票部分

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

        //2.订单部分

        //添加订单
        const int Num = 8;  //TODO:记得改这个数
        ui->scrollArea->setWidgetResizable(false);
        ui->scrollAreaWidgetContents->resize((420 + 11), Num * (200 + 10) + 50); //420是item宽度 11是宽度间的间隙 200是item长度 10是长度间的间隙 50是最底下多留点地
        qDebug() << ui->scrollAreaWidgetContents->geometry();
        for(int i = 0; i < Num; ++i)
        {
            OrdersItem *item = new OrdersItem();
            item->setParent(ui->scrollAreaWidgetContents);
    //        qDebug() << item->geometry();
            item->move(5, i * (200 + 10) + 10); //5让item和左边有点间隙
        }

        //3.我的部分
        ui->widget_3->setBuyer(buyer);
        //购票用户部分结束-------------
    }

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
