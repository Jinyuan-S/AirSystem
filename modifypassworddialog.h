#ifndef MODIFYPASSWORDDIALOG_H
#define MODIFYPASSWORDDIALOG_H

#include <QDialog>

#include "Admin.h"
#include "Buyer.h"
#include "Person.h"

namespace Ui {
class ModifyPasswordDialog;
}

class ModifyPasswordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyPasswordDialog(QWidget *parent = nullptr);
    ~ModifyPasswordDialog();
    void setAdmin(Admin *adminTemp);
    void setBuyer(Buyer *buyerTemp);

private:
    Ui::ModifyPasswordDialog *ui;
    Admin *admin;
    Buyer *buyer;
    Person *person;

};

#endif // MODIFYPASSWORDDIALOG_H
