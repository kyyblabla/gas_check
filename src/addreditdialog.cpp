#include "addreditdialog.h"
#include "ui_addreditdialog.h"

AddrEditDialog::AddrEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddrEditDialog)
{
    ui->setupUi(this);
}


Addr *AddrEditDialog::getValues(){

    return this->values;

}
void AddrEditDialog::setValues(Addr*values){

    this->values=values;
    ui->spinBox_5->setValue(values->slaveId);
    ui->spinBox->setValue(values->startAddr);
    ui->spinBox_2->setValue(values->coilNum);
    ui->spinBox_3->setValue(values->telStartAddr);
    ui->spinBox_4->setValue(values->telColiNum);

}

AddrEditDialog::~AddrEditDialog()
{
    delete ui;
}

void AddrEditDialog::on_buttonBox_accepted()
{

    values->slaveId=ui->spinBox_5->value();
    values->startAddr= ui->spinBox->value();
    values->coilNum=ui->spinBox_2->value();
    values->telStartAddr=ui->spinBox_3->value();
    values->telColiNum=ui->spinBox_4->value();

}
