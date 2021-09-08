#include "buyaddpersondialog.h"
#include "ui_buyaddpersondialog.h"
#include <QString>
#include <string>
#include <QMessageBox>
using std::string;
using std::stoi;

BuyAddPersonDialog::BuyAddPersonDialog(QWidget *parent, Flight flight, string cabin) :
    QDialog(parent),
    ui(new Ui::BuyAddPersonDialog)
{
    ui->setupUi(this);

    setWindowTitle("选座");


    ui->label_airline->setText("机型:" + QString::fromLocal8Bit(flight.Model));
    ui->label_num->setText("1");
    for(int i = 2; i <= 5; ++i) hidePerson(i);

    //判断机型以填充comboBox
    int flightTypeNum = 0;
    if(flight.Model == "A333E")
    {
        flightTypeNum = 0;
    }
    else
    {
        flightTypeNum = 1;
    }

    //填充comboBox
    if(cabin == "A")
    {
        comboBoxAddA(ui->comboBox_2, flightTypeNum);
        comboBoxAddA(ui->comboBox_3, flightTypeNum);
        comboBoxAddA(ui->comboBox_4, flightTypeNum);
        comboBoxAddA(ui->comboBox_5, flightTypeNum);
        comboBoxAddA(ui->comboBox_6, flightTypeNum);
    }
    else if(cabin == "B")
    {
        comboBoxAddB(ui->comboBox_2, flightTypeNum);
        comboBoxAddB(ui->comboBox_3, flightTypeNum);
        comboBoxAddB(ui->comboBox_4, flightTypeNum);
        comboBoxAddB(ui->comboBox_5, flightTypeNum);
        comboBoxAddB(ui->comboBox_6, flightTypeNum);
    }
    else
    {
        comboBoxAddC(ui->comboBox_2, flightTypeNum);
        comboBoxAddC(ui->comboBox_3, flightTypeNum);
        comboBoxAddC(ui->comboBox_4, flightTypeNum);
        comboBoxAddC(ui->comboBox_5, flightTypeNum);
        comboBoxAddC(ui->comboBox_6, flightTypeNum);
    }

    connect(ui->label_down, &ClickableLabel::clicked, [=](){
        if(ui->label_num->text() != "1")
        {
            int num = stoi((string)(ui->label_num->text().toLocal8Bit()));
            qDebug() << "decrease from" << num;
            ui->label_num->setText(QString::number(num - 1));
            qDebug() << "to" << ui->label_num->text();
            hidePerson(num);
        }
    });

    connect(ui->label_up, &ClickableLabel::clicked, [=](){
        if(ui->label_num->text() != "5")
        {
            int num = stoi((string)(ui->label_num->text().toLocal8Bit()));
            qDebug() << "increase from" << num;
            ui->label_num->setText(QString::number(num + 1));
            qDebug() << "to" << ui->label_num->text();
            showPerson(num + 1);
        }
    });

    connect(ui->pushButton, &QPushButton::clicked, [=](){
        //0 正常, 1 没有选座, 2 选座冲突, 3 没填姓名, 4 姓名冲突
        int ret = repeatInFive();
        if(ret == 1)
        {
             QMessageBox::warning(this, "订单购买", "您有乘客没有选座，请返回重选或减少乘客！");
        }
        else if(ret == 2)
        {
            QMessageBox::warning(this, "订单购买", "您的选座重复，请返回修改！");
        }
        else if(ret == 3)
        {
            QMessageBox::warning(this, "订单购买", "您有乘客没有填写姓名，请返回填写或减少乘客！");
        }
        else if(ret == 4)
        {
            QMessageBox::warning(this, "订单购买", "您有乘客姓名重复，请返回修改！");
        }
        else
        {
            if(QMessageBox::Ok
                    == QMessageBox::question(this, "订单购买", "确认要添加这些乘客并添加至购物车吗？", QMessageBox::Ok | QMessageBox::Cancel))
            {

                int num = ui->label_num->text().toInt();
                vector<string> personV;
                vector<string> seatV;
                for(int i = 1; i <= num; ++i)
                {
                    personV.push_back(getNameOrSeat(i, 0));
                    seatV.push_back(getNameOrSeat(i, 1));
                }
                emit addedPerson(personV, seatV);
                qDebug() << "BuyDialog Close And Signals Emit!";
                close();
                QMessageBox::information(this, "订单购买", "添加成功！请到购物车中结算。");
            }
        }

    });

}

BuyAddPersonDialog::~BuyAddPersonDialog()
{
    delete ui;
}


