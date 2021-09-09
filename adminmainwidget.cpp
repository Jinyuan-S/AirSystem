#include "adminmainwidget.h"
#include "ui_adminmainwidget.h"

#include <QString>
#include <QStringList>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <string>
#include <map>
#include <utility>
using std::make_pair;
using std::map;
#include "addflightwidget.h"

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
                ui->stackedWidget->setCurrentIndex(2);
            }
        }
        else
        {
            ui->stackedWidget->setCurrentIndex(2);
        }
    });

    connect(ui->pushButton_order2, &QPushButton::clicked, [=](){
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
                ui->stackedWidget->setCurrentIndex(3);
            }
        }
        else
        {
            ui->stackedWidget->setCurrentIndex(3);
        }
    });
    connect(ui->pushButton_mine, &QPushButton::clicked, [=](){
        ui->stackedWidget->setCurrentIndex(0);
    });

    //初始把一些radio选中以及默认值
    ui->radioButton_all->setChecked(true);
    ui->radioButton->setChecked(true);
    ui->label_from->setEnabled(false);
    ui->label_to->setEnabled(false);
    ui->dateEdit_from->setEnabled(false);
    ui->dateEdit_to->setEnabled(false);
    ui->dateEdit_from->setDate(QDate().currentDate());
    ui->dateEdit_to->setDate(QDate().currentDate());
    connect(ui->radioButton_spe, &QRadioButton::toggled, [=](){
        if(ui->radioButton_spe->isChecked() == true)
        {
            ui->label_from->setEnabled(true);
            ui->label_to->setEnabled(true);
            ui->dateEdit_from->setEnabled(true);
            ui->dateEdit_to->setEnabled(true);
        }
        else
        {
            ui->label_from->setEnabled(false);
            ui->label_to->setEnabled(false);
            ui->dateEdit_from->setEnabled(false);
            ui->dateEdit_to->setEnabled(false);
        }
    });

