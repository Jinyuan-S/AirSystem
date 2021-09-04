#include "mainwidgetminepart.h"
#include "ui_mainwidgetminepart.h"

#include <QMessageBox>

//可用于mineWidget AdminMineWidget

MainWidgetMinePart::MainWidgetMinePart(QWidget *parent, int userType) :
    QWidget(parent),
    ui(new Ui::MainWidgetMinePart)
{
    ui->setupUi(this);

    this->setWindowTitle("修改密码");

    //初始化把修改部分的都隐藏
    ui->lineEdit_email_2->hide();
    ui->lineEdit_tele_2->hide();


    //TODO: 加载用户信息


    //1.更改信息部分

    //普通状态与修改状态的更换
    connect(ui->label_changeInfo_2, &ClickableLabel::clicked, [=](){
        static int statusOfLabel = 0; // 0为正常状态 1为未修改状态

        if(statusOfLabel == 0)
        {
            ui->lineEdit_email_2->show();
            ui->lineEdit_tele_2->show();

            ui->label_email_2->hide();
            ui->label_tele_2->hide();

            ui->lineEdit_tele_2->setText(ui->label_tele_2->text());
            ui->lineEdit_email_2->setText(ui->label_email_2->text());

            ui->label_changePassword_2->hide();
            ui->label_changeInfo_2->setText("完成");

            statusOfLabel = 1;
        }
        else
        {
            if(QMessageBox::Ok == QMessageBox::question(this, "信息更改", "您确定要保存您更改的个人信息吗？", QMessageBox::Ok|QMessageBox::Cancel))
            {
                //TODO: 检测用户输入信息是否正确
                ui->label_tele_2->setText(ui->lineEdit_tele_2->text());
                ui->label_email_2->setText(ui->lineEdit_email_2->text());
            }

            ui->lineEdit_email_2->hide();
            ui->lineEdit_tele_2->hide();

            ui->label_email_2->show();
            ui->label_tele_2->show();

            ui->label_changePassword_2->show();
            ui->label_changeInfo_2->setText("更改信息 >");

            statusOfLabel = 0;
        }
    });

    //2.修改密码部分

    connect(ui->label_changePassword_2, &ClickableLabel::clicked, [=](){
        passwordDialog = new ModifyPasswordDialog();
        passwordDialog->exec();
    });
}

MainWidgetMinePart::~MainWidgetMinePart()
{
    delete ui;
}

void MainWidgetMinePart::setUserType(int userType)
{
    //当用户类型为购票用户时，将航空公司隐藏
    //0是用户 1是管理员 2是修改密码时
    if(userType == 0) //TODO:判断是用户还是管理员
    {
        ui->groupBox_com_2->hide();
    }
    else if(userType == 2)
    {

    }
}
