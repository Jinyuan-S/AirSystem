#include "mainwidgetminepart.h"
#include "ui_mainwidgetminepart.h"

#include <QMessageBox>
#include <QString>
#include <string>
using std::string;

//可用于mineWidget AdminMineWidget

MainWidgetMinePart::MainWidgetMinePart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidgetMinePart)
{
    ui->setupUi(this);
    buyer = nullptr;
    admin = nullptr;
    person = new Person();
    basicInit();
}

void MainWidgetMinePart::setBuyer(Buyer *buyerTemp)
{
    buyer = buyerTemp;
    ui->groupBox_com_2->hide();
    ui->label_userType->setText("购票用户");
    userInfoLoad(buyer);
}

void MainWidgetMinePart::setAdmin(Admin *adminTemp)
{
    admin = adminTemp;
    ui->label_userType->setText("管理员");
    ui->label_com_2->setText(QString::fromLocal8Bit(admin->Company));
    userInfoLoad(admin);
}

MainWidgetMinePart::~MainWidgetMinePart()
{
    delete ui;
}

void MainWidgetMinePart::basicInit()
{
    this->setWindowTitle("修改密码");

    //初始化为普通模式，把修改部分的都隐藏
    statusOfLabel = 0;
    ui->lineEdit_email_2->hide();
    ui->lineEdit_tele_2->hide();
    ui->label_error_email_2->hide();
    ui->label_error_tele_2->hide();
    ui->label_replace->hide();

    //1.更改信息部分

    //普通状态与修改状态的更换
    connect(ui->label_changeInfo_2, &ClickableLabel::clicked, [=](){
        if(statusOfLabel == 0)
        {
            //普通转修改
            ui->lineEdit_email_2->show();
            ui->lineEdit_tele_2->show();

            ui->label_email_2->hide();
            ui->label_tele_2->hide();

            ui->lineEdit_tele_2->setText(ui->label_tele_2->text());
            ui->lineEdit_email_2->setText(ui->label_email_2->text());

            //最开始，全部都是合法的
            isTeleLegal = 1;
            isEmailLegal = 1;

            ui->label_changePassword_2->hide();
            ui->label_changeInfo_2->setText("完成");
            ui->label_replace->show();

            statusOfLabel = 1;
        }
        else
        {
            //修改转普通
            changeToNormal();
        }
    });

    //修改信息时的具体操作

    //更改电话
    connect(ui->lineEdit_tele_2, &QLineEdit::textChanged, [=](){
        string text1 = string(ui->lineEdit_tele_2->text().toLocal8Bit());
        int ret = 3;

        //判断是admin还是buyer
        if(admin != nullptr)
        {
            ret = admin->change_tel(text1);
        }
        else if(buyer != nullptr)
        {
            ret = buyer->change_tel(text1);
        }
        else
        {
            ret = 3;
        }

        if(ret == 0)
        {
            ui->label_error_tele_2->hide();
            isTeleLegal = 1;
        }
        else if(ret == 1)
        {
            ui->label_error_tele_2->setText("电话长度应为11位！");
            ui->label_error_tele_2->show();
            isTeleLegal = 0;
        }
        else if(ret == 2)
        {
            ui->label_error_tele_2->setText("电话中含有非法字符！");
            ui->label_error_tele_2->show();
            isTeleLegal = 0;
        }
        else
        {
            ui->label_error_tele_2->setText("出现未知错误！");
            ui->label_error_tele_2->show();
            isTeleLegal = 0;
        }
    });

    //更改邮箱
    connect(ui->lineEdit_email_2, &QLineEdit::textChanged, [=](){
        string text2 = string(ui->lineEdit_email_2->text().toLocal8Bit());
        int ret = 2;

        //判断是admin还是buyer
        if(admin != nullptr)
        {
            ret = admin->change_email(text2);
        }
        else if(buyer != nullptr)
        {
            ret = buyer->change_email(text2);
        }
        else
        {
            ret = 2;
        }

        if(ret == 0)
        {
            ui->label_error_email_2->hide();
            isEmailLegal = 1;
        }
        else if(ret == 1)
        {
            ui->label_error_email_2->setText("邮箱格式不合法！");
            ui->label_error_email_2->show();
            isEmailLegal = 0;
        }
        else
        {
            ui->label_error_email_2->setText("出现未知错误！");
            ui->label_error_email_2->show();
            isEmailLegal = 0;
        }
    });

    //复原按钮
    connect(ui->label_replace, &ClickableLabel::clicked, [=](){
        ui->lineEdit_tele_2->setText(ui->label_tele_2->text());
        ui->lineEdit_email_2->setText(ui->label_email_2->text());
    });

    //2.修改密码部分
    connect(ui->label_changePassword_2, &ClickableLabel::clicked, [=](){
        passwordDialog = new ModifyPasswordDialog();
        if(admin != nullptr)
        {
            passwordDialog->setAdmin(admin);
        }
        else if(buyer != nullptr)
        {
            passwordDialog->setBuyer(buyer);
        }
        passwordDialog->exec();
    });
}

