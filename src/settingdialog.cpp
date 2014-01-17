#include "settingdialog.h"
#include "ui_settingdialog.h"
#include "configxml.h"
#include "config.h"
#include "addreditdialog.h"

#include <QStandardItemModel>
#include <QStandardItem>
#include <QDebug>
#include <QModelIndex>
#include <QMessageBox>
#include <QList>
#include <QListWidgetItem>

SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);

    initTable();



    this->setWindowFlags(Qt::Window|Qt::FramelessWindowHint);

    ui->listWidget->setCurrentItem(ui->listWidget->item(0));
}

SettingDialog::~SettingDialog()
{
    //delete listModel;
    delete ui;

}


void SettingDialog::showEvent(QShowEvent *event){

    initTable();

}

void SettingDialog::removeConnection(){

    disconnect(ui->checkBox,0,0,0);
    disconnect(ui->widget_6,0,0,0);

}

void SettingDialog::createConnects(){

    //  connect(listModel,SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)),this,SLOT(tableValueChange(const QModelIndex &, const QModelIndex &)));

    connect(ui->checkBox,SIGNAL(clicked(bool)),this,SLOT(on_checkBox_clicked(bool)));

    connect(this,SIGNAL(changeSerials(int)),ui->widget_6,SLOT(changeSerialPort(int)));

    connect(ui->widget_6,SIGNAL(selectIndexChanged(int)),this,SLOT(serilaSelectIndexChange(int)));
    connect(ui->listWidget,SIGNAL(itemSelectionChanged()),this,SLOT(listItemSelectChange()));

    connect(ui->spinBox_3,SIGNAL(valueChanged(int)),this,SLOT(setSureButtonEnable(int)));
    connect(ui->spinBox_4,SIGNAL(valueChanged(int)),this,SLOT(setSureButtonEnable(int)));
    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(setSureButtonEnable(int)));


}

void SettingDialog::listItemSelectChange(){

    int index=ui->listWidget->currentIndex().row();

    Addr*add=ConfigXml::addrs.at(index);

    ui->addr_label->setText(QString::number(add->slaveId));
    ui->fun_02_addr_label_7->setText(QString::number(add->startAddr));
    ui->fun_02_num_label_12->setText(QString::number(add->coilNum));
    ui->fun_04_addr_label_13->setText(QString::number(add->telStartAddr));
    ui->fun_04_num_label_20->setText(QString::number(add->telColiNum));


}


void SettingDialog::tableValueChange(const QModelIndex &topLeft, const QModelIndex &bottomRight){

    ui->pushButton_5->setEnabled(true);
    ui->pushButton->setEnabled(true);

}

void SettingDialog::initTable(){

    removeConnection();

    int len=ConfigXml::addrs.length();

    ui->listWidget->clear();

    for(int i=0;i<len;i++){

        Addr*addr=ConfigXml::addrs.at(i);
        QString labName= (addr->location==1)? Config::AREA_LABEL.split("#").at(0):Config::AREA_LABEL.split("#").at(1);
        new QListWidgetItem(labName+addr->num, ui->listWidget);
    }


    ui->checkBox->setChecked(Config::isSlave);

    ui->spinBox->setValue(Config::remoteAddress);
    ui->spinBox_2->setValue(Config::localAddress);

    setBlockEnable(!Config::isSlave);

    ui->spinBox_3->setValue(Config::ndLableMin);

    ui->spinBox_4->setValue(Config::ndLableMax);

    ui->comboBox->setCurrentIndex(ui->comboBox->findText(Config::ndLableName));


    createConnects();

}


void SettingDialog::setBlockEnable(bool enable){

    // ui->tableView->setEnabled(enable);

    QString labName;

    if(enable){

        labName=tr("slave address");

    }else{

        labName=tr("host address");
    }

    ui->label->setText(labName);

}


void SettingDialog::setSureButtonEnable(int value){

    bool enabled=value>=0;

    ui->pushButton_5->setEnabled(enabled);
    ui->pushButton->setEnabled(enabled);

}


//tab 1
void SettingDialog::on_pushButton_clicked()
{

    on_pushButton_5_clicked();
    on_pushButton_3_clicked();

}

void SettingDialog::on_pushButton_5_clicked()
{
    // changeTableValue();

    Config::updateConfig("model/isSlave",ui->checkBox->isChecked()?"true":"false");

    MainForm::MasterModel model= ui->checkBox->isChecked()?MainForm::Sub:MainForm::Master;

    emit changeIsSlave(model);

    setSureButtonEnable(-1);

}



void SettingDialog::on_pushButton_3_clicked()
{
    this->setSureButtonEnable(-1);

    this->close();
}



void SettingDialog::on_checkBox_clicked(bool checked)
{
    setBlockEnable(!checked);
    ui->pushButton->setEnabled(true);
    ui->pushButton_5->setEnabled(true);


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


//edit
void SettingDialog::on_pushButton_6_clicked()
{


    int index=ui->listWidget->currentRow();

    index=index!=-1?index:0;

    Addr*add=ConfigXml::addrs.at(index);

    AddrEditDialog addEdit(this);


    addEdit.setValues(add);

    int re= addEdit.exec();

    if(re){

        listItemSelectChange();

    }

    ConfigXml::update();

    qDebug()<<re<<endl;

}
