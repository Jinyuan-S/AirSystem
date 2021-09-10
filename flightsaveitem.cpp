#include "flightsaveitem.h"
#include "ui_flightsaveitem.h"
#include <addflightwidget.h>
#include <QMessageBox>
#include <Admin.h>

FlightSaveItem::FlightSaveItem(QWidget *parent, Flight *flight, QString company) :
    QWidget(parent),
    ui(new Ui::FlightSaveItem)
{
    ui->setupUi(this);
    ui->label_added->hide();
    ui->label_from->setText(QString::fromLocal8Bit(flight->Origin));
    ui->label_to->setText(QString::fromLocal8Bit(flight->Destination));
    AddFlightWidget *fWidget = new AddFlightWidget(nullptr, company);

    connect(ui->label_edit, &ClickableLabel::clicked, [=](){
        fWidget->setFlight(flight);
        fWidget->setWindowModality(Qt::ApplicationModal);
        fWidget->show();
    });

    connect(fWidget, &AddFlightWidget::saved, [=](){
        bool Ok = fWidget->saveFlight(*flight);
        if(Ok) fWidget->close();
        else
        {
            QMessageBox::warning(fWidget, "航班添加", "请填写所有信息或检查航班号与航空公司是否对应！");
        }
    });

    connect(fWidget, &AddFlightWidget::commited, this, &FlightSaveItem::deleted);
    connect(fWidget, &AddFlightWidget::commited, [=](){
        bool Ok = fWidget->saveFlight(*flight);
        if(Ok)
        {
            int ret = Admin().add_flight(*flight);
            if(ret == 0)
            {
                qDebug() << "添加航班";
                ui->label_edit->hide();
                ui->label_added->show();
                fWidget->close();
                QMessageBox::information(fWidget, "航班添加", "添加完成！");
                fWidget->close();
            }
            else if(ret == 1)
            {
                QMessageBox::warning(fWidget, "航班添加", "该航班已存在！");
            }
            else
            {
                QMessageBox::warning(fWidget, "航班添加", "该航班的飞行员时间安排冲突！");
            }

            qDebug() << "添加航班";
        }
        else
        {
            QMessageBox::warning(fWidget, "航班添加", "请填写所有信息或检查航班号与航空公司是否对应！");
        }
    });

}

FlightSaveItem::~FlightSaveItem()
{
    delete ui;
}
