#include "settingdialog.h"
#include "ui_settingdialog.h"
#include "configxml.h"
#include "config.h"

#include <QStandardItemModel>
#include <QStandardItem>
#include <QDebug>
#include <QModelIndex>
#include <QMessageBox>

SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);

    initTable();

    createConnects();

    this->setWindowFlags(Qt::Window);


}

SettingDialog::~SettingDialog()
{
    delete tableModel;
    delete ui;

}

void SettingDialog::createConnects(){

    connect(tableModel,SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)),this,SLOT(tableValueChange(const QModelIndex &, const QModelIndex &)));

    connect(ui->checkBox,SIGNAL(clicked(bool)),this,SLOT(on_checkBox_clicked(bool)));

    connect(this,SIGNAL(changeSerials(int)),ui->widget_6,SLOT(changeSerialPort(int)));

    connect(ui->widget_6,SIGNAL(selectIndexChanged(int)),this,SLOT(serilaSelectIndexChange(int)));


}

void SettingDialog::tableValueChange(const QModelIndex &topLeft, const QModelIndex &bottomRight){

    ui->pushButton_5->setEnabled(true);
    ui->pushButton->setEnabled(true);

}

void SettingDialog::initTable(){


    tableModel=new QStandardItemModel;

    tableModel->setColumnCount(6);

    tableModel->setHeaderData(0,Qt::Horizontal,tr("Name"));
    tableModel->setHeaderData(1,Qt::Horizontal,tr("Slave Id"));
    tableModel->setHeaderData(2,Qt::Horizontal,tr("Start Address"));
    tableModel->setHeaderData(3,Qt::Horizontal,tr("Number of Colis"));

    tableModel->setHeaderData(4,Qt::Horizontal,tr("Start TelAddress"));
    tableModel->setHeaderData(5,Qt::Horizontal,tr("Number of TelColis"));

    int len=ConfigXml::addrs.length();

    for(int i=0;i<len;i++){

        Addr*addr=ConfigXml::addrs.at(i);
        QString labName= (addr->location==1)? Config::AREA_LABEL.split("#").at(0):Config::AREA_LABEL.split("#").at(1);

        tableModel->setItem(i,0,new QStandardItem(labName+addr->num));
        tableModel->setItem(i,1,new QStandardItem(QString::number(addr->slaveId)));
        tableModel->setItem(i,2,new QStandardItem(QString::number(addr->startAddr)));
        tableModel->setItem(i,3,new QStandardItem(QString::number(addr->coilNum)));

        tableModel->setItem(i,4,new QStandardItem(QString::number(addr->telStartAddr)));
        tableModel->setItem(i,5,new QStandardItem(QString::number(addr->telColiNum)));


    }


    ui->tableView->setModel(tableModel);

    ui->tableView->resizeColumnsToContents();

    ui->checkBox->setChecked(Config::isSlave);

    setBlockEnable(!Config::isSlave);

}

void SettingDialog::setBlockEnable(bool enable){

    ui->tableView->setEnabled(enable);
    ui->widget_6->setEnabled(enable);

    QString labName;

    if(enable){

        labName=tr("slave address");

    }else{

        labName=tr("host address");
    }

    ui->label->setText(labName);

}

void SettingDialog::changeTableValue(){

    for(int i=0;i<this->tableModel->rowCount();i++){

        if(i>=ConfigXml::addrs.length()){
            break;
        }
        int slaveId;
        int addrStart,addrTelStart;
        int coilNum,telCoilNum;

        try{
            slaveId=tableModel->item(i,1)->text().toInt();
        }catch(QString exception){

            QMessageBox::about(this,tr("Error"),tr("slaveId must be num!"));
            return;
        }

        try{
            addrStart=tableModel->item(i,2)->text().toInt();
        }catch(QString exception){

            QMessageBox::about(this,tr("Error"),tr("addrStart must be num!"));
            return;
        }

        try{
            coilNum=tableModel->item(i,3)->text().toInt();
        }catch(QString exception){

            QMessageBox::about(this,tr("Error"),tr("coilNum must be num!"));
            return;
        }

        try{
            addrTelStart=tableModel->item(i,4)->text().toInt();
        }catch(QString exception){

            QMessageBox::about(this,tr("Error"),tr("addrTelStart must be num!"));
            return;
        }

        try{
            telCoilNum=tableModel->item(i,5)->text().toInt();
        }catch(QString exception){

            QMessageBox::about(this,tr("Error"),tr("telCoilNum must be num!"));
            return;
        }

        ConfigXml::addrs.at(i)->slaveId=slaveId;
        ConfigXml::addrs.at(i)->startAddr=addrStart;
        ConfigXml::addrs.at(i)->coilNum=coilNum;
        ConfigXml::addrs.at(i)->telStartAddr=addrTelStart;
        ConfigXml::addrs.at(i)->telColiNum=telCoilNum;


    }

    ConfigXml::update();

}





//tab 1
void SettingDialog::on_pushButton_clicked()
{

    on_pushButton_5_clicked();

    on_pushButton_3_clicked();
}

void SettingDialog::on_pushButton_5_clicked()
{
    changeTableValue();
    ui->pushButton_5->setEnabled(false);
    ui->pushButton->setEnabled(false);

}


void SettingDialog::on_pushButton_3_clicked()
{
    this->close();
}

void SettingDialog::on_checkBox_clicked(bool checked)
{
    Config::updateConfig("model/isSlave",checked?"true":"false");
    setBlockEnable(!Config::isSlave);

}


//tab2

void SettingDialog::on_pushButton_8_clicked()
{
    emit changeSerials(1);
    ui->pushButton_8->setEnabled(false);
    ui->pushButton_7->setEnabled(false);
}


void SettingDialog::on_pushButton_7_clicked()
{
    on_pushButton_8_clicked();
    on_pushButton_9_clicked();

}


void SettingDialog::on_pushButton_9_clicked()
{
    on_pushButton_3_clicked();
}


void SettingDialog::serilaSelectIndexChange(int){

    ui->pushButton_8->setEnabled(true);
    ui->pushButton_7->setEnabled(true);

}
