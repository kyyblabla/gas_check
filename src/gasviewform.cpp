#include "gasviewform.h"
#include "ui_gasviewform.h"
#include "equipmentwidget.h"
#include "gasviewwidget.h"

#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <QEvent>

GasViewForm::GasViewForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GasViewForm)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Window);

    currentEquipIndex=0;

    ui->label_2->installEventFilter(this);
    ui->label_3->installEventFilter(this);

}

GasViewForm::~GasViewForm()
{
    delete ui;
}


void GasViewForm::setEquipments(QString tit, double value,int index){

    ui->widget->setGanNd(value);
    ui->label->setText(tit);
    this->currentEquipIndex=index;

}


bool GasViewForm::eventFilter(QObject *obj, QEvent *event){

    if(obj==ui->label_2){

        if (event->type() == QEvent::MouseButtonPress) {

            emit currentEquipIndexChange(++currentEquipIndex);
            return true;
        }
    }else if(obj==ui->label_3){

        if (event->type() == QEvent::MouseButtonPress) {

            emit currentEquipIndexChange(--currentEquipIndex);
            return true;
        }
    }

}
