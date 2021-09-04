#include "airlinesdetailwidget.h"
#include "ui_airlinesdetailwidget.h"


AirlinesDetailWidget::AirlinesDetailWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AirlinesDetailWidget)
{
    ui->setupUi(this);
}

AirlinesDetailWidget::~AirlinesDetailWidget()
{
    delete ui;
}


