#include "clickablelabel.h"
#include <QEvent>
#include <QEnterEvent>
#include <QMouseEvent>
#include <QPalette>

ClickableLabel::ClickableLabel(QWidget* parent, Qt::WindowFlags flags)
    : QLabel(parent)
{
    setPaletteDefault();

    //连接信号和槽
    connect(this, &ClickableLabel::released, [=](){
        setPaletteDefault();
    });
    connect(this, &ClickableLabel::pressed, [=](){
        setPalettePressed();
    });
}

ClickableLabel::~ClickableLabel() {}

//检测鼠标释放
void ClickableLabel::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit released();
        emit clicked();
    }
    QLabel::mouseReleaseEvent(event);
}

//检测鼠标按下
void ClickableLabel::mousePressEvent(QMouseEvent* event) {
    if(event->button() == Qt::LeftButton)
    {
        emit pressed();
    }
    QLabel::mousePressEvent(event);
}

//将Label颜色改为默认值
void ClickableLabel::setPaletteDefault()
{
    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::blue);   //改变字体颜色
    this->setPalette(palette);
}

//将Label颜色改为按下时的深蓝色
void ClickableLabel::setPalettePressed()
{
    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::darkBlue);   //改变字体颜色
    this->setPalette(palette);
}
