#include "cartwidget.h"
#include "ui_cartwidget.h"

CartWidget::CartWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CartWidget)
{
    ui->setupUi(this);

    connect(ui->pushButton_ok, &QPushButton::clicked, [=](){
        //TODO:
    });

}

CartWidget::~CartWidget()
{
    delete ui;
}

void CartWidget::loadAllOrder(vector<vector<Children_order>> allOrder)
{
    ui->scrollArea->setWidgetResizable(false);
    int totalHeight = 0;
    int totalFare = 0;
    //添加购物车Item
    for(auto i = allOrder.begin(); i != allOrder.end(); ++i)
    {
        CartItem *item = new CartItem(ui->scrollAreaWidgetContents, &*i);
        item->move(5, totalHeight + 10); //5让item和左边有点间隙
        item->show();
        int itemHeight = item->geometry().y();
        totalHeight += (itemHeight + 10);
        itemVec.push_back(item);
        auto itemIterator = itemVec.end() - 1;
        //TODO: 删除 感觉现在的不太对
//        connect(item, &CartItem::deleted, [=](){
//            item->setParent(nullptr);
//            item->deleteLater();
//            itemVec.erase(itemIterator);
//            allOrder.erase(i);
//            deleteAllOrder();
//            loadAllOrder(allOrder);
//        });
        for(auto j = i->begin(); j != i->end(); ++j)
        {
            totalFare += stoi(j->Money);
        }
    }
    ui->scrollAreaWidgetContents->resize((400 + 10), totalHeight);
    ui->label_totalFare->setText("￥" + QString::number(totalFare));
}


void CartWidget::deleteAllOrder()
{
    for(auto i = itemVec.begin(); i != itemVec.end(); ++i)
    {
        (*i)->setParent(nullptr);
        (*i)->deleteLater();
    }
    itemVec.clear();
}
