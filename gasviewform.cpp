#include "gasviewform.h"
#include "ui_gasviewform.h"

#include <QPaintEvent>
#include <QPainter>

GasViewForm::GasViewForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GasViewForm)
{
    ui->setupUi(this);


}

GasViewForm::~GasViewForm()
{
    delete ui;
}


void GasViewForm::paintEvent(QPaintEvent *event){

    QPainter painter(this);


    painter.drawArc(10,10,100,100,-45,270);



}
