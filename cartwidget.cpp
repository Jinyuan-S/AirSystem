#include "cartwidget.h"
#include "ui_cartwidget.h"

#include <QMessageBox>

CartWidget::CartWidget(QWidget *parent, Buyer *buyer) :
    QWidget(parent),
    ui(new Ui::CartWidget)
{
    ui->setupUi(this);
    setWindowTitle("购物车");
    Order *order = new Order();

    Buyer *buyerNew = new Buyer();
    *buyerNew = *buyer;

    connect(ui->pushButton_ok, &QPushButton::clicked, [=](){
        if(allOrderVec.size() == 0)
        {
            QMessageBox::warning(this, "购物车", "您的购物车里没有航班！");
        }
        else
        {
            //即将买票
            Mother_order motherOrder;
            motherOrder.Is_cancel = "0";
            motherOrder.Is_paid = "0";
            motherOrder.Who = buyerNew->ID;
            qDebug() << QString::fromLocal8Bit(motherOrder.Who);
            vector<Children_order> tempChildOrderVec;
            int priceTot = 0;

            //子订单添加
            for(auto i = allOrderVec.begin(); i != allOrderVec.end(); ++i)
            {
                for(auto &j : *i)
                {
                    tempChildOrderVec.push_back(j);
                    priceTot += stoi(j.Money);
                }
            }

            //把票价添加一下
            motherOrder.Money = std::to_string(priceTot);
            qDebug() << QString::fromLocal8Bit(motherOrder.Money);

            //买票判定
            int rec;
            Children_order recOrder;
            int ret = order->add_order(motherOrder, tempChildOrderVec, rec, recOrder);
//            返回值：
//                0：成功购买
//                1：当前正在飞机上
//                2：不能及时从上一趟航班落地地赶到新加航班起飞地
//                3：来不及从新加航班目的地赶往下一班航班出发地
            if(ret == 0)
            {
                QMessageBox::information(this, "购物车", "下单成功，清前往订单页面支付！");
                deleteAllOrder();
                allOrderVec.clear();
                emit closed();
                close();
            }
            else if(ret == 1)
            {
                QMessageBox::warning(this, "购物车", "有航班和您已经购买的航班时间冲突！无法完成购买。");
            }
            else if(ret == 2)
            {
                QMessageBox::warning(this, "购物车", "您可能无法及时从您的上一趟航班落地地赶到新加航班起飞地！无法完成购买。");
            }
            else
            {
                QMessageBox::warning(this, "购物车", "您可能无法及时从您的新加航班落地地赶到下一班航班的起飞地！无法完成购买。");
            }
        }

    });

}

CartWidget::~CartWidget()
{
    delete ui;
}

//在UI中添加
void CartWidget::loadAllOrder(/*vector<vector<Children_order>> allOrder*/)
{
    ui->scrollArea->setWidgetResizable(false);
    int totalHeight = 0;
    int totalFare = 0;
    //添加购物车Item
    ui->scrollAreaWidgetContents->resize((400 + 20), 3000);
    for(auto i = allOrderVec.begin(); i != allOrderVec.end(); ++i)
    {
        CartItem *item = new CartItem(ui->scrollAreaWidgetContents, &*i);
        item->move(20, totalHeight + 10); //20让item和左边有点间隙
        item->show();
        qDebug() << item->geometry();
        int itemHeight = item->geometry().height();
        qDebug() << "itemHeight" << itemHeight;
        totalHeight += (itemHeight + 10);
        qDebug() << "totalHeight" << totalHeight;
        itemVec.push_back(item);
//        auto itemIterator = itemVec.end() - 1;
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
            qDebug() << QString::fromLocal8Bit(j->Who);
            qDebug() << QString::fromLocal8Bit(j->Seat);
            totalFare += stoi(j->Money);
        }
    }
    ui->label_totalFare->setText("￥" + QString::number(totalFare));
}

//在ui中删除
void CartWidget::deleteAllOrder()
{
    for(auto i = itemVec.begin(); i != itemVec.end(); ++i)
    {
        (*i)->setParent(nullptr);
        (*i)->deleteLater();
    }
    itemVec.clear();
    ui->label_totalFare->setText("￥0");
}

void CartWidget::addOrder(vector<Children_order> vec)
{
    qDebug() << "CartWidget AddOrder Function REALLY Begin!";
    allOrderVec.push_back(vec);
    int size2 = 0;
    for(auto i = allOrderVec.begin(); i != allOrderVec.end(); ++i)
    {
        size2 += i->size();
    }
    if(size2 >= 5)
    {
        ui->pushButton_ok->setEnabled(false);
    }
    qDebug() << "CartWidget AddOrder Function End!";
}

void CartWidget::resizeEvent(QResizeEvent *event)
{
    deleteAllOrder();
    loadAllOrder();
}
