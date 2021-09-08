#include "airlinesitem.h"
#include "ui_airlinesitem.h"
#include <QDate>

AirlinesItem::AirlinesItem(QWidget *parent, Flight *flightTemp) :
    QWidget(parent),
    ui(new Ui::AirlinesItem)
{
    ui->setupUi(this);

    qDebug() << "airlinesItem BEGIN!";


    flight = new Flight();
    *flight = *flightTemp;


    this->setAutoFillBackground(true);

    //初始化背景图片
    setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(QPixmap(":/general/images/edging.jpg")));
    setPalette(palette);


    qDebug() << QString::fromLocal8Bit(flight->Origin);
    qDebug() << QString::fromLocal8Bit(flight->Destination);

    //初始化箭头图片 (TODO: 没写好）
//    ui->label_arrow->setPixmap(QPixmap(":/general/images/arrow.jfif"));


    //初始化航班信息
    //这里从航班类里获取信息
    if(flight)
    {
        ui->label_from->setText(QString::fromLocal8Bit(flight->Origin));
        ui->label_to->setText(QString::fromLocal8Bit(flight->Destination));
        ui->label_price->setText("￥" + QString::fromLocal8Bit(flight->Price));
        ui->label_fromTime->setText(QString::fromLocal8Bit(flight->Time_on.substr(0, 5)));
        ui->label_toTime->setText(QString::fromLocal8Bit(flight->Time_off.substr(0, 5)));
        ui->label_flightNum->setText("航班号:" + QString::fromLocal8Bit(flight->Airline));
        ui->label_flightType->setText("机型:" + QString::fromLocal8Bit(flight->Model));
        ui->label_att->setText("准点率:" + QString::fromLocal8Bit(flight->Rate) + "%");
    }

}

AirlinesItem::~AirlinesItem()
{
    delete ui;
}



//检测鼠标释放
void AirlinesItem::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        detailWidget = new AirlinesDetailWidget(nullptr, flight);
        detailWidget->setWindowModality(Qt::ApplicationModal);
        detailWidget->show();
    }
    QWidget::mouseReleaseEvent(event);
}
