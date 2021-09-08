#ifndef BUYADDPERSONDIALOG_H
#define BUYADDPERSONDIALOG_H

#include <QDialog>
#include <vector>
#include <string>
#include <QComboBox>
using std::vector;
using std::string;
#include "Flight.h"

namespace Ui {
class BuyAddPersonDialog;
}

class BuyAddPersonDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BuyAddPersonDialog(QWidget *parent = nullptr, Flight flight = Flight(), string cabin = "");
    ~BuyAddPersonDialog();

private:
    Ui::BuyAddPersonDialog *ui;
    void hidePerson(int row);
    void showPerson(int row);
    string getNameOrSeat(int num, int type);
    void comboBoxAddA(QComboBox *cBox, int type);
    void comboBoxAddB(QComboBox *cBox, int type);
    void comboBoxAddC(QComboBox *cBox, int type);
    int repeatInFive();


signals:
    void addedPerson(vector<string> personStr, vector<string> seatStr);
};

#endif // BUYADDPERSONDIALOG_H
