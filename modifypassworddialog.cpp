#include "modifypassworddialog.h"
#include "ui_modifypassworddialog.h"

#include <QMessageBox>
#include <QPushButton>

ModifyPasswordDialog::ModifyPasswordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifyPasswordDialog)
{
    ui->setupUi(this);



    ui->lineEdit_old->setText("");
    ui->lineEdit_new->setText("");
    ui->lineEdit_repeat->setText("");

    //在这里更改密码
    connect(ui->pushButton_ok, &QPushButton::clicked, [=](){
        //TODO: 判断原密码是否正确 新密码与确认密码是否相同
        if(0/*TODO: 原密码是否正确*/)
        {

        }
        else if(ui->lineEdit_new->text() != ui->lineEdit_repeat->text())
        {
            QMessageBox::critical(this, "修改密码", "您的新密码与重复新密码不相同！");
        }
        else
        {
            QMessageBox::information(this, "修改密码", "修改密码成功！");
            close();
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
