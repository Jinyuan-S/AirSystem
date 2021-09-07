#ifndef AIRLINESDETAILWIDGET_H
#define AIRLINESDETAILWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include "Flight.h"

namespace Ui {
class AirlinesDetailWidget;
}

class AirlinesDetailWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AirlinesDetailWidget(QWidget *parent = nullptr, Flight *flightTemp = nullptr);
    ~AirlinesDetailWidget();

private:
    Flight *flight;
    Ui::AirlinesDetailWidget *ui;

};

#endif // AIRLINESDETAILWIDGET_H
