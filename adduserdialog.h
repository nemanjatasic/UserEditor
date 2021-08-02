#ifndef ADDUSERDIALOG_H
#define ADDUSERDIALOG_H

#include <QDialog>
#include "user.h"

namespace Ui {
class AddUserDialog;
}

class AddUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddUserDialog(QWidget *parent = nullptr);
    ~AddUserDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddUserDialog *ui;

signals:
    void accept(int);
};

#endif // ADDUSERDIALOG_H