void MainWidgetMinePart::userInfoLoad(Buyer *user)
{
    //设置用户信息
    ui->label_id_2->setText(QString::fromLocal8Bit(user->ID));
    ui->label_name_2->setText(QString::fromLocal8Bit(user->Name));
    ui->label_gender_2->setText(QString::fromLocal8Bit(user->Gender));
    ui->label_tele_2->setText(QString::fromLocal8Bit(user->Tel));
    ui->label_email_2->setText(QString::fromLocal8Bit(user->Email));
}

//true表示可以切换 false表示不可以切换
bool MainWidgetMinePart::changeToNormal()
{
    //如果是普通状态调用直接返回
    if(statusOfLabel == 0) return true;

    //修改转普通
    if(isTeleLegal && isEmailLegal)
    {
        //信息是合法的情况
        if(QMessageBox::Ok
                == QMessageBox::question(this, "信息更改", "您确定要保存您更改的个人信息吗？", QMessageBox::Ok|QMessageBox::Cancel))
        {
            //确认修改信息并提交
            if(admin != nullptr)
            {
                qDebug() << QString::fromLocal8Bit(admin->Tel);
                person->renew(*admin);
            }
            else if(buyer != nullptr)
            {
                qDebug() << QString::fromLocal8Bit(buyer->Tel);
                qDebug() << QString::fromLocal8Bit(buyer->Email);
                person->renew(*buyer);
            }
            //修改普通状态下label信息
            ui->label_tele_2->setText(ui->lineEdit_tele_2->text());
            ui->label_email_2->setText(ui->lineEdit_email_2->text());

            //恢复普通状态原状
            ui->lineEdit_email_2->hide();
            ui->lineEdit_tele_2->hide();

            ui->label_error_email_2->hide();
            ui->label_error_tele_2->hide();

            ui->label_email_2->show();
            ui->label_tele_2->show();

            ui->label_changePassword_2->show();
            ui->label_replace->hide();
            ui->label_changeInfo_2->setText("更改信息 >");

            statusOfLabel = 0;
        }
        else
        {
            cancleInfoChange(); //取消修改
        }
        return true;
    }
    else
    {
        if(QMessageBox::Ok
                == QMessageBox::question(this, "信息更改", "您新添加的信息有误，您是否要放弃修改？", QMessageBox::Ok|QMessageBox::Cancel))
        {
            cancleInfoChange(); //取消修改
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

void MainWidgetMinePart::cancleInfoChange()
{
    //取消修改
    //恢复之前的电话和邮箱
    if(admin != nullptr)
    {
        admin->Tel = ui->label_tele_2->text().toLocal8Bit();
        admin->Email =  ui->label_email_2->text().toLocal8Bit();
    }
    else if(buyer != nullptr)
    {
        buyer->Tel = ui->label_tele_2->text().toLocal8Bit();
        buyer->Email =  ui->label_email_2->text().toLocal8Bit();
    }

    //恢复普通状态原状
    ui->lineEdit_email_2->hide();
    ui->lineEdit_tele_2->hide();

    ui->label_error_email_2->hide();
    ui->label_error_tele_2->hide();

    ui->label_email_2->show();
    ui->label_tele_2->show();

    ui->label_changePassword_2->show();
    ui->label_replace->hide();
    ui->label_changeInfo_2->setText("更改信息 >");

    statusOfLabel = 0;
}
