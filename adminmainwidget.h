#ifndef ADMINMAINWIDGET_H
#define ADMINMAINWIDGET_H

#include <QWidget>

#include "Admin.h"
#include "flightsavewidget.h"
#include <QSqlDatabase>

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
    QSqlDatabase *db;
    Ui::AdminMainWidget *ui;
    Admin *admin;
    void airlineInit();
    void orderInit();
    void orderAllInit();
    FlightSaveWidget *fWidget;
//    void changeSortFliter();
//    void airlineSortFliter();
};

#endif // ADMINMAINWIDGET_H
