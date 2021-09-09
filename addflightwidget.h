#ifndef ADDFLIGHTWIDGET_H
#define ADDFLIGHTWIDGET_H

#include <QWidget>

#include "Flight.h"

namespace Ui {
class AddFlightWidget;
}

class AddFlightWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AddFlightWidget(QWidget *parent = nullptr, QString company = "");
    ~AddFlightWidget();
    void setFlight(Flight *flight);
    bool saveFlight(Flight &flight);

private:
    Ui::AddFlightWidget *ui;

signals:
    void saved();
    void commited();
};

#endif // ADDFLIGHTWIDGET_H
