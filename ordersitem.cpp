#include "ordersitem.h"
#include "ui_ordersitem.h"

OrdersItem::OrdersItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrdersItem)
{
    ui->setupUi(this);

    //初始化背景图片
    setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(QPixmap(":/general/images/edging420_200.jpg")));
    setPalette(palette);

    //connect 连接详细信息label与详细信息Widget
    connect(ui->label_detail, &ClickableLabel::clicked, [=](){
        detailWidget = new OrdersDetailWidget(/*这里需要订单具体信息*/);
        detailWidget->setWindowModality(Qt::ApplicationModal);
        detailWidget->show();
    });
}

OrdersItem::~OrdersItem()
{
    delete ui;
}
