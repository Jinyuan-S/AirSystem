#ifndef AIRLINESDETAILWIDGET_H
#define AIRLINESDETAILWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include "Flight.h"
#include <Children_order.h>
#include <vector>
using std::vector;

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

signals:
    void added(vector<Children_order> vec);
};

#endif // AIRLINESDETAILWIDGET_H
