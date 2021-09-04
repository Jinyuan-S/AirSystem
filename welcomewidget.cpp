#include "welcomewidget.h"
#include "ui_welcomewidget.h"
#include "loginwidget.h"
#include <QSqlDatabase>
#include <QMessageBox>

WelcomeWidget::WelcomeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomeWidget)
{
    ui->setupUi(this);

    //初始化背景图片
    setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(QPixmap(":/welcomeWidget/images/welcome_background.jpg")));
    setPalette(palette);

    //connect——把label和loginWidget连接
    connect(ui->label_user, &ClickableLabel::clicked, [=](){
        LoginWidget *widget = new LoginWidget(nullptr, LoginWidget::RoleAsUser);
        widget->show();
        this->hide();
    });
    connect(ui->label_admin, &ClickableLabel::clicked, [=](){
        LoginWidget *widget = new LoginWidget(nullptr, LoginWidget::RoleAsAdmin);
        widget->show();
        this->hide();
    });


    QSqlDatabase db = QSqlDatabase::addDatabase("MYSQL");
        db.setHostName("8.136.214.13");
        db.setPort(3306);
        db.setDatabaseName("airsystem");
        db.setUserName("root");
        db.setPassword("654321");
        bool ok = db.open();
        if (ok)
        {
            QMessageBox::information(this, "infor", "success");
        }
        else
        {
            QMessageBox::information(this, "infor", "open failed");
            qDebug() << "error open database" ;
        }

}

WelcomeWidget::~WelcomeWidget()
{
    delete ui;
}
