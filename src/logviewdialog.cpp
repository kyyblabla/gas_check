#include "logviewdialog.h"
#include "config.h"
#include "ui_logviewdialog.h"
#include "configxml.h"


#include <QListWidgetItem>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <QFileDialog>


LogViewDialog::LogViewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogViewDialog)
{
    ui->setupUi(this);

    initTableView();
    initTreeView();

    createConnection();

    ui->lineEdit->setFocus();
    this->setWindowFlags(Qt::Window|Qt::FramelessWindowHint);

    this->logList=new QList<Log>;

    //ui->listWidget->setVisible(false);
    ui->checkBox->setVisible(false);
    ui->comboBox->setVisible(false);

    doShowLog();

}

LogViewDialog::~LogViewDialog()
{
    delete ui;
    delete tableModel;
    delete logList;
}

void LogViewDialog::createConnection(){

    connect(ui->listWidget,SIGNAL(itemSelectionChanged()),this,SLOT(doShowLog()));
}


void LogViewDialog::showLogs(){

    tableModel->removeRows(0,tableModel->rowCount());

    for(int i=0;i<logList->size();i++){

        Log l=logList->at(i);

        // tableModel->setItem(i,0,new QStandardItem(QString::number(l.logId)));
        tableModel->setItem(i,0,new QStandardItem(l.logCreateTime));
        tableModel->setItem(i,1,new QStandardItem(l.logDetial));
        tableModel->setItem(i,2,new QStandardItem(l.logSolveTime));
        //     student_model->setItem(0, 0, new QStandardItem(“张三"))
    }


    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();

}

void LogViewDialog::doShowLog(){


    int index=ui->listWidget->currentIndex().row();

    this->logList->clear();

    if(index>0){

        index--;

        QString key= ui->listWidget->currentItem()->text();


        SQLUtil::getByKeyWord(key,this->logList);


    }else{

        SQLUtil::getAll(this->logList);

    }

    showLogs();

}




void LogViewDialog::initTableView(){


    tableModel=new QStandardItemModel;

    tableModel->setColumnCount(3);

    //tableModel->setHeaderData(0,Qt::Horizontal,tr("ID"));
    tableModel->setHeaderData(0,Qt::Horizontal,tr("Create Time"));
    tableModel->setHeaderData(1,Qt::Horizontal,tr("Detial"));
    tableModel->setHeaderData(2,Qt::Horizontal,tr("Deal Time"));




    ui->tableView->setModel(tableModel);

}


void LogViewDialog::initTreeView(){

    int len=ConfigXml::addrs.length();

    new QListWidgetItem(tr("All"), ui->listWidget);

    for(int i=0;i<len;i++){

        Addr*addr=ConfigXml::addrs.at(i);
        QString labName= (addr->location==1)? Config::AREA_LABEL.split("#").at(0):Config::AREA_LABEL.split("#").at(1);
        new QListWidgetItem(labName+addr->num, ui->listWidget);

    }


}

void LogViewDialog::on_pushButton_4_clicked()
{
    this->close();
}


void LogViewDialog::on_pushButton_3_clicked()
{
    QString fileName= QFileDialog::getOpenFileName(this,"open file","/","xls file(*.xls);;txt file(*.txt)");

    bool re=false;

    if(fileName.endsWith(".txt")){

        re=SQLUtil::save_txt(this->logList,fileName);

    }else  if(fileName.endsWith(".xls")){

        re=SQLUtil::save_excel(this->logList,fileName);
    }else{

        return;
    }

    QString info;


    if(re){

        info =tr("save success!");

    }else{

        info =tr("save fail! check file is exist!");

    }

    QMessageBox message(QMessageBox::Information,tr("dump result"),info, QMessageBox::Yes,NULL);

    message.exec();

}


//search
void LogViewDialog::on_pushButton_clicked()
{
    QString key=ui->lineEdit->text().trimmed();

    this->logList->clear();

    SQLUtil::getByKeyWord(key,this->logList);

    showLogs();


}
