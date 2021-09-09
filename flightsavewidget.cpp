#include "flightsavewidget.h"
#include "ui_flightsavewidget.h"

FlightSaveWidget::FlightSaveWidget(QWidget *parent, vector<Flight> fliTempVec, QString companyTemp) :
    QWidget(parent),
    ui(new Ui::FlightSaveWidget)
{
    ui->setupUi(this);
    company = companyTemp;
    flightVec = fliTempVec;
    updateUI();
}

FlightSaveWidget::~FlightSaveWidget()
{
    delete ui;
}

void FlightSaveWidget::updateUI()
{
    for(auto &i : itemVec)
    {
        i->setParent(nullptr);
        i->deleteLater();
    }

    ui->scrollArea->setWidgetResizable(false);
    //添加购物车Item
    ui->scrollAreaWidgetContents->resize((400 + 20), (80 + 10) * flightVec.size());
    for(auto i = flightVec.begin(); i != flightVec.end(); ++i)
    {
        FlightSaveItem *item = new FlightSaveItem(ui->scrollAreaWidgetContents, &*i, company);
        item->move(10, (80 + 10) * (i - flightVec.begin())); //10让item和左边有点间隙
        item->show();
        itemVec.push_back(item);
//        connect(item, &FlightSaveItem::deleted, [=](){

//        });
    }
}

void FlightSaveWidget::resizeEvent(QResizeEvent *event)
{
    updateUI();
}
