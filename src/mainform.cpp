﻿#include "mainform.h"
#include "ui_mainform.h"
#include "settingdialog.h"
#include "logviewdialog.h"
#include "sqlutil.h"
#include "config.h"
#include "qcustlabel.h"
#include "equipmentwidget.h"
#include "configxml.h"

#include "imodbus.h"
#include "modbus.h"


#include <QWidget>
#include <QMessageBox>
#include <QMenu>
#include <QAction>
#include <QPoint>
#include <QMouseEvent>
#include <QIcon>
#include <QCloseEvent>
#include <QGridLayout>
#include <QDesktopWidget>
#include <QSound>
#include <QTimer>
#include <QDebug>


MainForm::MainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);

    initLabels();

    createActions();

    initEventerFilter();

    creatContentMenu();

    createTrayIcon();

    createEquipments();

    createLinkStatusPic();

    //remove the title bar
    this->setWindowFlags(Qt::FramelessWindowHint);

    this->setAttribute(Qt::WA_TranslucentBackground);

    this->showNormal();
    //resize(QApplication::desktop()->availableGeometry().size());
    //SQLUtil::test();

    logview=new LogViewDialog();

    isPlay=false;
    playTimer=new QTimer;
    connect(playTimer, SIGNAL(timeout()), this, SLOT(playSound()));

    transcationCreate=new QTimer;
    connect(transcationCreate, SIGNAL(timeout()), this, SLOT(createTranstration()));

    //transcationDone
    connect(&reqThread,SIGNAL(transcationDone(Transcation*)),this,SLOT(transcationIsDone(Transcation*)));

    transitionIndex=0;
    transtionTimeOut=1000;

}

void MainForm::createTranstration(){

    int index=transitionIndex%ConfigXml::addrs.length();
    if(index<0){
        index+=ConfigXml::addrs.length();
    }

    Transcation*t=new Transcation;
    t->addr=ConfigXml::addrs.at(index);
    t->funCode=2;

    this->reqThread.addTranscation(t);

    transitionIndex= (transitionIndex+1)<ConfigXml::addrs.length()?transitionIndex+1:0;





}

void MainForm::transcationIsDone(Transcation*trans){

    qDebug()<<"==============================="<<endl;

    int funCode=trans->funCode;
    int index=trans->addr->index;

    qDebug()<<"thread message index:"<<index<<endl;

    switch (funCode) {
    case 2:

        qDebug()<<"thread message from:"<<trans->addr->slaveId<<endl;
        qDebug()<<"thread message data:"<<trans->returnData<<endl;
        qDebug()<<"thread message returnCode:"<<trans->returnCode<<endl;

        if(trans->returnCode>0){

            changeEquipmentStatus(index,2,0,"");

            QStringList list=trans->returnData.split("#");

            int fault=list.at(7).toInt()==1?1:0;

            int a1=list.at(5).toInt()==1?2:0;
            int a2=list.at(4).toInt()==1?2:0;
            int a3=list.at(3).toInt()==1?3:0;

            qDebug()<<"a1,a2,a3:"<<a1<<","<<a2<<","<<a3<<endl;

            if(fault==1){

                changeEquipmentStatus(index,3,1,"");

            }else{

                changeEquipmentStatus(index,3,0,"");

            }

            int waringLevel=((a3>a2)?(a3>a1?a3:(a1>a2?a1:a3)):(a2>a1?a2:a1>a3?a1:a2));

            int  lighhtlevel= (waringLevel>0)?waringLevel:fault;

            qDebug()<<"lighhtlevel:"<<waringLevel<<" "<<lighhtlevel<<endl;


            changeEquipmentStatus(index,4,waringLevel-1,"");

            changeEquipmentStatus(index,0,lighhtlevel,"");


        }else{  //fult to link

            changeEquipmentStatus(index,2,1,"");
            changeEquipmentStatus(index,0,1,"");

        }
        break;
        //    case 3:

        //        break;
        //    case 4:

        //        break;
        //    case 6:

        //        break;
        //    case 16:

        //        break;
    default:
        break;
    }

}


void MainForm::changeEquipmentStatus(int index,int labelIndex,int data,QString info){


    EquipmentWidget*e=equipmentsList.at(index);

    e->updateLabelInfo(labelIndex,data,info);
}



MainForm::~MainForm()
{
    delete ui;
    delete contentMenu;
    delete exitAction;
    delete settingAction;
    delete trayIcon;

    delete trayIconMenu;
    delete maximizeAction;
    delete minimizeAction;

    delete logview;
    delete playTimer;
    delete transcationCreate;

}


void MainForm::initLabels(){
    ui->label->setText(Config::MAIN_TITLE);
    ui->label_12->setText(Config::AREA_LABEL.split("#").at(0).split("|").at(0));
    ui->label_13->setText(Config::AREA_LABEL.split("#").at(1).split("|").at(0));
}

