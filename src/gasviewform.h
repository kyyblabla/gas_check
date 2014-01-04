#ifndef GASVIEWFORM_H
#define GASVIEWFORM_H

#include <QDialog>
class QPaintEvent;
class QPainter;
class EquipmentWidget;
class QEvent;

namespace Ui {
class GasViewForm;
}

class GasViewForm : public QDialog
{
    Q_OBJECT


public:
    explicit GasViewForm(QWidget *parent = 0);
    ~GasViewForm();

    void setEquipments(QString tit, double value, int index);

    int getcurrentEquipIndex(){return currentEquipIndex;}

signals:
    void currentEquipIndexChange(int);

public  slots:


protected:
     bool eventFilter(QObject *obj, QEvent *event); //filter events, in this moment,we just attention this event of ui's label


private:
    Ui::GasViewForm *ui;
    int currentEquipIndex;
};

#endif // GASVIEWFORM_H
