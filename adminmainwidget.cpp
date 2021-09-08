#include "adminmainwidget.h"
#include "ui_adminmainwidget.h"

#include <QString>
#include <QStringList>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <string>

AdminMainWidget::AdminMainWidget(QWidget *parent, Admin *adminTemp) :
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

    admin = new Admin();

    *admin = *adminTemp;

    db = new QSqlDatabase();

    //初始化背景图片
    QPalette palette2;
    palette2.setBrush(QPalette::Window, QBrush(QPixmap(":/main/images/admin_main_background.jpg")));
    setPalette(palette2);

    //初始化时把按钮和对应的一级菜单连接起来
    connect(ui->pushButton_order, &QPushButton::clicked, [=](){
        //当切换到其他页面时，个人页面询问是否更改
        if(ui->widget_3->statusOfLabel == 1)
        {
            if(ui->widget_3->changeToNormal())
            {
                ui->stackedWidget->setCurrentIndex(1);
            }
        }
        else
        {
            ui->stackedWidget->setCurrentIndex(1);
        }
    });
    connect(ui->pushButton_flight, &QPushButton::clicked, [=](){//当切换到其他页面时，个人页面询问是否更改
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
    connect(ui->pushButton_mine, &QPushButton::clicked, [=](){
        ui->stackedWidget->setCurrentIndex(0);
    });

    //初始化数据库
    *db = QSqlDatabase::addDatabase("QMYSQL");
    db->setPort(3306);
    db->setHostName("8.136.214.13");    //数据库主机名
    db->setDatabaseName("airsystem");    //数据库名
    db->setUserName("root");        //数据库用户名
    db->setPassword("654321");        //数据库密码
    bool isOpen = db->open();
    qDebug() << isOpen;

    airlineInit();
    orderInit();

    //3.我的部分
    ui->widget_3->setAdmin(admin);
}

AdminMainWidget::~AdminMainWidget()
{
    delete ui;
}


void AdminMainWidget::airlineInit()
{
    QSqlTableModel *model = new QSqlTableModel(this, *db);
    model->setTable("air");
    QString qstr = QString::fromLocal8Bit(admin->Company);
    model->setFilter("company = '" + qstr + "'");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select(); //选取整个表的所有行
    model->removeColumn(0); //隐藏第1行
    ui->tableView_flight->setModel(model);
    ui->tableView_flight->show();
}

void AdminMainWidget::orderInit()
{
    QSqlTableModel *model = new QSqlTableModel(this, *db);
    model->setTable("air");
    QString qstr = QString::fromLocal8Bit(admin->Company);
    model->setFilter("company = '" + qstr + "'");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select(); //选取整个表的所有行
    model->removeColumn(0); //隐藏第1行
    model->removeColumns(8, 9); //隐藏各种上座信息
    model->removeColumn(9); //隐藏准点率
    QStringList strList = QStringList() << "航班号" << "始发地" << "目的地" << "航空公司" << "起飞时间" << "到达时间" << "是否跨天"
                                        << "机型" << "日期" << "基准价格" << "飞行员1";
    for(auto i = strList.begin(); i != strList.end(); ++i)
    {
        model->setHeaderData((i - strList.begin()), Qt::Orientation::Horizontal, *i);
    }
    ui->tableView_flight->setModel(model);
    ui->tableView_flight->show();

}

void AdminMainWidget::changeSortFliter()
{

}
