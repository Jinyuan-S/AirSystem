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
    explicit QueryWidget(QWidget *parent = nullptr);
    ~QueryWidget();

private:
    Ui::QueryWidget *ui;
};

#endif // QUERYWIDGET_H
