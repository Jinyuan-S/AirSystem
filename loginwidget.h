#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <Person.h>
#include <Admin.h>
#include <Buyer.h>

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWidget; }
QT_END_NAMESPACE

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();
//    static const int RoleAsUser = 1;
//    static const int RoleAsAdmin = 2;
    Buyer *buyer;
    Admin *admin;
    Person *person;

private:
    bool isIdAddedInLogin = 0;
    bool isPasswordAddedInLogin = 0;
    bool isIdLegal = 1;
    bool isPasswordLegal = 1;
    bool isTeleLegal = 1;
    bool isEmailLegal = 1;
    bool isRepeatLegal = 1;
    bool isIdAdded = 0;
    bool isNameAdded = 0;
    bool isPasswordAdded = 0;
    bool isTeleAdded = 0;
    bool isEmailAdded = 0;
    bool isRepeatAdded = 0;
    bool isAirlinesAdded = 0;
    bool isGenderAdded = 0;
    Ui::LoginWidget *ui;
    void loginComplete();
    void signupComplete();
    void basicInit();
    void pushedInit();
    void loginPushedInit();
    void signupPushedInit();
};
#endif // LOGINWIDGET_H