void BuyAddPersonDialog::hidePerson(int row)
{
    if(row == 1)
    {
        ui->comboBox_2->hide();
        ui->label_2->hide();
        ui->label_2_2->hide();
        ui->lineEdit_2->hide();
    }
    else if(row == 2)
    {
        ui->comboBox_3->hide();
        ui->label_3->hide();
        ui->label_3_2->hide();
        ui->lineEdit_3->hide();
    }
    else if(row == 3)
    {
        ui->comboBox_4->hide();
        ui->label_4->hide();
        ui->label_4_2->hide();
        ui->lineEdit_4->hide();
    }
    else if(row == 4)
    {
        ui->comboBox_5->hide();
        ui->label_5->hide();
        ui->label_5_2->hide();
        ui->lineEdit_5->hide();
    }
    else if(row == 5)
    {
        ui->comboBox_6->hide();
        ui->label_6->hide();
        ui->label_6_2->hide();
        ui->lineEdit_6->hide();
    }
}

void BuyAddPersonDialog::showPerson(int row)
{
    if(row == 1)
    {
        ui->comboBox_2->show();
        ui->label_2->show();
        ui->label_2_2->show();
        ui->lineEdit_2->show();
    }
    else if(row == 2)
    {
        ui->comboBox_3->show();
        ui->label_3->show();
        ui->label_3_2->show();
        ui->lineEdit_3->show();
    }
    else if(row == 3)
    {
        ui->comboBox_4->show();
        ui->label_4->show();
        ui->label_4_2->show();
        ui->lineEdit_4->show();
    }
    else if(row == 4)
    {
        ui->comboBox_5->show();
        ui->label_5->show();
        ui->label_5_2->show();
        ui->lineEdit_5->show();
    }
    else if(row == 5)
    {
        ui->comboBox_6->show();
        ui->label_6->show();
        ui->label_6_2->show();
        ui->lineEdit_6->show();
    }
}

string BuyAddPersonDialog::getNameOrSeat(int num, int type)
{
    //type 0 姓名, 1 座位
    if(type == 0)
    {
        if(num == 1)
        {
            return string(ui->lineEdit_2->text().toLocal8Bit());
        }
        else if(num == 2)
        {
            return string(ui->lineEdit_3->text().toLocal8Bit());
        }
        else if(num == 3)
        {
            return string(ui->lineEdit_4->text().toLocal8Bit());
        }
        else if(num == 4)
        {
            return string(ui->lineEdit_5->text().toLocal8Bit());
        }
        else if(num == 5)
        {
            return string(ui->lineEdit_6->text().toLocal8Bit());
        }
    }
    else
    {
        if(num == 1)
        {
            return string(ui->comboBox_2->currentText().toLocal8Bit());
        }
        else if(num == 2)
        {
            return string(ui->comboBox_3->currentText().toLocal8Bit());
        }
        else if(num == 3)
        {
            return string(ui->comboBox_4->currentText().toLocal8Bit());
        }
        else if(num == 4)
        {
            return string(ui->comboBox_5->currentText().toLocal8Bit());
        }
        else if(num == 5)
        {
            return string(ui->comboBox_6->currentText().toLocal8Bit());
        }
    }
    return "";
}

void BuyAddPersonDialog::comboBoxAddA(QComboBox *cBox, int type) //type 0 空客, 1 波音
{
    QStringList strList;
    if(type == 0)
    {
        strList = QStringList() << "请选择" << "11A" << "11C" << "11D" << "11H" << "11J" << "11L"  <<
                                   "12A" << "12C" << "12D" << "12H" << "12J" << "12L";
    }
    else
    {
        strList = QStringList() << "请选择" << "6A" << "6C" << "6J" << "6L" <<
                                   "7A" << "7C" << "7J" << "7L";
    }
    cBox->addItems(strList);
}

void BuyAddPersonDialog::comboBoxAddB(QComboBox *cBox, int type)
{
    QStringList strList;
    if(type == 0)
    {
        strList = QStringList() << "请选择" << "13A" << "13C" << "13D" << "13H" << "13J" << "13L" <<
                                   "14A" << "14C" << "14D" << "14H" << "14J" << "14L" <<
                                   "15A" << "15C" << "15D" << "15H" << "15J" << "15L";
    }
    else
    {
        strList = QStringList() << "请选择" << "25A" << "25B" << "25C" << "25J" << "25K" << "25L"  <<
                                   "26A" << "26B" << "26C" << "26J" << "26K" << "26L" <<
                                   "27A" << "27B" << "27C" << "27J" << "27K" << "27L";
    }
    cBox->addItems(strList);
}

