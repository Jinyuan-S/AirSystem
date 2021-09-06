#ifndef MAINWIDGETMINEPART_H
#define MAINWIDGETMINEPART_H

#include <QWidget>

#include "modifypassworddialog.h"
#include "Admin.h"
#include "Buyer.h"
#include "Person.h"

namespace Ui {
class MainWidgetMinePart;
}

class MainWidgetMinePart : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidgetMinePart(QWidget *parent = nullptr);
    ~MainWidgetMinePart();
    void setBuyer(Buyer *buyerTemp);
    void setAdmin(Admin *adminTemp);
    bool changeToNormal();
    bool statusOfLabel = 0;

private:
    bool isTeleLegal = 0;
    bool isEmailLegal = 0;
    ModifyPasswordDialog *passwordDialog;
    Ui::MainWidgetMinePart *ui;
    Buyer *buyer = nullptr;
    Admin *admin = nullptr;
    Person *person = nullptr;
    void basicInit();
    void userInfoLoad(Buyer *user);
    void cancleInfoChange();
};

#endif // MAINWIDGETMINEPART_H