//    QGroupBox

    connect(ui->radioButton, &QRadioButton::toggled, [=](){
        if(ui->radioButton->isChecked() == true) airlineInit();
    });

    connect(ui->radioButton_2, &QRadioButton::toggled, [=](){
       if(ui->radioButton_2->isChecked() == true) airlineInit();
    });

    connect(ui->radioButton_3, &QRadioButton::toggled, [=](){
       if(ui->radioButton_3->isChecked() == true) airlineInit();
    });

    connect(ui->radioButton_all, &QRadioButton::toggled, [=](){
       if(ui->radioButton_all->isChecked() == true) airlineInit();
    });

    connect(ui->radioButton_his, &QRadioButton::toggled, [=](){
       if(ui->radioButton_his->isChecked() == true) airlineInit();
    });

    connect(ui->radioButton_spe, &QRadioButton::toggled, [=](){
       if(ui->radioButton_spe->isChecked() == true) airlineInit();
    });

    connect(ui->radioButton_no, &QRadioButton::toggled, [=](){
       if(ui->radioButton_no->isChecked() == true) airlineInit();
    });

    connect(ui->dateEdit_from, &QDateEdit::editingFinished, [=](){
       airlineInit();
    });

    connect(ui->dateEdit_to, &QDateEdit::editingFinished, [=](){
        airlineInit();
    });

    connect(ui->label_add, &ClickableLabel::clicked, [=](){
        AddFlightWidget *fWidget  = new AddFlightWidget();
        fWidget->setWindowModality(Qt::ApplicationModal);
        fWidget->show();
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
    orderAllInit();

    //3.我的部分
    ui->widget_3->setAdmin(admin);
}

AdminMainWidget::~AdminMainWidget()
{
    delete ui;
}


void AdminMainWidget::airlineInit()
{
    //航班信息
    QSqlTableModel *model = new QSqlTableModel(this, *db);
    model->setTable("air");
    QString qstr = QString::fromLocal8Bit(admin->Company);
//    model->setFilter("company = '" + qstr + "'");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    if(ui->radioButton->isChecked() == true)
    {
        model->setSort(14, Qt::DescendingOrder); //总人数
    }
    else if(ui->radioButton_2->isChecked() == true)
    {
        model->setSort(15, Qt::DescendingOrder); //上座率
    }
    else
    {
        model->setSort(16, Qt::DescendingOrder); //票价总收入
    }
    model->select(); //选取整个表的所有行
    model->removeColumn(0); //隐藏第1行
    model->removeColumns(18, 4); //隐藏第18 - 21行
    QDate date = QDate().currentDate();
    QTime time = QTime().currentTime();
    QString dateStr = date.toString("yyyy-MM-dd");
    QString timeStr = time.toString("hh:mm:ss");
    QString dateFrom = ui->dateEdit_from->date().toString("yyyy-MM-dd");
    QString dateTo = ui->dateEdit_to->date().toString("yyyy-MM-dd");

    if(ui->radioButton_all->isChecked() == true)
    {
        //without filter
    }
    else if(ui->radioButton_his->isChecked() == true)
    {
        qDebug() << "((date<'" + dateStr + "') OR (time_on<'" + timeStr + "' AND date='" + dateStr + "'))" + " AND company='" + qstr + "'";
        model->setFilter("((date<'" + dateStr + "') OR (time_on<'" + timeStr + "' AND date='" + dateStr + "'))" + " AND company='" + qstr + "'"); //历史
    }
    else if(ui->radioButton_no->isChecked() == true)
    {
        qDebug() << "date>'" + dateStr + "' OR (time_on>'" + timeStr + "' AND date='" + dateStr + "')" + " AND company='" + qstr + "'";
        model->setFilter("(date>'" + dateStr + "' OR (time_on>'" + timeStr + "' AND date='" + dateStr + "'))" + " AND company='" + qstr + "'"); //未来
    }
    else
    {
        qDebug() << "((date>='" + dateFrom + "') AND date<='" + dateTo + "')" + " AND company='" + qstr + "'";
        model->setFilter("((date>='" + dateFrom + "') AND date<='" + dateTo + "')" + " AND company='" + qstr + "'");
    }

    ui->tableView_order->clearSpans();
    ui->tableView_order->setModel(model);
    ui->tableView_order->show();
    QStringList strList = QStringList() << "航班号" << "始发地" << "目的地" << "航空公司" << "起飞时间" << "到达时间" << "是否跨天"
                                        << "机型" << "头等舱剩余" << "商务舱剩余" << "经济舱剩余"
                                        << "头等舱已售" << "商务舱已售" << "经济舱已售"
                                        << "已购票人数" << "上座率(%)" << "总收入" << "日期";
    for(auto i = strList.begin(); i != strList.end(); ++i)
    {
        model->setHeaderData((i - strList.begin()), Qt::Orientation::Horizontal, *i);
    }
}

void AdminMainWidget::orderInit()
{
    //订单 in 航班
    QSqlTableModel *model = new QSqlTableModel(this, *db);
    model->setTable("air");
    QString qstr = QString::fromLocal8Bit(admin->Company);
    model->setFilter("company='" + qstr + "'");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select(); //选取整个表的所有行
    model->removeColumn(0); //隐藏第1行
    model->removeColumns(8, 9); //隐藏各种上座信息
    model->removeColumn(9); //隐藏准点率
    QStringList strList = QStringList() << "航班号" << "始发地" << "目的地" << "航空公司" << "起飞时间" << "到达时间" << "是否跨天"
                                        << "机型" << "日期" << "基准价格" << "飞行员1" << "飞行员2";
    for(auto i = strList.begin(); i != strList.end(); ++i)
    {
        model->setHeaderData((i - strList.begin()), Qt::Orientation::Horizontal, *i);
    }
    ui->tableView_flight->setModel(model);
    ui->tableView_flight->show();
}

void AdminMainWidget::orderAllInit()
{
    //订单
    QSqlTableModel *model = new QSqlTableModel(this, *db);
    model->setTable("children_order");
    QString qstrOrigin = QString::fromLocal8Bit(admin->Company);
    QString qstr;
    map<QString, QString> mapAir;
    mapAir.insert(make_pair("中国国航", "CA"));
    mapAir.insert(make_pair("东方航空", "MU"));
    mapAir.insert(make_pair("首都航空", "JD"));
    mapAir.insert(make_pair("南方航空", "CZ"));
    mapAir.insert(make_pair("海南航空", "HU"));
    mapAir.insert(make_pair("河北航空", "NS"));
    mapAir.insert(make_pair("吉祥航空", "HO"));
    mapAir.insert(make_pair("山东航空", "SC"));
    mapAir.insert(make_pair("厦门航空", "MF"));
    auto iter = mapAir.find(qstrOrigin);
    if(iter != mapAir.end()) qstr = iter->second;
    qDebug() << "mapAir Find" << qstr;
    model->setFilter("com='" + qstr + "'");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select(); //选取整个表的所有行
    model->removeColumn(7); //隐藏第8行航空公司
    QStringList strList = QStringList() << "订单号" << "购买人姓名" << "航班号" << "日期" << "座位号" << "舱位(A头等舱, B商务舱, C经济舱)" << "付款金额";
    for(auto i = strList.begin(); i != strList.end(); ++i)
    {
        model->setHeaderData((i - strList.begin()), Qt::Orientation::Horizontal, *i);
    }
    ui->tableView_orderAll->setModel(model);
    ui->tableView_orderAll->show();
}
