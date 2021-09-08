#include "querywidget.h"
#include "ui_querywidget.h"

#include <QDebug>
#include <QScrollArea>
#include <QDate>
#include <QRadioButton>
#include <QMessageBox>

QueryWidget::QueryWidget(QWidget *parent, int type) : //type == 0 起降地 type == 1 航班号
    QWidget(parent),
    ui(new Ui::QueryWidget)
{
    ui->setupUi(this);


    this->setWindowTitle("航班具体信息查询界面");

    flight = new Flight();
    inq = new Inquiry();

    //隐藏航班号或起降地
    if(type == 0)
    {
        ui->label_num->hide();
        ui->lineEdit_num->hide();
    }
    else
    {
        ui->label_from->hide();
        ui->lineEdit_from->hide();
        ui->label_to->hide();
        ui->lineEdit_to->hide();
    }

    //设置scrollArea widget自动设置背景白色
    ui->scrollArea->setAutoFillBackground(true);
    ui->widget->setAutoFillBackground(true);

    //初始化背景图片
    setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(QPixmap(":/main/images/query_background.jpg")));
    setPalette(palette);

    //为筛选条件添加信息
    ui->comboBox->addItems(QStringList() << "请选择" << "中国国航" << "东方航空" << "首都航空"  \
                           << "南方航空" << "海南航空" << "河北航空" << "吉祥航空" << "山东航空" << "厦门航空");
    ui->comboBox_2->addItems(QStringList() << "请选择" << "头等舱" << "商务舱" << "经济舱");
    ui->comboBox_3->addItems(QStringList() << "请选择" << "A333E" << "B738");

    returnToNormal();

//    connect 输入框和状态更新
    connect(ui->lineEdit_from, &QLineEdit::editingFinished, [=](){
        setFromAndTo(ui->lineEdit_from->text(), ui->lineEdit_to->text(), ui->dateEdit->date());
        //恢复初始状态
        returnToNormal();
    });

    connect(ui->lineEdit_to, &QLineEdit::editingFinished, [=](){
        setFromAndTo(ui->lineEdit_from->text(), ui->lineEdit_to->text(), ui->dateEdit->date());
        //恢复初始状态
        returnToNormal();
    });

    connect(ui->lineEdit_num, &QLineEdit::editingFinished, [=](){
        setNumber(ui->lineEdit_num->text(), ui->dateEdit->date());
        //恢复初始状态
        returnToNormal();
    });

    connect(ui->dateEdit, &QDateEdit::editingFinished, [=](){
        if(type == 0)
        {
            setFromAndTo(ui->lineEdit_from->text(), ui->lineEdit_to->text(), ui->dateEdit->date());
        }
        else
        {
            setNumber(ui->lineEdit_num->text(), ui->dateEdit->date());
        }
        //恢复初始状态
        returnToNormal();
    });

    //排序
    connect(ui->radioButton_timeEarly, &QRadioButton::toggled, [=](){
        changeSortFilter();
    });

    connect(ui->radioButton_timeLate, &QRadioButton::toggled, [=](){
        changeSortFilter();
    });

    connect(ui->radioButton_priceHigh, &QRadioButton::toggled, [=](){
        changeSortFilter();
    });

    connect(ui->radioButton_priceLow, &QRadioButton::toggled, [=](){
        changeSortFilter();
    });

    //connect 筛选条件更新
    //用航空公司筛选
    connect(ui->comboBox, &QComboBox::currentTextChanged, [=](){
        changeSortFilter();
    });

    connect(ui->comboBox_2, &QComboBox::currentTextChanged, [=](QString str){
        if(str != "请选择")
        {
            QMessageBox::information(this, "提示", "所有航班均有头等舱、商务舱和经济舱，无需过滤。");
            ui->comboBox_2->setCurrentIndex(0);
        }
    });

    connect(ui->comboBox_3, &QComboBox::currentTextChanged, [=](){
        changeSortFilter();
    });

    connect(ui->timeEdit_from, &QTimeEdit::timeChanged, [=](){
        changeSortFilter();
        QTime time = ui->timeEdit_from->time();
        time.setHMS(time.hour(), 0, time.second());
        ui->timeEdit_from->setTime(time);
    });

    connect(ui->timeEdit_to, &QTimeEdit::timeChanged, [=](){
        changeSortFilter();
        QTime time = ui->timeEdit_to->time();
        time.setHMS(time.hour(), 59, time.second());
        ui->timeEdit_to->setTime(time);
    });
}

QueryWidget::~QueryWidget()
{
    delete ui;
}

