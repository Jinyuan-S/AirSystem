#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
//#include <Person.h>

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWidget; }
QT_END_NAMESPACE

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();
    static const int RoleAsUser = 1;
    static const int RoleAsAdmin = 2;
//    User user;
//    Admin admin;

private:
    Ui::LoginWidget *ui;
    void loginComplete();
    void signupComplete();
    void basicInit();
    void pushedInit();
    void loginPushedInit();
    void signupPushedInit();
};
#endif // LOGINWIDGET_H
