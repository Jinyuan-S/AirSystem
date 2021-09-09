#ifndef FLIGHTSAVEITEM_H
#define FLIGHTSAVEITEM_H

#include <QWidget>

#include "Flight.h"

namespace Ui {
class FlightSaveItem;
}

class FlightSaveItem : public QWidget
{
    Q_OBJECT

public:
    explicit FlightSaveItem(QWidget *parent = nullptr, Flight *flight = nullptr, QString company = "");
    ~FlightSaveItem();

private:
    Ui::FlightSaveItem *ui;

signals:
    void deleted();
};

#endif // FLIGHTSAVEITEM_H
