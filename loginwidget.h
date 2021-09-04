#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWidget; }
QT_END_NAMESPACE

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    LoginWidget(QWidget *parent = nullptr, int roleNumber = 0);
    ~LoginWidget();
    static const int RoleAsUser = 1;
    static const int RoleAsAdmin = 2;

private:
    Ui::LoginWidget *ui;
    void loginComplete();
    void signupComplete();

};
#endif // LOGINWIDGET_H
