#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "Inquiry.h"
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>
#include <vector>
#include "cartwidget.h"

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

    buyer = new Buyer();
    *buyer = *buyerTemp;

    cWidget = new CartWidget(nullptr, buyer);
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

    connect(ui->pushButton_refresh, &QPushButton::clicked, [=](){
        orderInit();
    });

    buyInit();
    orderInit();
    mineInit();

}

MainWidget::~MainWidget()
{
    delete ui;
}

//购买初始化
void MainWidget::buyInit()
{

    //初始化dateEdit
    ui->dateEdit->setDate(QDate().currentDate());
    ui->dateEdit1->setDate(QDate().currentDate());

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


    //把完成和**进入查询界面**连接起来 connect
    connect(ui->pushButton_city_complete, &QPushButton::clicked, [=](){
        newQueryWidget(0);
    });
    connect(ui->pushButton_number_complete, &QPushButton::clicked, [=](){
        newQueryWidget(1);
    });

    //热门航班初始化
    Inquiry *inq = new Inquiry();
    vector<Flight> fliVec;
    QDate date = QDate().currentDate();
    string dateStr = std::string(date.toString("yyyy-MM-dd").toLocal8Bit());
    inq->recommand(dateStr, fliVec);
    ui->scrollArea_2->setWidgetResizable(false);
    qDebug() << "flight 大小" << fliVec.size();
    //370是item宽度 10是宽度间的间隙 120是item长度 10是长度间的间隙 50是最底下多留点地
    ui->scrollAreaWidgetContents_3->resize((370 + 10), fliVec.size() * (120 + 10) + 50);
    //添加航班
    for(auto i = fliVec.begin(); i != fliVec.end(); ++i)
    {
        AirlinesItem *item = new AirlinesItem(ui->scrollAreaWidgetContents, &*i);
        //航班添加就更新购物车
        connect(item, &AirlinesItem::added, [=](vector<Children_order> vec){
            qDebug() << "MainWidget Slot Begin!";
            addCart(vec);
//            if(!ret) QMessageBox::warning(this, "购物车", "您今天购买订单超过上限5个，请重新添加！");
        });
        item->setParent(ui->scrollAreaWidgetContents_3);
        item->move(5, (i - fliVec.begin()) * (120 + 10) + 10); //5让item和左边有点间隙
        item->show();
        qDebug() << item->geometry();
    }

    //购物车
    connect(ui->label_cart, &ClickableLabel::clicked, [=](){
        cWidget->setWindowModality(Qt::ApplicationModal);
        cWidget->show();
        static bool two = 0;
        if(two == 0)
        {
            cWidget->resize(500, 400);
            two = 1;
        }
        else
        {
            cWidget->resize(501, 401);
            two = 0;
        }
    });

    connect(cWidget, &CartWidget::closed, [=](){
        ui->stackedWidget->setCurrentIndex(0);
        orderInit();
    });
}

void MainWidget::newQueryWidget(int type)  //这里从输入框里提取信息
{
    QueryWidget *widget = new QueryWidget(nullptr, type);

    //查询框添加航班就加到购物车里
    connect(widget, &QueryWidget::added, [=](vector<Children_order> vec){
        qDebug() << "MainWidget Slot From QueryWidget Begin!";
        addCart(vec);
//        if(!ret) QMessageBox::warning(this, "购物车", "您今天购买订单超过上限5个，请重新添加！");
    });

    if(type == 0)
    {
        widget->setFromAndTo(ui->lineEdit_from->text(), ui->lineEdit_to->text(), ui->dateEdit->date());
    }
    else
    {
        widget->setNumber(ui->lineEdit_num->text(), ui->dateEdit->date());
    }
    widget->setWindowModality(Qt::ApplicationModal);
    widget->show();
}

//订单初始化
void MainWidget::orderInit()
{
    ui->scrollArea->setWidgetResizable(false);
    //添加订单
    std::vector<Mother_order> motherVec;
    int orderNum = order->get_all_order(buyer->ID, motherVec);
    qDebug() << "MainWidget orderInit" << orderNum;
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
        qDebug() << "Order Num" << orderNum;
        qDebug() << "size" << motherVec.size();
        for(int i = 0; i < orderNum; ++i)
        {
            qDebug() << QString::fromLocal8Bit(motherVec.at(i).Contain);
            qDebug() << QString::fromLocal8Bit(motherVec.at(i).Is_paid);
            qDebug() << QString::fromLocal8Bit(motherVec.at(i).Is_cancel);
            qDebug() << QString::fromLocal8Bit(motherVec.at(i).Sub1);
            qDebug() << QString::fromLocal8Bit(motherVec.at(i).Sub5);
            OrdersItem *item = new OrdersItem(ui->scrollAreaWidgetContents, &motherVec.at(i));
            item->show();
            connect(item, &OrdersItem::canceled, [=](){
                QDate orderDate = QDate().fromString(QString::fromLocal8Bit(motherVec.at(i).Time.substr(0, 10)), "yyyy-MM-dd");
                qDebug() << "orderTime is" << QString::fromLocal8Bit(motherVec.at(i).Time);
                qDebug() << "dateTime.date is" << orderDate;
                if(orderDate == QDate().currentDate())
                {
                    cWidget->five -= stoi(motherVec.at(i).Contain);
                    qDebug() << "five is" << cWidget->five;
                }
            });
//            item->setParent(ui->scrollAreaWidgetContents);
            qDebug() << i << "now" << item->geometry();
            item->move(5, i * (200 + 10) + 10); //5让item和左边有点间隙
        }
    }
    repaint();
}


//个人信息初始化
void MainWidget::mineInit()
{
    ui->widget_3->setBuyer(buyer);
}

bool MainWidget::addCart(vector<Children_order> orders)
{
    qDebug() << "MainWidget Slot REALLY Begin!";
    return cWidget->addOrder(orders);
}


void MainWidget::closeEvent(QCloseEvent *event)
{
    qDebug() << "recording Five";
    Write *write = new Write(buyer->ID + ".txt");
    Write *write2 = new Write(buyer->ID + ".txt");
    write2->append(string(QDate().currentDate().toString("yyyy-MM-dd").toLocal8Bit()));
    write2->append(to_string(cWidget->five));
    delete write;
    delete write2;
}
