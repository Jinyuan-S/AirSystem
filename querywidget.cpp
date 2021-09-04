#include "querywidget.h"
#include "ui_querywidget.h"

#include <QDebug>
#include <QScrollArea>

QueryWidget::QueryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QueryWidget)
{
    ui->setupUi(this);

    this->setWindowTitle("");

    //设置scrollArea widget自动设置背景白色
    ui->scrollArea->setAutoFillBackground(true);
    ui->widget->setAutoFillBackground(true);

    //初始化背景图片
    setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(QPixmap(":/main/images/query_background.jpg")));
    setPalette(palette);

    const int Num = 8;

    //添加航班
    ui->scrollArea->setWidgetResizable(false);
    ui->scrollAreaWidgetContents->resize((370 + 10), Num * (120 + 10) + 50); //370是item宽度 10是宽度间的间隙 120是item长度 10是长度间的间隙 50是最底下多留点地
    for(int i = 0; i < Num; ++i)
    {
        AirlinesItem *item = new AirlinesItem();
        item->setParent(ui->scrollAreaWidgetContents);
        item->move(5, i * (120 + 10) + 10); //5让item和左边有点间隙
    }
    //改变底线标识位置
//    qDebug() << ui->widget_end->geometry();
    ui->widget_end->move(100, Num * (120 + 10) + 10); //100可以让底线正好到最中间
//    qDebug() << ui->widget_end->geometry();

}

QueryWidget::~QueryWidget()
{
    delete ui;
}