/**
 * @brief MainForm::initEventerFilter
 *
 */
void MainForm::initEventerFilter(){

    ui->label_11->installEventFilter(this);
    ui->label_15->installEventFilter(this);

    ui->label_2->installEventFilter(this);
    ui->label_3->installEventFilter(this);

    ui->label_14->installEventFilter(this);
}

/**
 * @brief MainForm::createActions
 */
void MainForm::createActions(){


    settingAction=new QAction(tr("Setting"),this);
    connect(settingAction,SIGNAL(triggered()),this,SLOT(doSetting()));

    //showLogView
    logViewAction=new QAction(tr("Log"),this);
    connect(logViewAction, SIGNAL(triggered()), this, SLOT(logView()));

    exitAction=new QAction(tr("Exit"),this);
    connect(exitAction,SIGNAL(triggered()),this,SLOT(quit()));

    minimizeAction=new QAction(tr("Min"),this);
    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(showMinimized()));

    maximizeAction=new QAction(tr("Max"),this);
    connect(maximizeAction, SIGNAL(triggered()), this, SLOT(showMaximized()));

    norimizeAction=new QAction(tr("Normal"),this);
    connect(norimizeAction, SIGNAL(triggered()), this, SLOT(showNormal()));



}

/**
 * @brief MainForm::creatContentMenu
 *
 */
void MainForm::creatContentMenu(){

    contentMenu = new QMenu(this);
    contentMenu->addAction(settingAction);
    contentMenu->addAction(logViewAction);
    contentMenu->addAction(exitAction);

    trayIconMenu=new QMenu(this);
    trayIconMenu->addAction(logViewAction);
    trayIconMenu->addAction(exitAction);



}


/**
 * @brief MainForm::createTrayIcon
 *
 */
void MainForm::createTrayIcon(){

    QIcon icon = QIcon(":/icofire.ico");
    setWindowIcon(icon);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon=new QSystemTrayIcon(this);

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(backShowStyle(QSystemTrayIcon::ActivationReason)));

    trayIcon->setIcon(icon);
    trayIcon->setContextMenu(this->trayIconMenu);
    trayIcon->show();

}


void MainForm::createEquipments(){



    int len=ConfigXml::addrs.length();

    for(int i=0;i<len;i++){

        EquipmentWidget *e=new EquipmentWidget;
        int loca=ConfigXml::addrs.at(i)->location;
        if(loca==1){

            ui->widget_5->layout()->addWidget(e);

        }else{

            ui->widget_6->layout()->addWidget(e);

        }

        equipmentsList.append(e);
    }



}

/**
 * @brief MainForm::createLinkStatusPic
 *
 */
void MainForm::createLinkStatusPic(){



    QCustLabel *lab1=new QCustLabel;

    lab1->setDesInfo(tr("MainDevice"));
    lab1->setPixmap(QPixmap(QString::fromUtf8(":/computer_white.png")));

    QCustLabel*lab2=new QCustLabel;



    lab2->setDesInfo(tr(" SubI"));
    lab2->setPixmap(QPixmap(QString::fromUtf8(":/computer_white.png")));


    QCustLabel*lab3=new QCustLabel;


    lab3->setDesInfo(tr(" SubII"));
    lab3->setPixmap(QPixmap(QString::fromUtf8(":/computer_white.png")));


    QGridLayout *layout=new QGridLayout;
    layout->setMargin(0);
    layout->setSpacing(0);

    layout->addWidget(lab1,0,0,1,2);
    layout->addWidget(lab2,1,0);
    layout->addWidget(lab3,1,1);

    QWidget *newWidget=new QWidget;

    newWidget->setLayout(layout);

    ui->widget_2->layout()->addWidget(newWidget);


}


/**
 * @brief MainForm::backShowStyle
 * @param reason
 *
 */
void MainForm::backShowStyle(QSystemTrayIcon::ActivationReason reason){

    switch(reason)	 {
    //single click
    case QSystemTrayIcon::Trigger:
        //double click
    case QSystemTrayIcon::DoubleClick:
        // recover the show of the form
        if(this->isHidden()||this->isMinimized()){
            this->setWindowState(Qt::WindowActive);
            this->show();
        }else{
            this->hide();
        }

        break;
    default:
        break;
    }

}


/**
 * @brief MainForm::eventFilter
 * @param obj
 * @param event
 * @return
 *
 */
