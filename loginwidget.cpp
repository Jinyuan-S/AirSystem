#include "loginwidget.h"
#include "ui_loginwidget.h"
#include "mainwidget.h"
#include "adminmainwidget.h"
#include <QLabel>
#include <QStackedWidget>
#include <QPixmap>
#include <QDebug>
#include <QPalette>

//TODO: 实时检测输入是否符合格式

LoginWidget::LoginWidget(QWidget *parent, int roleNumber) //roleNum 是用户还是管理员
    : QWidget(parent)
    , ui(new Ui::LoginWidget)
{
    ui->setupUi(this);


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

    //初始时选项为用户还是管理员
    if(roleNumber != RoleAsAdmin) //非管理员
    {
        ui->comboBox_type->setCurrentIndex(0);
        ui->comboBox_type_signup->setCurrentIndex(0);
        ui->label_airlines->setEnabled(false);
        ui->comboBox_airlines->setEnabled(false);
    }
    else
    {
        ui->comboBox_type->setCurrentIndex(1);
        ui->comboBox_type_signup->setCurrentIndex(1);
        ui->label_airlines->setEnabled(false);
        ui->comboBox_airlines->setEnabled(false);
    }


    //初始化隐藏注册界面有误提示
    ui->label_error_id->hide();
    ui->label_error_password->hide();
    ui->label_error_tele->hide();
    ui->label_error_email->hide();


    //当在登录界面点击注册时，转入注册界面
    connect(ui->label_toSignup, &ClickableLabel::clicked, [=](){
        ui->stackedWidget->setCurrentIndex(1);  //转入注册界面
//        qDebug() << ui->stackedWidget->geometry();
    });
    //当在注册界面点击我已经有账号时，转入登录界面
    connect(ui->label_toLogin, &ClickableLabel::clicked, [=](){
        ui->stackedWidget->setCurrentIndex(0);  //转入登录界面
//        qDebug() << ui->stackedWidget->geometry();
    });

    //当在登录界面完成登录后，进入主界面或者向用户报告错误
    connect(ui->pushButton_loginComplete, &QPushButton::clicked, this, &LoginWidget::loginComplete);
    //当在注册界面完成注册后，回到登录界面或向用户报告错误
    connect(ui->pushButton_signupComplete, &QPushButton::clicked, this, &LoginWidget::signupComplete);

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


    //当输入框结束输入时，判定输入是否合法
    //密码和确认密码是否相同
    connect(ui->lineEdit_repeat, &QLineEdit::editingFinished, [=](){
        if(ui->lineEdit_password->text() == ui->lineEdit_repeat->text())
        {
            ui->label_error_password->hide();
        }
        else
        {
            ui->label_error_password->show();
        }
    });

    connect(ui->lineEdit_password, &QLineEdit::editingFinished, [=](){
        if(ui->lineEdit_password->text() == ui->lineEdit_repeat->text())
        {
            ui->label_error_password->hide();
        }
    });

    //TODO: 电话是否合法
    connect(ui->lineEdit_tele, &QLineEdit::editingFinished, [=](){

    });


    //TODO: 邮箱是否合法
    connect(ui->lineEdit_email, &QLineEdit::editingFinished, [=](){

    });





}

LoginWidget::~LoginWidget()
{
    delete ui;
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
    if(1) //TODO: 判断用户输入的信息是否正确
    {
        ui->stackedWidget->setCurrentIndex(0);  //注册完成后转入登录界面
    }
    else
    {

    }
}
