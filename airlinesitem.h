#ifndef AIRLINESITEM_H
#define AIRLINESITEM_H

#include <QWidget>
#include <QString>
#include <QTime>
#include <QMouseEvent>
#include "airlinesdetailwidget.h"

namespace Ui {
class AirlinesItem;
}

class AirlinesItem : public QWidget
{
    Q_OBJECT

public:
    explicit AirlinesItem(QWidget *parent = nullptr);
    ~AirlinesItem();

private:
    Ui::AirlinesItem *ui;
    AirlinesDetailWidget *detailWidget;
    QString fromAirport;
    QString toAirport;
    QString fromTime;
    QString toTime;
    QString flightNum;
    QString flightType;
    QString totalTime;
    QString price;

protected:
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // AIRLINESITEM_H
