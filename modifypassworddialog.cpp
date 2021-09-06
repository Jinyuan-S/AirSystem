#include "modifypassworddialog.h"
#include "ui_modifypassworddialog.h"

#include <QMessageBox>
#include <QPushButton>
#include <QString>

ModifyPasswordDialog::ModifyPasswordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifyPasswordDialog)
{
    ui->setupUi(this);

    person = new Person();
    admin = nullptr;
    buyer = nullptr;

    ui->lineEdit_old->setText("");
    ui->lineEdit_new->setText("");
    ui->lineEdit_repeat->setText("");


    //在这里更改密码
    connect(ui->pushButton_ok, &QPushButton::clicked, [=](){
        if(admin != nullptr)
        {
            //管理员

            if(admin->Password != std::string(ui->lineEdit_old->text().toLocal8Bit()))
            {
                QMessageBox::warning(this, "修改密码", "您的原密码不正确！");
            }
            else if((ui->lineEdit_new->text().length() < 6) || (ui->lineEdit_new->text().length() > 20))
            {
                QMessageBox::warning(this, "修改密码", "密码长度必须在6-20位之间，请返回修改！");
            }
            else if(ui->lineEdit_new->text() != ui->lineEdit_repeat->text())
            {
                QMessageBox::warning(this, "修改密码", "您的新密码与重复新密码不相同！");
            }
            else
            {
                std::string passwd = (std::string)ui->lineEdit_new->text().toLocal8Bit();
                int ret = admin->change_password(passwd);
                if(ret == 0)
                {
                    person->renew(*admin);
                    QMessageBox::information(this, "修改密码", "修改密码成功！");
                    close();
                }
                else
                {
                    QMessageBox::warning(this, "修改密码", "密码长度必须在6-20位之间，请返回修改！");
                }
            }
        }
        else if(buyer != nullptr)
        {
            qDebug() << "购票用户密码修改";
            //购票用户
            if(buyer->Password != std::string(ui->lineEdit_old->text().toLocal8Bit()))
            {
                qDebug() << "不正确";
                QMessageBox::warning(this, "修改密码", "您的原密码不正确！");
            }
            else if((ui->lineEdit_new->text().length() < 6) || (ui->lineEdit_new->text().length() > 20))
            {
                qDebug() << "6-20";
                QMessageBox::warning(this, "修改密码", "密码长度必须在6-20位之间，请返回修改！");
            }
            else if(ui->lineEdit_new->text() != ui->lineEdit_repeat->text())
            {
                qDebug() << "不相同";
                QMessageBox::warning(this, "修改密码", "您的新密码与重复新密码不相同！");
            }
            else
            {
                qDebug() << "准备修改";
                std::string passwd = (std::string)ui->lineEdit_new->text().toLocal8Bit();
                qDebug() << "before";
                int ret = buyer->change_password(passwd);
                qDebug() << "after";
                if(ret == 0)
                {
                    person->renew(*buyer);
                    QMessageBox::information(this, "修改密码", "修改密码成功！");
                    close();
                }
                else
                {
                    QMessageBox::warning(this, "修改密码", "密码长度必须在6-20位之间，请返回修改！");
                }
            }
        }
    });
    connect(ui->pushButton_cancel, &QPushButton::clicked, [=](){
        close();
    });
}

ModifyPasswordDialog::~ModifyPasswordDialog()
{
    delete ui;
}

void ModifyPasswordDialog::setAdmin(Admin *adminTemp)
{
    admin = adminTemp;
    ui->label_id->setText(QString::fromLocal8Bit(admin->ID));
}

void ModifyPasswordDialog::setBuyer(Buyer *buyerTemp)
{
    buyer = buyerTemp;
    ui->label_id->setText(QString::fromLocal8Bit(buyer->ID));
    qDebug() << QString::fromLocal8Bit(buyer->Password);
}
