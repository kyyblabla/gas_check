#include "gasviewform.h"
#include "ui_gasviewform.h"
#include <QPaintEvent>
#include <QPainter>
#include <QPen>

GasViewForm::GasViewForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GasViewForm)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Window);
}

GasViewForm::~GasViewForm()
{
    delete ui;

}