bool MainForm::eventFilter(QObject *obj, QEvent *event){

    if(obj==ui->label_11){

        if (event->type() == QEvent::MouseButtonPress) {

            showContentMenu();

            return true;
        }

    }else if(obj==ui->label_15){

        if (event->type() == QEvent::MouseButtonPress) {

            //qDebug()<<"show"<<endl;

            showLogView();

            return true;
        }
    }else if(obj==ui->label_2){

        if (event->type() == QEvent::MouseButtonPress) {

            this->close();
            return true;
        }
    }else if(obj==ui->label_3){

        if (event->type() == QEvent::MouseButtonPress) {

            this->showMinimized();
            return true;
        }
    }else if(obj==ui->label_14){

        if (event->type() == QEvent::MouseButtonPress) {

            ui->textEdit->clear();
            return true;
        }
    }


    return QWidget::eventFilter(obj,event);

}


void MainForm::chageMenuLabelBack(bool top){

    if(top){

        ui->label_11->setPixmap(QPixmap(QString::fromUtf8(":/top.png")));

    }else{

        ui->label_11->setPixmap(QPixmap(QString::fromUtf8(":/bottom.png")));

    }


}



/**
 * @brief MainForm::doSetting
 *
 */
void MainForm::doSetting(){

    SettingDialog settingDialog;

    settingDialog.exec();

}


/**
 * @brief MainForm::showContentMenu
 *
 */
void MainForm::showContentMenu(){

    chageMenuLabelBack(false);
    QPoint point=this->ui->label_11->pos();

    QPoint tPoint;

    tPoint.setX(point.x());
    tPoint.setY(point.y()+(this->ui->label_11->height()));

    this->contentMenu->exec(this->mapToGlobal(tPoint));
    chageMenuLabelBack(true);

}


/*
 * @brief MainForm::mousePressEvent
 * @param event
 * 处理鼠标按下的事件

void MainForm::mousePressEvent(QMouseEvent *event){

    //if(event->button() == Qt::LeftButton){

    //    this->dragPosition=event->globalPos() - frameGeometry().topLeft();
        event->accept();
   // }

}
 */
/*
 * @brief MainForm::mouseMoveEvent
 * @param event
 * 处理鼠标移动事件

void MainForm::mouseMoveEvent(QMouseEvent *event){

   // if ((!this->isMaximized()&&!this->isFullScreen())&&event->buttons() == Qt::LeftButton)
   // {
   //     move(event->globalPos() - dragPosition);
        event->accept();
   // }


}*/

void MainForm::logView(){

    showLogView();

}


void MainForm::quit(){

    QMessageBox message(QMessageBox::NoIcon,"",tr("Are you sure?"), QMessageBox::Yes | QMessageBox::No, NULL);

    if(message.exec() == QMessageBox::Yes)
    {
        qApp->quit();
    }

}



/**
 * @brief MainForm::showLogView
 *  显示日志管理窗口
 */
void MainForm::showLogView(){

    this->logview->show();
    //QMessageBox::warning(this,tr(""),tr(""),QMessageBox::Yes|QMessageBox::No);

}

/**
 * @brief MainForm::closeEvent
 * @param event
 * 重写窗口关闭事件,可以使窗口关闭时系统不退出
 */
void MainForm::closeEvent(QCloseEvent *event){

    if(this->trayIcon->isVisible()){
        this->hide();
        event->ignore();
    }

}


void MainForm::on_pushButton_clicked()
{
    int num=ui->lightNum->currentIndex();
    int  on=ui->onOrOff->currentIndex();
    int  status=ui->norOrBreak->currentIndex();
    int  waring=ui->lowOrHigh->currentIndex();


    EquipmentWidget*e=equipmentsList.at(num);

    e->updateLabelInfo(2,on,tr(""));

    e->updateLabelInfo(3,status,tr(""));

    e->updateLabelInfo(4,waring,tr(""));

    int waringLeve= waring>0?(waring+1):(status>0||on>0?1:0);

    e->updateLabelInfo(0,waringLeve,tr(""));

    qDebug()<<num<<" "<<on<<" "<<status<<" "<<waring<<" "<<waringLeve<<endl;


}


void MainForm::playSound(){

    QApplication::beep();
    qDebug()<<"======"<<endl;
    //  QSound::play("ala.wav");


}

/**
 * @brief MainForm::on_pushButton_2_clicked
 * Test the alarm
 */
void MainForm::on_pushButton_2_clicked()
{

    if(this->isPlay){
        if(this->playTimer->isActive()){
            this->playTimer->stop();
        }
        this->isPlay=false;

    }else{

        this->playTimer->start(300);
        this->isPlay=true;

    }

}


/**
 * @brief MainForm::on_pushButton_3_clicked
 * test request thread
 */
void MainForm::on_pushButton_3_clicked()
{
    if(reqThread.isRunning()){
        return;
    }

    this->transcationCreate->start(this->transtionTimeOut);
    reqThread.start();
}
