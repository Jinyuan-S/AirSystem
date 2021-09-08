#ifndef ADDFLIGHTWIDGET_H
#define ADDFLIGHTWIDGET_H

#include <QWidget>

namespace Ui {
class AddFlightWidget;
}

class AddFlightWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AddFlightWidget(QWidget *parent = nullptr);
    ~AddFlightWidget();

private:
    Ui::AddFlightWidget *ui;
};

#endif // ADDFLIGHTWIDGET_H