void BuyAddPersonDialog::comboBoxAddC(QComboBox *cBox, int type)
{
    QStringList strList;
    if(type == 0)
    {
        strList = QStringList() <<"请选择" <<"31A"<<"31C"<<"31D"<<"31E"<<"31F"<<"31H"<<"31J"<<"31L"<<
                                        "32A"<<"32C"<<"32D"<<"32E"<<"32F"<<"32H"<<"32J"<<"32L"<<
                                        "33A"<<"33C"<<"33D"<<"33E"<<"33F"<<"33H"<<"33J"<<"33L"<<
                                        "34A"<<"34C"<<"34D"<<"34E"<<"34F"<<"34H"<<"34J"<<"34L"<<
                                        "35A"<<"35C"<<"35D"<<"35E"<<"35F"<<"35H"<<"35J"<<"35L"<<
                                        "36A"<<"36C"<<"36D"<<"36E"<<"36F"<<"36H"<<"36J"<<"36L"<<
                                        "37A"<<"37C"<<"37D"<<"37E"<<"37F"<<"37H"<<"37J"<<"37L"<<
                                        "38A"<<"38C"<<"38D"<<"38E"<<"38F"<<"38H"<<"38J"<<"38L"<<
                                        "39A"<<"39C"<<"39D"<<"39E"<<"39F"<<"39H"<<"39J"<<"39L"<<
                                        "40A"<<"40C"<<"40D"<<"40E"<<"40F"<<"40H"<<"40J"<<"40L"<<
                                        "41A"<<"41C"<<"41D"<<"41E"<<"41F"<<"41H"<<"41J"<<"41L"<<
                                        "42A"<<"42C"<<"42D"<<"42E"<<"42F"<<"42H"<<"42J"<<"42L"<<
                                        "43A"<<"43C"<<"43D"<<"43E"<<"43F"<<"43H"<<"43J"<<"43L"<<
                                        "44A"<<"44C"<<"44D"<<"44E"<<"44F"<<"44H"<<"44J"<<"44L"<<
                                        "45A"<<"45C"<<"45D"<<"45E"<<"45F"<<"45H"<<"45J"<<"45L"<<
                                        "46A"<<"46C"<<"46D"<<"46E"<<"46F"<<"46H"<<"46J"<<"46L"<<
                                        "47A"<<"47C"<<"47D"<<"47E"<<"47F"<<"47H"<<"47J"<<"47L"<<
                                        "48A"<<"48C"<<"48D"<<"48E"<<"48F"<<"48H"<<"48J"<<"48L"<<
                                        "49A"<<"49C"<<"49D"<<"49E"<<"49F"<<"49H"<<"49J"<<"49L"<<
                                        "50A"<<"50C"<<"50D"<<"50E"<<"50F"<<"50H"<<"50J"<<"50L"<<
                                        "51A"<<"51C"<<"51D"<<"51E"<<"51F"<<"51H"<<"51J"<<"51L"<<
                                        "52A"<<"52C"<<"52D"<<"52E"<<"52F"<<"52H"<<"52J"<<"52L"<<
                                        "53A"<<"53C"<<"53D"<<"53E"<<"53F"<<"53H"<<"53J"<<"53L"<<
                                        "54A"<<"54C"<<"54D"<<"54E"<<"54F"<<"54H"<<"54J"<<"54L"<<
                                        "55A"<<"55C"<<"55D"<<"55E"<<"55F"<<"55H"<<"55J"<<"55L"<<
                                        "56A"<<"56C"<<"56D"<<"56E"<<"56F"<<"56H"<<"56J"<<"56L"<<
                                        "57A"<<"57C"<<"57D"<<"57E"<<"57F"<<"57H"<<"57J"<<"57L"<<
                                        "58A"<<"58C"<<"58D"<<"58E"<<"58F"<<"58H"<<"58J"<<"58L"<<
                                        "59A"<<"59C"<<"59D"<<"59E"<<"59F"<<"59H"<<"59J"<<"59L"<<
                                        "60A"<<"60C"<<"60D"<<"60E"<<"60F"<<"60H"<<"60J"<<"60L"<<
                                        "61A"<<"61C"<<"61D"<<"61E"<<"61F"<<"61H"<<"61J"<<"61L"<<
                                        "62A"<<"62C"<<"62D"<<"62E"<<"62F"<<"62H"<<"62J"<<"62L"<<
                                        "63A"<<"63C"<<"63D"<<"63E"<<"63F"<<"63H"<<"63J"<<"63L"<<
                                        "64A"<<"64C"<<"64D"<<"64E"<<"64F"<<"64H"<<"64J"<<"64L";
    }
    else
    {
        strList = QStringList() << "请选择" << "31A" << "31B" << "31C" << "31J" << "31K" << "31L" <<
        "32A" << "32B" << "32C" << "32J" << "32K" << "32L" <<
        "33A" << "33B" << "33C" << "33J" << "33K" << "33L" <<
        "34A" << "34B" << "34C" << "34J" << "34K" << "34L" <<
        "35A" << "35B" << "35C" << "35J" << "35K" << "35L" <<
        "36A" << "36B" << "36C" << "36J" << "36K" << "36L" <<
        "37A" << "37B" << "37C" << "37J" << "37K" << "37L" <<
        "38A" << "38B" << "38C" << "38J" << "38K" << "38L" <<
        "39A" << "39B" << "39C" << "39J" << "39K" << "39L" <<
        "40A" << "40B" << "40C" << "40J" << "40K" << "40L" <<
        "41A" << "41B" << "41C" << "41J" << "41K" << "41L" <<
        "42A" << "42B" << "42C" << "42J" << "42K" << "42L" <<
        "43A" << "43B" << "43C" << "43J" << "43K" << "43L" <<
        "44A" << "44B" << "44C" << "44J" << "44K" << "44L" <<
        "45A" << "45B" << "45C" << "45J" << "45K" << "45L" <<
        "46A" << "46B" << "46C" << "46J" << "46K" << "46L" <<
        "47A" << "47B" << "47C" << "47J" << "47K" << "47L" <<
        "48A" << "48B" << "48C" << "48J" << "48K" << "48L" <<
        "49A" << "49B" << "49C" << "49J" << "49K" << "49L" <<
        "50A" << "50B" << "50C" << "50J" << "50K" << "50L" <<
        "51A" << "51B" << "51C" << "51J" << "51K" << "51L" <<
        "52A" << "52B" << "52C" << "52J" << "52K" << "52L";
    }
    cBox->addItems(strList);
}

