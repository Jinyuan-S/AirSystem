#ifndef MODIFYPASSWORDDIALOG_H
#define MODIFYPASSWORDDIALOG_H

#include <QDialog>


namespace Ui {
class ModifyPasswordDialog;
}

class ModifyPasswordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyPasswordDialog(QWidget *parent = nullptr);
    ~ModifyPasswordDialog();

private:
    Ui::ModifyPasswordDialog *ui;
};

#endif // MODIFYPASSWORDDIALOG_H
