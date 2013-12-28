#ifndef GASVIEWFORM_H
#define GASVIEWFORM_H

#include <QDialog>
class QPaintEvent;
class QPainter;

namespace Ui {
class GasViewForm;
}

class GasViewForm : public QDialog
{
    Q_OBJECT
    
public:
    explicit GasViewForm(QWidget *parent = 0);
    ~GasViewForm();


private:
    Ui::GasViewForm *ui;
};

#endif // GASVIEWFORM_H
