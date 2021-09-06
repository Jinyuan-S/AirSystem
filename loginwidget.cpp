#include "loginwidget.h"
#include "ui_loginwidget.h"
#include "mainwidget.h"
#include "adminmainwidget.h"
#include <QLabel>
#include <QStackedWidget>
#include <QPixmap>
#include <QDebug>
#include <QPalette>
#include <QMessageBox>
#include "Database.h"
#include <vector>
#include <string>
//#include "Person.h"
using namespace std;

LoginWidget::LoginWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    basicInit();
    pushedInit();
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

//基础初始化
void LoginWidget::basicInit()
{
    //初始化时固定大小
    setFixedSize(400, 600);

    //初始化时设置标题
    setWindowTitle("登录界面");

    setWindowIcon(QIcon(":/general/images/logo.jfif"));

    //初始时进入登录界面
    ui->stackedWidget->setCurrentIndex(0);


    //初始化背景图片
    setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(QPixmap(":/loginWidget/images/login_background.jpg")));
    setPalette(palette);

    //初始化stackedWidget颜色
    ui->stackedWidget->setAutoFillBackground(true);

    //初始化comboBox
    ui->comboBox_type->addItems(QStringList() << "用户" << "管理员");
    ui->comboBox_type_signup->addItems(QStringList() << "用户" << "管理员");

    //初始化隐藏注册界面有误提示
    ui->label_error_id->hide();
    ui->label_error_password->hide();
    ui->label_error_passwordRepeat->hide();
    ui->label_error_tele->hide();
    ui->label_error_email->hide();
}

//交互界面初始化
//pushed意思是可以被按下的按钮,label等(随便起的名字)
void LoginWidget::pushedInit()
{
    //在注册和登录之间切换的相关-------

    //当在登录界面点击注册时，转入注册界面
    connect(ui->label_toSignup, &ClickableLabel::clicked, [=](){
        ui->stackedWidget->setCurrentIndex(1);  //转入注册界面
        ui->lineEdit_id->setText(ui->lineEdit->text()); //把ID复制过去
        ui->lineEdit_2->setText(""); //把这里的密码清空
    });

    //当在注册界面点击我已经有账号时，转入登录界面
    connect(ui->label_toLogin, &ClickableLabel::clicked, [=](){
        ui->stackedWidget->setCurrentIndex(0);  //转入登录界面
        ui->lineEdit->setText(ui->lineEdit_id->text()); //把ID复制过去
        ui->lineEdit_password->setText(""); //把这里的密码清空
        ui->lineEdit_repeat->setText(""); //把这里的重复密码清空
        //隐藏和密码相关的错误提示
        ui->label_error_password->hide();
        ui->label_error_passwordRepeat->hide();
    });

    //注册和登录之间切换相关结束------
    loginPushedInit();
    signupPushedInit();
}

//交互界面登录部分初始化
void LoginWidget::loginPushedInit()
{
    //当在登录界面完成登录后，进入主界面或者向用户报告错误
    connect(ui->pushButton_loginComplete, &QPushButton::clicked, this, &LoginWidget::loginComplete);
}

//交互界面注册部分初始化
void LoginWidget::signupPushedInit()
{
    //初始时为购票用户，隐藏航空公司
    ui->comboBox_type_signup->setCurrentIndex(0);
    ui->label_airlines->setEnabled(false);
    ui->comboBox_airlines->setEnabled(false);

    //当在注册界面切换用户类型时，所属航空公司出现或隐藏
    connect(ui->comboBox_type_signup, &QComboBox::currentTextChanged, [=](QString text){
        qDebug() << text;
        if(text == "管理员")
        {
            ui->label_airlines->setEnabled(true);
            ui->comboBox_airlines->setEnabled(true);
        }
        else
        {
            ui->label_airlines->setEnabled(false);
            ui->comboBox_airlines->setEnabled(false);
        }
    });

    //在注册界面当输入框结束输入时，判定输入是否合法

    //TODO: ID是否合法
    connect(ui->lineEdit_id, &QLineEdit::editingFinished, [=](){
        if(1)
        {

        }
        else
        {

        }
    });

    //TODO: 密码是否合法
    connect(ui->lineEdit_password, &QLineEdit::editingFinished, [=](){
        if(1)
        {

        }
        else
        {

        }
    });

    //密码和确认密码是否相同
    connect(ui->lineEdit_repeat, &QLineEdit::editingFinished, [=](){
        if((ui->lineEdit_password->text() == ui->lineEdit_repeat->text())
                || (ui->lineEdit_password->text() == ""))
        {
            ui->label_error_passwordRepeat->hide();
        }
        else
        {
            ui->label_error_passwordRepeat->show();
        }
    });

    //密码被更改后和确认密码一样就把错误信息隐藏
    connect(ui->lineEdit_password, &QLineEdit::editingFinished, [=](){
        if(ui->lineEdit_password->text() == ui->lineEdit_repeat->text())
        {
            ui->label_error_passwordRepeat->hide();
        }
    });

    //TODO: 电话是否合法
    connect(ui->lineEdit_tele, &QLineEdit::editingFinished, [=](){

    });

    //TODO: 邮箱是否合法
    connect(ui->lineEdit_email, &QLineEdit::editingFinished, [=](){

    });

    //当在注册界面完成注册后，回到登录界面或向用户报告错误
    connect(ui->pushButton_signupComplete, &QPushButton::clicked, this, &LoginWidget::signupComplete);
}


//登录完成的槽函数
void LoginWidget::loginComplete()
{
    if(1) //TODO: 判断用户输入的用户名和密码是否正确
    {
        if(ui->comboBox_type->currentText() == "管理员")
        {
            AdminMainWidget *adminMainW = new AdminMainWidget();
            adminMainW->show();
        }
        else
        {
            MainWidget *mainW = new MainWidget();
            mainW->show();
        }
        this->close();
    }

}

//注册完成的槽函数
void LoginWidget::signupComplete()
{
    if(0) //TODO: 判断用户输入的信息是否正确
    {
        //复制ID到登录界面 清空注册界面全部信息
        ui->stackedWidget->setCurrentIndex(0);  //注册完成后转入登录界面
        ui->lineEdit->setText(ui->lineEdit_id->text()); //把ID复制过去
        ui->lineEdit_id->setText("");
        ui->lineEdit_name->setText("");
        ui->lineEdit_password->setText("");
        ui->lineEdit_repeat->setText("");
        ui->lineEdit_tele->setText("");
        ui->lineEdit_email->setText("");
        ui->comboBox_airlines->setCurrentIndex(0);
        //隐藏所有错误提示
        ui->label_error_id->hide();
        ui->label_error_password->hide();
        ui->label_error_passwordRepeat->hide();
        ui->label_error_tele->hide();
        ui->label_error_email->hide();
    }
    else
    {
        QMessageBox::warning(this, "账户注册", "您的注册信息出现问题，请返回修改！");
    }
}

