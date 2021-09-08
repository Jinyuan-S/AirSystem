#include "airlinesitem.h"
#include "ui_airlinesitem.h"
#include <QDate>
#include <QMessageBox>

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

    //计算价格
    int price = stoi(flight->Price);
    QDate currentDate = QDate().currentDate();
    QDate flightDate = QDate::fromString(QString::fromLocal8Bit(flight->Date), "yyyy-MM-dd");
    int diff = currentDate.daysTo(flightDate);
    //相差日期过大就减钱
    if(diff >= 4)
    {
        price = std::max((int)(price / 2), (int)(price * (4.0 / diff)));
    }

    //计算是否起飞
    if(currentDate > flightDate)
    {
        isTookOff = 1;
    }
    else if(currentDate == flightDate)
    {
        QTime currentTime = QTime().currentTime();
        QTime flightTime = QTime::fromString(QString::fromLocal8Bit(flight->Time_on), "hh:mm:ss");
        if(currentTime > flightTime)
        {
            isTookOff = 1;
        }
        else
        {
            isTookOff = 0;
        }
    }
    else
    {
        isTookOff = 0;
    }

    if(isTookOff)
    {
        ui->label->hide();
    }
    else
    {
        ui->label_2->hide();
    }

    //初始化航班信息
    //这里从航班类里获取信息
    if(flight)
    {
        ui->label_from->setText(QString::fromLocal8Bit(flight->Origin));
        ui->label_to->setText(QString::fromLocal8Bit(flight->Destination));
        ui->label_price->setText("￥" + QString::number(price));
        ui->label_fromTime->setText(QString::fromLocal8Bit(flight->Time_on.substr(0, 5)));
        ui->label_toTime->setText(QString::fromLocal8Bit(flight->Time_off.substr(0, 5)));
        ui->label_flightNum->setText("航班号:" + QString::fromLocal8Bit(flight->Airline));
        ui->label_flightType->setText("机型:" + QString::fromLocal8Bit(flight->Model));
        ui->label_att->setText("准点率:" + QString::fromLocal8Bit(flight->Rate) + "%");
    }


    //第二天是否显示
    if(flight->Tomorrow == "1")
    {
        ui->label_plus1->show();
    }
    else
    {
        ui->label_plus1->hide();
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
        if(isTookOff)
        {
            QMessageBox::information(this, "提示", "已起飞航班不能购票！");
        }
        else
        {
            detailWidget = new AirlinesDetailWidget(nullptr, flight);
            detailWidget->setWindowModality(Qt::ApplicationModal);
            detailWidget->show();
            //若detail添加订单，则传递信号
            connect(detailWidget, &AirlinesDetailWidget::added, [=](vector<Children_order> vec){
                qDebug() << "AirlinesItem Signals Emit!";
                emit added(vec);
//                close();
            });
        }

    }
    QWidget::mouseReleaseEvent(event);
}
