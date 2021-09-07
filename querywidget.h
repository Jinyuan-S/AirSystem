#ifndef QUERYWIDGET_H
#define QUERYWIDGET_H

#include <QWidget>
#include "airlinesitem.h"

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
    void setNumber(QString str, QDate date);

private:
    Ui::QueryWidget *ui;
};

#endif // QUERYWIDGET_H
