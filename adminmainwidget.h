#ifndef ADMINMAINWIDGET_H
#define ADMINMAINWIDGET_H

#include <QWidget>

#include "Admin.h"

namespace Ui {
class AdminMainWidget;
}

class AdminMainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AdminMainWidget(QWidget *parent = nullptr, Admin *admin = nullptr);
    ~AdminMainWidget();

private:
    Ui::AdminMainWidget *ui;
};

#endif // ADMINMAINWIDGET_H
