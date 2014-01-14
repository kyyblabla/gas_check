#ifndef ADDREDITDIALOG_H
#define ADDREDITDIALOG_H

#include <configxml.h>
#include <QDialog>

namespace Ui {
class AddrEditDialog;
}

class AddrEditDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddrEditDialog(QWidget *parent = 0);
    ~AddrEditDialog();
    Addr*values;
    Addr*getValues();
    void setValues(Addr *values);
    
private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddrEditDialog *ui;
};

#endif // ADDREDITDIALOG_H
