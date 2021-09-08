#include "addflightwidget.h"
#include "ui_addflightwidget.h"

AddFlightWidget::AddFlightWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddFlightWidget)
{
    ui->setupUi(this);
}

AddFlightWidget::~AddFlightWidget()
{
    delete ui;
}
