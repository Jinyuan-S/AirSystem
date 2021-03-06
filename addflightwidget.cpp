#include "addflightwidget.h"
#include "ui_addflightwidget.h"
#include <QStringList>
#include <map>
#include <utility>
using std::map;
using std::make_pair;

AddFlightWidget::AddFlightWidget(QWidget *parent, QString company) :
    QWidget(parent),
    ui(new Ui::AddFlightWidget)
{
    ui->setupUi(this);
    ui->comboBox_com->addItems(QStringList() << "请选择" << company);
    ui->comboBox_model->addItems(QStringList() << "请选择" << "A333E" << "B738");
    ui->comboBox_tom->addItems(QStringList() << "请选择" << "0" << "1");
    QStringList qStr1 = QStringList() << "请选择" << "傅岩" <<
                                         "洪春静" <<
                                         "闵政" <<
                                         "谭明凯" <<
                                         "唐哲" <<
                                         "莫成会" <<
                                         "薛国" <<
                                         "章淑" <<
                                         "陆飞" <<
                                         "卢叶黛" <<
                                         "庄先有";
    QStringList qStr2 = QStringList() << "请选择" << "詹鹏" <<
                                         "路东安" <<
                                         "贺启" <<
                                         "聂厚宝" <<
                                         "曲爱" <<
                                         "傅功" <<
                                         "程会" <<
                                         "向菊" <<
                                         "柴雪香" <<
                                         "卜英莉" <<
                                         "詹淑" <<
                                         "邱康奇";
    ui->comboBox_pilot1->addItems(qStr1);
    ui->comboBox_pilot2->addItems(qStr2);
    ui->dateEdit->setDate(QDate().currentDate());

    connect(ui->pushButton_save, &QPushButton::clicked, [=]()
    {
        emit saved();
    });
    connect(ui->pushButton_commit, &QPushButton::clicked, [=]()
    {
        emit commited();
    });
}

AddFlightWidget::~AddFlightWidget()
{
    delete ui;
}

void AddFlightWidget::setFlight(Flight *flight)
{
    ui->lineEdit_from->setText(QString::fromLocal8Bit(flight->Origin));
    ui->lineEdit_to->setText(QString::fromLocal8Bit(flight->Destination));
    ui->lineEdit_num->setText(QString::fromLocal8Bit(flight->Airline));
    ui->dateEdit->setDate(QDate().fromString(QString::fromLocal8Bit(flight->Date), "yyyy-MM-dd"));
    ui->timeEdit_from->setTime(QTime().fromString(QString::fromLocal8Bit(flight->Time_on), "hh:mm:ss"));
    ui->timeEdit_to->setTime(QTime().fromString(QString::fromLocal8Bit(flight->Time_off), "hh:mm:ss"));
    ui->comboBox_com->setCurrentText(QString::fromLocal8Bit(flight->Company));
    ui->comboBox_model->setCurrentText(QString::fromLocal8Bit(flight->Model));
    ui->comboBox_tom->setCurrentText(QString::fromLocal8Bit(flight->Tomorrow));
    ui->comboBox_pilot1->setCurrentText(QString::fromLocal8Bit(flight->Pilot1));
    ui->comboBox_pilot2->setCurrentText(QString::fromLocal8Bit(flight->Pilot2));
    ui->lineEdit_price->setText(QString::fromLocal8Bit(flight->Price));
}

bool AddFlightWidget::saveFlight(Flight &flight)
{
    if(ui->lineEdit_from->text() == "") return false;
    if(ui->lineEdit_to->text() == "") return false;
    if(ui->lineEdit_num->text() == "") return false;
    if(ui->comboBox_com->currentIndex() == 0) return false;
    if(ui->comboBox_model->currentIndex() == 0) return false;
    if(ui->comboBox_tom->currentIndex() == 0) return false;
    if(ui->comboBox_pilot1->currentIndex() == 0) return false;
    if(ui->comboBox_pilot2->currentIndex() == 0) return false;
    if(ui->comboBox_pilot1->currentText() == ui->comboBox_pilot2->currentText()) return false;
    if(ui->lineEdit_price->text() == "") return false;
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
    if(mapAir.find(ui->comboBox_com->currentText())->second
            != QString::fromLocal8Bit(string(ui->lineEdit_num->text().toLocal8Bit()).substr(0, 2)))
        return false;
    flight.Origin = ui->lineEdit_from->text().toLocal8Bit();
    flight.Destination = ui->lineEdit_to->text().toLocal8Bit();
    flight.Airline = ui->lineEdit_num->text().toLocal8Bit();
    flight.Date = ui->dateEdit->date().toString("yyyy-MM-dd").toLocal8Bit();
    flight.Time_on = ui->timeEdit_from->time().toString("hh:mm:ss").toLocal8Bit();
    flight.Time_off = ui->timeEdit_to->time().toString("hh:mm:ss").toLocal8Bit();
    flight.Company = ui->comboBox_com->currentText().toLocal8Bit();
    flight.Model = ui->comboBox_model->currentText().toLocal8Bit();
    flight.Tomorrow = ui->comboBox_tom->currentText().toLocal8Bit();
    flight.Pilot1 = ui->comboBox_pilot1->currentText().toLocal8Bit();
    flight.Pilot2 = ui->comboBox_pilot2->currentText().toLocal8Bit();
    flight.Price =  ui->lineEdit_price->text().toLocal8Bit();
    flight.A_remain = "10";
    flight.B_remain = "10";
    flight.C_remain = "10";
    return true;
}
