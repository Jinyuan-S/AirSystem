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
#include <QRadioButton>
#include "Database.h"
#include <vector>
#include <string>
//#include "Person.h"
using std::string;

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
    //new对象
    buyer = new Buyer();
    admin = new Admin();
    person = new Person();

    //合法性全部等于1
    isIdLegal = 1;
    isPasswordLegal = 1;
    isTeleLegal = 1;
    isEmailLegal = 1;
    isRepeatLegal = 1;

    //是否添加全部等于0
    isIdAdded = 0;
    isNameAdded = 0;
    isPasswordAdded = 0;
    isTeleAdded = 0;
    isEmailAdded = 0;
    isRepeatAdded = 0;
    isAirlinesAdded = 0;
    isGenderAdded = 0;
    isIdAddedInLogin = 0;
    isPasswordAddedInLogin = 0;

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
    ui->comboBox_airlines->addItems(QStringList() << "请选择" << "Air China" << "China Eastern");

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
        //重构admin和buyer
        delete admin;
        delete buyer;
        admin = new Admin();
        buyer = new Buyer();
        string text = ui->lineEdit->text().toStdString();
        admin->change_id(text);
        buyer->change_id(text);
        ui->lineEdit_id->setText(ui->lineEdit->text()); //把ID复制过去
        ui->lineEdit_2->setText(""); //把登录的密码清空
    });

    //当在注册界面点击我已经有账号时，转入登录界面
    connect(ui->label_toLogin, &ClickableLabel::clicked, [=](){
        ui->stackedWidget->setCurrentIndex(0);  //转入登录界面
        ui->lineEdit->setText(ui->lineEdit_id->text()); //把ID复制过去
        ui->lineEdit_password->setText(""); //把这里的密码清空
        ui->lineEdit_repeat->setText(""); //把这里的重复密码清空
        //重构admin和buyer
        delete admin;
        delete buyer;
        admin = new Admin();
        buyer = new Buyer();
        string text = ui->lineEdit_id->text().toStdString();
        admin->change_id(text);
        buyer->change_id(text);
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
    connect(ui->lineEdit, &QLineEdit::textChanged, [=](){
        if(ui->lineEdit->text().toStdString() != "")
        {
            isIdAddedInLogin = 1;
            admin->ID = ui->lineEdit->text().toStdString();
            buyer->ID = ui->lineEdit->text().toStdString();
        }
        else
        {
            isIdAddedInLogin = 0;
        }
    });
    connect(ui->lineEdit_2, &QLineEdit::textChanged, [=](){
        if(ui->lineEdit_2->text().toStdString() != "")
        {
            isPasswordAddedInLogin = 1;
            admin->Password = ui->lineEdit_2->text().toStdString();
            buyer->Password = ui->lineEdit_2->text().toStdString();
        }
        else
        {
            isPasswordAddedInLogin = 0;
        }
    });

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

    //ID是否合法
    connect(ui->lineEdit_id, &QLineEdit::textChanged, [=](){
        if(ui->lineEdit_id->text() != "")
        {
            isIdAdded = 1;
            string text = ui->lineEdit_id->text().toStdString();
            int retA = admin->change_id(text);
            int ret = buyer->change_id(text);
            if(ret == 0)
            {
                ui->label_error_id->hide();
                isIdLegal = 1;
            }
            else if(ret == 1)
            {
                ui->label_error_id->setText("ID位数要在6-10位之间");
                ui->label_error_id->show();
                isIdLegal = 0;
            }
            else if(ret == 2)
            {
                ui->label_error_id->setText("ID中含有非法字符");
                ui->label_error_id->show();
                isIdLegal = 0;
            }
            else
            {
                ui->label_error_id->setText("您的ID格式有误！");
                ui->label_error_id->show();
                isIdLegal = 0;
            }
        }
    });

    //添加姓名
    connect(ui->lineEdit_name, &QLineEdit::editingFinished, [=](){
        std::string cstr;
        QString qstring = ui->lineEdit_name->text();
        //从QString 到 std::string
        cstr = string((const char *)qstring.toLocal8Bit());
        isNameAdded = 1;
        string text = cstr;
        admin->Name = text;
        buyer->Name = text;
    });

    //密码是否合法
    connect(ui->lineEdit_password, &QLineEdit::editingFinished, [=](){
        isPasswordAdded = 1;
        string text = ui->lineEdit_password->text().toStdString();
        int retA = admin->change_password(text);
        int ret = buyer->change_password(text);
        qDebug() << "密码是否合法：" << ret;
        if(ret == 0)
        {
            ui->label_error_password->hide();
            isPasswordLegal = 1;
        }
        else
        {
            ui->label_error_password->setText("密码位数要在6-20位之间");
            ui->label_error_password->show();
            isPasswordLegal = 0;
        }
    });

    //密码和确认密码是否相同
    connect(ui->lineEdit_repeat, &QLineEdit::editingFinished, [=](){
        isRepeatAdded = 1;
        if((ui->lineEdit_password->text() == ui->lineEdit_repeat->text())
                || (ui->lineEdit_password->text() == ""))
        {
            ui->label_error_passwordRepeat->hide();
            isRepeatLegal = 1;
        }
        else
        {
            ui->label_error_passwordRepeat->show();
            isRepeatLegal = 0;
        }
    });

    //密码被更改后和确认密码一样就把错误信息隐藏
    connect(ui->lineEdit_password, &QLineEdit::editingFinished, [=](){
        if(ui->lineEdit_password->text() == ui->lineEdit_repeat->text())
        {
            ui->label_error_passwordRepeat->hide();
            isRepeatLegal = 1;
        }
    });

    connect(ui->radioButton_male, &QRadioButton::toggled, [=](){
        if(ui->radioButton_male->isChecked())
        {
            std::string cstr;
            QString qstring = "男";
            //从QString 到 std::string
            cstr = string((const char *)qstring.toLocal8Bit());
            isGenderAdded = 1;
            string text = cstr;
            buyer->change_gender(text);
            admin->change_gender(text);
        }
    });

    connect(ui->radioButton_female, &QRadioButton::toggled, [=](){
        if(ui->radioButton_female->isChecked())
        {
            std::string cstr;
            QString qstring = "女";
            //从QString 到 std::string
            cstr = string((const char *)qstring.toLocal8Bit());
            isGenderAdded = 1;
            string text = cstr;
            buyer->change_gender(text);
            admin->change_gender(text);
        }
    });

    //航空公司
    connect(ui->comboBox_airlines, &QComboBox::currentIndexChanged, [=](){
        if(ui->comboBox_airlines->currentIndex() == 0)
        {
            isAirlinesAdded = 0;
        }
        else
        {
            isAirlinesAdded = 1;
            admin->Company = ui->comboBox_airlines->currentText().toStdString();
        }

    });

    //电话是否合法
    connect(ui->lineEdit_tele, &QLineEdit::editingFinished, [=](){
        isTeleAdded = 1;
        string text = ui->lineEdit_tele->text().toStdString();
        int retA = admin->change_tel(text);
        int ret = buyer->change_tel(text);
        if(ret == 0)
        {
            ui->label_error_tele->hide();
            isTeleLegal = 1;
        }
        else if(ret == 1)
        {
            ui->label_error_tele->setText("电话长度不正确");
            ui->label_error_tele->show();
            isTeleLegal = 0;
        }
        else if(ret == 2)
        {
            ui->label_error_tele->setText("电话中含有非法字符");
            ui->label_error_tele->show();
            isTeleLegal = 0;
        }
    });

    //邮箱是否合法
    connect(ui->lineEdit_email, &QLineEdit::editingFinished, [=](){
        isEmailAdded = 1;
        string text = ui->lineEdit_email->text().toStdString();
        int retA = admin->change_email(text);
        int ret = buyer->change_email(text);
        if(ret == 0)
        {
            ui->label_error_email->hide();
            isEmailLegal = 1;
        }
        else if(ret == 1)
        {
            ui->label_error_email->setText("邮箱格式不正确");
            ui->label_error_email->show();
            isEmailLegal = 0;
        }
    });

    //当在注册界面完成注册后，回到登录界面或向用户报告错误
    connect(ui->pushButton_signupComplete, &QPushButton::clicked, this, &LoginWidget::signupComplete);
}


//登录完成的槽函数
void LoginWidget::loginComplete()
{
    if(isIdAddedInLogin && isPasswordAddedInLogin)
    {
        if(ui->comboBox_type->currentText() == "管理员")
        {
            int ret = person->admin_login(admin->ID, admin->Password, *admin);
            if(ret == 0)
            {
                AdminMainWidget *adminMainW = new AdminMainWidget(nullptr, admin);
                adminMainW->show();
                this->close();
            }
            else if(ret == 1)
            {
                QMessageBox::warning(this, "账户登录", "您的用户名不存在或者您没有连接网络！");
            }
            else if(ret == 2)
            {
                QMessageBox::warning(this, "账户登录", "您的密码或用户名不正确！");
            }
            else
            {
                QMessageBox::critical(this, "账户登录", "程序出bug了，不知道存在什么错误，无法完成登录。");
            }
        }
        else
        {
            int ret = person->buyer_login(buyer->ID, buyer->Password, *buyer);
            if(ret == 0)
            {
                MainWidget *mainW = new MainWidget(nullptr, buyer);
                mainW->show();
                this->close();
            }
            else if(ret == 1)
            {
                QMessageBox::warning(this, "账户登录", "您的用户名不存在！");
            }
            else if(ret == 2)
            {
                QMessageBox::warning(this, "账户登录", "您的密码或用户名不正确！");
            }
            else
            {
                QMessageBox::critical(this, "账户登录", "程序出bug了，不知道存在什么错误，无法完成登录。");
            }
        }
    }
    else
    {
        QMessageBox::warning(this, "账户登录", "请填写您的账号和密码！");
    }
}

//注册完成的槽函数
void LoginWidget::signupComplete()
{
    if(isIdLegal && isPasswordLegal && isRepeatLegal && isTeleLegal && isEmailLegal
            && isIdAdded && isNameAdded && isPasswordAdded && isRepeatAdded && isTeleAdded && isEmailAdded && isGenderAdded
            && (ui->comboBox_type_signup->currentIndex() == 0 || isAirlinesAdded))
    {
        bool ret = 0;
        if(ui->comboBox_type_signup->currentIndex() == 0) //用户
        {
            ret = person->add_buyer(*buyer);
        }
        else
        {
            ret = person->add_admin(*admin);
        }
        //判定是否成功
        if(ret)
        {
            QMessageBox::information(this, "账户注册", "注册成功！");
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
            QMessageBox::warning(this, "账户注册", "该账户已存在！");
        }
    }
    else
    {
        QMessageBox::warning(this, "账户注册", "您的注册信息出现问题或填写不完整，请返回修改！");
    }

}

