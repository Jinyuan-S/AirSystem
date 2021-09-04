#include "airlinesitem.h"
#include "ui_airlinesitem.h"

AirlinesItem::AirlinesItem(QWidget *parent/*TODO: 这里需要传入航班类*/) :
    QWidget(parent),
    ui(new Ui::AirlinesItem)
{
    ui->setupUi(this);



    this->setAutoFillBackground(true);

    //初始化背景图片
    setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(QPixmap(":/general/images/edging.jpg")));
    setPalette(palette);

    //初始化箭头图片 (TODO: 没写好）
//    ui->label_arrow->setPixmap(QPixmap(":/general/images/arrow.jfif"));


    //初始化航班信息
    //这里从航班类里获取信息
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
        detailWidget = new AirlinesDetailWidget(/*这里需要传入航班信息*/);
        detailWidget->setWindowModality(Qt::ApplicationModal);
        detailWidget->show();
    }
    QWidget::mouseReleaseEvent(event);
}
