#ifndef QUERYWIDGET_H
#define QUERYWIDGET_H

#include <QWidget>
#include "airlinesitem.h"
#include "Flight.h"
#include "Inquiry.h"
using std::vector;

namespace Ui {
class QueryWidget;
}

class QueryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QueryWidget(QWidget *parent = nullptr, int type = 0);
    ~QueryWidget();
    void setFromAndTo(QString from, QString to, QDate date);
    void setNumber(QString number, QDate date);

private:
    vector<AirlinesItem *> flightWidgetVec;
    vector<Flight> flightVec;
    Flight *flight;
    Inquiry *inq;
    Ui::QueryWidget *ui;
    void addFlight(vector<Flight> &flightVec);
    void deleteFlight();
    void changeSortFilter();
    void returnToNormal();
signals:
    void added(vector<Children_order> vec);
};

#endif // QUERYWIDGET_H