//0 正常, 1 没有选座, 2 选座冲突, 3 没填姓名, 4 姓名冲突
int BuyAddPersonDialog::repeatInFive()
{
    int totalNum = ui->label_num->text().toInt();

    if(totalNum >= 1 && ui->lineEdit_2->text() == "") return 3;
    if(totalNum >= 2 && ui->lineEdit_3->text() == "") return 3;
    if(totalNum >= 3 && ui->lineEdit_4->text() == "") return 3;
    if(totalNum >= 4 && ui->lineEdit_5->text() == "") return 3;
    if(totalNum >= 5 && ui->lineEdit_6->text() == "") return 3;

    if(totalNum >= 1 && ui->comboBox_2->currentIndex() == 0) return 1;
    if(totalNum >= 2 && ui->comboBox_3->currentIndex() == 0) return 1;
    if(totalNum >= 3 && ui->comboBox_4->currentIndex() == 0) return 1;
    if(totalNum >= 4 && ui->comboBox_5->currentIndex() == 0) return 1;
    if(totalNum >= 5 && ui->comboBox_6->currentIndex() == 0) return 1;
    vector<QString> repeatStr;
    vector<QString> repeatNameStr;
    if(totalNum >= 1) repeatStr.push_back(ui->comboBox_2->currentText()), repeatNameStr.push_back(ui->lineEdit_2->text());
    if(totalNum >= 2) repeatStr.push_back(ui->comboBox_3->currentText()), repeatNameStr.push_back(ui->lineEdit_3->text());
    if(totalNum >= 3) repeatStr.push_back(ui->comboBox_4->currentText()), repeatNameStr.push_back(ui->lineEdit_4->text());
    if(totalNum >= 4) repeatStr.push_back(ui->comboBox_5->currentText()), repeatNameStr.push_back(ui->lineEdit_5->text());
    if(totalNum >= 5) repeatStr.push_back(ui->comboBox_6->currentText()), repeatNameStr.push_back(ui->lineEdit_6->text());
    sort(repeatStr.begin(), repeatStr.end());
    sort(repeatNameStr.begin(), repeatNameStr.end());
    repeatStr.erase(unique(repeatStr.begin(), repeatStr.end()), repeatStr.end());
    repeatNameStr.erase(unique(repeatNameStr.begin(), repeatNameStr.end()), repeatNameStr.end());
    if((int)repeatStr.size() != totalNum) return 2;
    else if((int)repeatNameStr.size() != totalNum) return 4;
    else return 0;
}
