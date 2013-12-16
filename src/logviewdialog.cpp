#include "logviewdialog.h"
#include "config.h"
#include "ui_logviewdialog.h"

#include <QTableView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QMessageBox>
#include <QString>


LogViewDialog::LogViewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogViewDialog)
{
    ui->setupUi(this);

    initTreeView();
    initTableView();
    ui->splitter->setStretchFactor(1,5);
    ui->lineEdit->setFocus();
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

    QString areaName1=Config::AREA_LABEL.split("#").at(0).split("|").at(0);

    int len1=Config::AREA_LABEL.split("#").at(0).split("|").at(1).split("/").length();

    for(int i=0;i<len1;i++){

        QStandardItem *item = new QStandardItem(areaName1+Config::AREA_LABEL.split("#").at(0).split("|").at(1).split("/").at(i));
        treeModel->appendRow(item);
    }


    QString areaName2=Config::AREA_LABEL.split("#").at(1).split("|").at(0);
    int len2=Config::AREA_LABEL.split("#").at(1).split("|").at(1).split("/").length();

    for(int i=0;i<len2;i++){

        QStandardItem *item = new QStandardItem(areaName2+Config::AREA_LABEL.split("#").at(1).split("|").at(1).split("/").at(i));
        treeModel->appendRow(item);
    }

    ui->treeView->setModel(treeModel);

}
