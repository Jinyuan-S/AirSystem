#include "airlinesdetailwidget.h"
#include "ui_airlinesdetailwidget.h"


AirlinesDetailWidget::AirlinesDetailWidget(QWidget *parent, Flight *flightTemp) :
    QWidget(parent),
    ui(new Ui::AirlinesDetailWidget)
{
    ui->setupUi(this);
    flight = new Flight();
    *flight = *flightTemp;
}

AirlinesDetailWidget::~AirlinesDetailWidget()
{
    delete ui;
}


