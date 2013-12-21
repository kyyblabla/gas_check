#include "logviewdialog.h"
#include "config.h"
#include "ui_logviewdialog.h"
#include "configxml.h"

#include <QTableView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QMessageBox>
#include <QString>
#include <QDebug>


LogViewDialog::LogViewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogViewDialog)
{
    ui->setupUi(this);

    initTreeView();
    initTableView();
    ui->splitter->setStretchFactor(1,5);
    ui->lineEdit->setFocus();
    this->setWindowFlags(Qt::Window);
}

LogViewDialog::~LogViewDialog()
{
    delete ui;
    delete tableModel;
    delete treeModel;

}


void LogViewDialog::initTableView(){


    tableModel=new QStandardItemModel;

    tableModel->setColumnCount(4);

    tableModel->setHeaderData(0,Qt::Horizontal,tr("ID"));
    tableModel->setHeaderData(1,Qt::Horizontal,tr("Detial"));
    tableModel->setHeaderData(2,Qt::Horizontal,tr("Create Time"));
    tableModel->setHeaderData(3,Qt::Horizontal,tr("Deal Time"));

    ui->tableView->setModel(tableModel);

}


void LogViewDialog::initTreeView(){

    treeModel=new QStandardItemModel;


    QStandardItem *itemAll = new QStandardItem(tr("all"));

    treeModel->appendRow(itemAll);


    int len=ConfigXml::addrs.length();

    for(int i=0;i<len;i++){

        Addr*addr=ConfigXml::addrs.at(i);
        QString labName= (addr->location==1)? Config::AREA_LABEL.split("#").at(0):Config::AREA_LABEL.split("#").at(1);

        QStandardItem *item = new QStandardItem(labName+addr->num);
        treeModel->appendRow(item);

    }

    ui->treeView->setModel(treeModel);



}
