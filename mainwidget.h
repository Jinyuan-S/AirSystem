#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "querywidget.h"
#include "ordersitem.h"
#include "Buyer.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr, Buyer *buyer = nullptr);
    //TODO: 还需要 用户 和 管理员 的构造函数
    ~MainWidget();

private:
    Ui::MainWidget *ui;
//    void createUserBasicUI(Ui::MainWidget ui);
//    void createAdminBasicUi(Ui::MainWidget ui);
    void newQueryWidget();
};

#endif // MAINWIDGET_H
