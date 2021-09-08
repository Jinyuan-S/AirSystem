#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "querywidget.h"
#include "ordersitem.h"
#include "Buyer.h"
#include "Order.h"
#include "Mother_order.h"
#include "Children_order.h"
#include "cartwidget.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr, Buyer *buyerTemp = nullptr);
    ~MainWidget();

private:
    Ui::MainWidget *ui;
//    void createUserBasicUI(Ui::MainWidget ui);
//    void createAdminBasicUi(Ui::MainWidget ui);
    Buyer *buyer;
    Order *order;

    CartWidget *cWidget;
    void newQueryWidget(int type);
    void buyInit();
    void orderInit();
    void mineInit();
};

#endif // MAINWIDGET_H
