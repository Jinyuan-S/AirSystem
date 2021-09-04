#ifndef MAINWIDGETMINEPART_H
#define MAINWIDGETMINEPART_H

#include <QWidget>

#include "modifypassworddialog.h"

namespace Ui {
class MainWidgetMinePart;
}

class MainWidgetMinePart : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidgetMinePart(QWidget *parent = nullptr, int userType = 0);  //0为用户 1为管理员
    ~MainWidgetMinePart();
    void setUserType(int userType);

private:
    ModifyPasswordDialog *passwordDialog;
    Ui::MainWidgetMinePart *ui;
};

#endif // MAINWIDGETMINEPART_H
