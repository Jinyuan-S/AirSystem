#ifndef AIRLINESDETAILWIDGET_H
#define AIRLINESDETAILWIDGET_H

#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class AirlinesDetailWidget;
}

class AirlinesDetailWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AirlinesDetailWidget(QWidget *parent = nullptr);
    ~AirlinesDetailWidget();

private:
    Ui::AirlinesDetailWidget *ui;

};

#endif // AIRLINESDETAILWIDGET_H
