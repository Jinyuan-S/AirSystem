#ifndef FLIGHTSAVEWIDGET_H
#define FLIGHTSAVEWIDGET_H

#include <QWidget>
#include "Flight.h"
#include <vector>
#include <flightsaveitem.h>
using std::vector;

namespace Ui {
class FlightSaveWidget;
}

class FlightSaveWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FlightSaveWidget(QWidget *parent = nullptr, vector<Flight> fliTempVec = vector<Flight>(), QString companyTemp = "");
    ~FlightSaveWidget();
    vector<Flight> flightVec;
    void updateUI();

private:
    Ui::FlightSaveWidget *ui;
    vector<FlightSaveItem *> itemVec;
    QString company;

protected:
    void resizeEvent(QResizeEvent *event);
};

#endif // FLIGHTSAVEWIDGET_H