void QueryWidget::setFromAndTo(QString from, QString to, QDate date)
{
    qDebug() << "setFromAndTo";
    //设置文本框内容
    ui->lineEdit_from->setText(from);
    ui->lineEdit_to->setText(to);
    ui->dateEdit->setDate(date);
    //int search(string& origin, string& destination, string& date, vector<Flight>& vec);
//    vector<Flight> flightVec;
    //转为string
    string fromStr = std::string(from.toLocal8Bit());
    string toStr = std::string(to.toLocal8Bit());
    string dateStr = std::string(date.toString("yyyy-MM-dd").toLocal8Bit());
    qDebug() << "setFromAndTo2";
    deleteFlight();
    flightVec.clear();
    inq->search(fromStr, toStr, dateStr, flightVec);
    qDebug() << "setFromAndTo3";
    addFlight(flightVec);
    qDebug() << "setFromAndTo4";
}

void QueryWidget::setNumber(QString number, QDate date)
{
    ui->lineEdit_num->setText(number);
    ui->dateEdit->setDate(date);
    //转为string
    string numberStr = std::string(number.toLocal8Bit());
    string dateStr = std::string(date.toString("yyyy-MM-dd").toLocal8Bit());
    deleteFlight();
    flightVec.clear();
    inq->search(numberStr, dateStr, flightVec);
    addFlight(flightVec);
}


//在界面中添加航班
void QueryWidget::addFlight(vector<Flight> &flightVec)
{
    int num = flightVec.size();
    if(num == 0)
    {
        ui->label->setText("暂无对应航班");
        ui->widget_end->move(100, 10);
        return;
    }
    else
    {
        ui->label->setText("已经到底了");
    }
    qDebug() << "size is" << num;
    ui->scrollArea->setWidgetResizable(false);
    //370是item宽度 10是宽度间的间隙 120是item长度 10是长度间的间隙 50是最底下多留点地
    ui->scrollAreaWidgetContents->resize((370 + 10), num * (120 + 10) + 50);
    //添加航班
    int j = 0;
    for(auto i = flightVec.begin(); i != flightVec.end(); ++i, ++j)
    {
        qDebug() << j;
        AirlinesItem *item = new AirlinesItem(ui->scrollAreaWidgetContents, &*i);
        flightWidgetVec.push_back(item);
        item->setParent(ui->scrollAreaWidgetContents);
        item->move(5, j * (120 + 10) + 10); //5让item和左边有点间隙
        item->show();
        qDebug() << item->geometry();
    }
    //改变底线标识位置
    ui->widget_end->move(100, num * (120 + 10) + 10); //100可以让底线正好到最中间
}

//在界面中删除航班
void QueryWidget::deleteFlight()
{
    for(auto i = flightWidgetVec.begin(); i != flightWidgetVec.end(); ++i)
    {
        (*i)->setParent(nullptr);
        (*i)->deleteLater();
    }
    flightWidgetVec.clear();
}

void QueryWidget::changeSortFilter()
{
    deleteFlight();

    //判断按哪一种排序方式
    if(ui->radioButton_timeEarly->isChecked() == true)
    {
        inq->sort_by_time_inc(flightVec);
    }
    else if(ui->radioButton_timeLate->isChecked() == true)
    {
        inq->sort_by_time_dec(flightVec);
    }
    else if(ui->radioButton_priceHigh->isChecked() == true)
    {
        inq->sort_by_price_dec(flightVec);
    }
    else if(ui->radioButton_priceLow->isChecked() == true)
    {
        inq->sort_by_price_inc(flightVec);
    }

    vector<Flight> flightVecTemp1, flightVecTemp2;

    //time筛选
    string from = std::to_string(ui->timeEdit_from->time().hour());
    string to = std::to_string(ui->timeEdit_to->time().hour());
    inq->filter_by_time(from, to, flightVec, flightVecTemp1);

    //航空公司筛选
    if(ui->comboBox->currentText() == "请选择")
    {
        flightVecTemp2 = flightVecTemp1;
    }
    else
    {
        string str = string(ui->comboBox->currentText().toLocal8Bit());
        inq->filter_by_company(str, flightVecTemp1, flightVecTemp2);
    }
    flightVecTemp1.clear();

    //机型筛选
    if(ui->comboBox_3->currentText() == "请选择")
    {
        flightVecTemp1 = flightVecTemp2;
    }
    else
    {
        string str = string(ui->comboBox_3->currentText().toLocal8Bit());
        inq->filter_by_model(str, flightVecTemp2, flightVecTemp1);
    }

    //

    addFlight(flightVecTemp1);
}

void QueryWidget::returnToNormal()
{
    //排序方式默认为0
    ui->radioButton_timeEarly->setChecked(true);

    //时间默认为全天
    ui->timeEdit_from->setTime(QTime(0, 0));
    ui->timeEdit_to->setTime(QTime(23, 59));

    //为筛选条件添加信息
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(0);
    ui->comboBox_3->setCurrentIndex(0);
}
