#include "mainform.h"
#include "ui_mainform.h"
#include "settingdialog.h"
#include "logviewdialog.h"
#include "sqlutil.h"
#include "config.h"
#include "qcustlabel.h"
#include "equipmentwidget.h"
#include "configxml.h"
#include "dialpan.h"
#include "sqlite.h"


#include "imodbus.h"
#include "modbus.h"

#include <QDateTime>
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
#include <QGraphicsDropShadowEffect>
#include <QStackedLayout>
#include <QHBoxLayout>


extern MainForm * globalMainWin;

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

    //remove the title bar
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->showNormal();

    logview=new LogViewDialog;

    this->settingDialog=new SettingDialog;

    connect(settingDialog,SIGNAL(changeIsSlave(MainForm::MasterModel)),this,SLOT(modelChange(MainForm::MasterModel)));

    changeStackIndex(0);

    initTimerAndThread();



}


void MainForm::initTimerAndThread(){

    isPlay=false;

    playTimer=new QTimer;
    connect(playTimer, SIGNAL(timeout()), this, SLOT(playSound()));

    transcationCreate=new QTimer;
    connect(transcationCreate, SIGNAL(timeout()), this, SLOT(createTranstration()));

    pollTimer=new QTimer;

    connect(pollTimer, SIGNAL(timeout()), this, SLOT(pollForDataOnBus()));

    reqThread= new ModbusRequestThread;
    //transcationDone
    connect(reqThread,SIGNAL(transcationDone(Transcation*)),this,SLOT(transcationIsDone(Transcation*)));

    transitionIndex=0;

    if(Config::isSlave){

        pollTimer->start(10);

        this->masterModel=Sub;

    }else{

        this->transcationCreate->start(Config::sleepTime);
        reqThread->start();
        this->masterModel=Master;
    }

}



void MainForm::changeStackIndex(int index){



    ui->stackedWidget->setCurrentIndex(index);

    if(index==0){

        ui->float_menu->setVisible(false);

        ui->main_view->setVisible(true);

    }else if(index==1){

        ui->float_menu->setVisible(true);

        ui->main_view->setVisible(true);

    }

}

void MainForm::modelChange(MainForm::MasterModel model){


    this->masterModel=model;
    switch (model) {

    case Master:
    case SubToMaster:
        if(this->pollTimer->isActive()){
            this->pollTimer->stop();
        }

        if(!this->transcationCreate->isActive()){
            this->transcationCreate->start(Config::sleepTime);
        }

        if(!this->reqThread->isRunning()){
            this->reqThread->start();
        }
        break;
    case Sub:
    case MasterToSub:

        if(this->transcationCreate->isActive()){
            this->transcationCreate->stop();
        }

        if(this->reqThread->isRunning()){
            this->reqThread->stopReq();
        }

        if(!this->pollTimer->isActive()){
            this->pollTimer->start(15);
        }
        break;
    default:
        break;
    }



}

void MainForm::pollForDataOnBus()
{
    if( ModbusRequestThread::m_modbus )
    {
        modbus_poll( ModbusRequestThread::m_modbus );
    }
}


void MainForm::createTranstration(){

    int index=transitionIndex%ConfigXml::addrs.length();

    if(index<0){
        index+=ConfigXml::addrs.length();
    }

    Transcation*t=new Transcation;

    t->addr=ConfigXml::addrs.at(index);

    t->funCode=2;

    this->reqThread->addTranscation(t);

    Transcation*t2=new Transcation;

    t2->addr=ConfigXml::addrs.at(index);

    t2->funCode=4;

    this->reqThread->addTranscation(t2);

    transitionIndex= (transitionIndex+1)<ConfigXml::addrs.length()?transitionIndex+1:0;

}

void MainForm::transcationIsDone(Transcation*trans){

    qDebug()<<"==============================="<<endl;

    int funCode=trans->funCode;
    int index=trans->addr->index;


    bool change=false;

    qDebug()<<"thread message index:"<<index<<endl;
    qDebug()<<"thread message returnCode:"<<trans->returnCode<<endl;
    qDebug()<<"thread message funccode:"<<trans->funCode<<endl;


    switch (funCode) {
    case 2:

        if(trans->returnCode>0){

            change=changeEquipmentStatus(index,2,0);
            if(change){
                addLogInfo(index,2,0);
            }

            qDebug()<<"thread message Data:"<<trans->returnData<<endl;

            QStringList list=trans->returnData.split("#");

            int fault=list.at(7).toInt()==1?1:0;

            int a1=list.at(5).toInt()==1?2:0;
            int a2=list.at(4).toInt()==1?2:0;
            int a3=list.at(3).toInt()==1?3:0;

            if(fault==1){

                change = changeEquipmentStatus(index,3,1);
                if(change){
                    addLogInfo(index,3,1);
                }
                return;

            }else{

                change=changeEquipmentStatus(index,3,0);
                if(change){
                    addLogInfo(index,3,0);
                }


            }

            int waringLevel=((a3>a2)?(a3>a1?a3:(a1>a2?a1:a3)):(a2>a1?a2:a1>a3?a1:a2));

            change= changeEquipmentStatus(index,4,waringLevel);


        }else{  //fult to link

            change=changeEquipmentStatus(index,2,1);

            if(change){
                addLogInfo(index,2,1);
            }

        }

        break;
    case 4:

        if(trans->returnCode>0){

            qDebug()<<"thread message Data 4:"<<trans->returnData<<endl;
            QStringList list=trans->returnData.split("#");

            int gasNd=list.at(0).toInt();

            change=changeEquipmentStatus(index,1,gasNd);


        }else{


            change=changeEquipmentStatus(index,1,0);
            if(change){
                addLogInfo(index,1,0);
            }
        }


        break;

    default:
        break;
    }

}

void MainForm::addLogInfo(int equipmentIndex, int labelIndex, int statu){



    Addr*addr=ConfigXml::addrs.at(equipmentIndex);

    QString labName= (addr->location==1)? Config::AREA_LABEL.split("#").at(0):Config::AREA_LABEL.split("#").at(1);

    labName=labName+addr->num;

    QString detila;

    if(labelIndex==2){

        if(statu==1){

            detila+=labName+tr(":not work!");

        }else{

            detila+=labName+tr(":continue to work.");

        }


    }else if(labelIndex==3){

        if(statu==1){

            detila+=labName+tr(":fault!");

        }else{
            detila+=labName+tr(":fault is dispear.");
        }

    }else if(labelIndex==4){

        if(statu==3){

            detila+=labName+tr(":high waring!");

        }else if(statu==2){

            detila+=labName+tr(":low waring");
        }else{

            detila+=labName+tr(":waring dispaer.");

        }

    }

    detila="["+QDateTime::currentDateTime().toLocalTime().toString()+"]"+detila;

    ui->textEdit->append(detila);

    //    Log log;

    //    log.logCreateTime=QDateTime::currentDateTime().toLocalTime();
    //    log.logDetial=detila;
    //    log.logId="";
    //    log.logSolveTime="";




}

bool MainForm::changeEquipmentStatus(int index,int labelIndex,int data){

    EquipmentWidget*e=equipmentsList.at(index);
    return  e->updateLableValue(labelIndex,data);

}



MainForm::~MainForm()
{
    //this->transcationCreate->stop();
    // this->pollTimer->stop();



    delete ui;
    delete exitAction;
    delete settingAction;
    delete trayIcon;
    delete trayIconMenu;
    delete logview;
    delete playTimer;
    delete transcationCreate;
    delete reqThread;
    delete pollTimer;
    delete settingDialog;



}


void MainForm::initLabels(){


    ui->label->setText(Config::MAIN_TITLE);
    //    ui->label_12->setText(Config::AREA_LABEL.split("#").at(0));
    //    ui->label_13->setText(Config::AREA_LABEL.split("#").at(1));
    //ui->stackedWidget_4->setCurrentIndex(0);

    QStackedLayout*laylout=(QStackedLayout*)ui->stackedWidget->layout();
    laylout->setStackingMode(QStackedLayout::StackAll);

    //ui->widget->setStyleSheet("border-color:#fff;border-width:1px;border-style:solid");

    ui->widget_8->isConnection(true);

}

/**
 * @brief MainForm::initEventerFilter
 *
 */
void MainForm::initEventerFilter(){




    ui->label_16->installEventFilter(this);

    ui->label_17->installEventFilter(this);
    ui->label_18->installEventFilter(this);



    ui->main_view->installEventFilter(this);
    ui->float_menu->installEventFilter(this);
}

/**
 * @brief MainForm::createActions
 */
void MainForm::createActions(){


    settingAction=new QAction(tr("Setting"),this);
    connect(settingAction,SIGNAL(triggered()),this,SLOT(doSetting()));

    //  showLogView
    logViewAction=new QAction(tr("Log"),this);
    connect(logViewAction, SIGNAL(triggered()), this, SLOT(doLogView()));

    exitAction=new QAction(tr("Exit"),this);
    connect(exitAction,SIGNAL(triggered()),this,SLOT(quit()));

}


void MainForm::doLogView(){

    this->showLogView();
}
/**
 * @brief MainForm::creatContentMenu
 *
 */
void MainForm::creatContentMenu(){



    trayIconMenu=new QMenu(this);
    trayIconMenu->addAction(this->settingAction);
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

        Addr*addr=ConfigXml::addrs.at(i);

        QString labName= (addr->location==1)? Config::AREA_LABEL.split("#").at(0):Config::AREA_LABEL.split("#").at(1);

        labName=labName+addr->num;

        EquipmentWidget*e=new EquipmentWidget;
        // dialpan*dia=new dialpan;
        e->setTitle(labName);

        ui->widget_5->layout()->addWidget(e);

        this->equipmentsList.append(e);

    }

    qDebug()<<"equipmentsList:"<<equipmentsList.size()<<endl;

    //ui->widget_5->setStyleSheet("border-color:#fff;border-style:solid;border-width:1px;");


}

/*
void MainForm::createLinkStatusPic(){


    QCustLabel *lab1=new QCustLabel;
    lab1->setDesInfo(Config::LINKSTATUS_LABEL.split("#").at(0));
    lab1->setPixmap(QPixmap(QString::fromUtf8(":/computer_white.png")));
    lab1->setLabelType(QCustLabel::MainDevice);


    QCustLabel*lab2=new QCustLabel;
    lab2->setDesInfo(Config::LINKSTATUS_LABEL.split("#").at(1));
    lab2->setPixmap(QPixmap(QString::fromUtf8(":/computer_white.png")));


    QCustLabel*lab3=new QCustLabel;
    lab3->setDesInfo(Config::LINKSTATUS_LABEL.split("#").at(2));
    lab3->setPixmap(QPixmap(QString::fromUtf8(":/computer_white.png")));




    QGridLayout *layout=new QGridLayout;
    layout->setMargin(0);
    layout->setSpacing(0);

    layout->addWidget(lab1,0,0,1,2);
    layout->addWidget(lab2,1,0);
    layout->addWidget(lab3,1,1);

    // QWidget *newWidget=new QWidget;
    // newWidget->setLayout(layout);
    //newWidget->setStyleSheet("*{border-style:solid;border-color:#000;border-width:1px}");

    ui->widget_2->setLayout(layout);


}

 */


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

    if(obj==ui->label_17){

        if (event->type() == QEvent::MouseButtonPress) {

            this->showLogView();
            return true;
        }

    }else if(obj==ui->label_16){

        if (event->type() == QEvent::MouseButtonPress) {

            this->doSetting();
            return true;
        }

    }else if(obj==ui->label_18){

        if (event->type() == QEvent::MouseButtonPress) {

            this->quit();
            return true;

        }

    }else if(obj==ui->main_view){

        if (event->type() == QEvent::MouseButtonPress) {


            this->changeStackIndex(1);

            return true;

        }

    }else if(obj==ui->float_menu){

        if (event->type() == QEvent::MouseButtonPress) {


            this->changeStackIndex(0);

            return true;

        }

    }

    return QWidget::eventFilter(obj,event);

}





/**
 * @brief MainForm::doSetting
 *
 */
void MainForm::doSetting(){

    settingDialog->show();

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

void MainForm::playSound(){

    QApplication::beep();

}






//void MainForm::addLogInfo(QString info,int index,int level){

//    Addr*addr=ConfigXml::addrs.at(index);
//    QString loca;

//    loca=(addr->location==1)?Config::AREA_LABEL.split("#").at(0):Config::AREA_LABEL.split("#").at(1);


//    info="<span style='color:"+Config::colorLevel.split("|").at(level)+"'>"+info+"</span>";

//    ui->textEdit->append("["+QDateTime::currentDateTime().toLocalTime().toString()+"]"+loca+addr->num+":"+info);


//}

void MainForm::doReceiveData(QString data){

    qDebug()<<"data"<<data<<endl;

}


extern "C" {

void busMonitorAddItem( uint8_t isRequest, uint8_t slave, uint8_t func, uint16_t addr, uint16_t nb, uint16_t expectedCRC, uint16_t actualCRC )
{




}

void busMonitorRawData( uint8_t * data, uint8_t dataLen, uint8_t addNewline )
{
    qDebug()<<"busMonitorRawData:"<<endl;

    if( dataLen > 0 )
    {
        QString dump = "";
        for( int i = 0; i < dataLen; ++i )
        {
            dump += QString().sprintf( "%.2x ", data[i] );
        }
        if( addNewline )
        {
            dump += "\n";
        }

        qDebug()<<dump<<endl;
    }


}

int busMonitorReceiveMes(uint8_t * data, uint8_t dataLen){



    //   int len = sizeof(data);
    //    QString dump = "";
    //    for( int i = 0; i < len; ++i )
    //    {
    //        dump += QString().sprintf( "%.2x ", data[i] );
    //    }

    //  //  globalMainWin->doReceiveData(dump);
    //qDebug()<<"busMonitorRawData:"<<dump<<endl;

    // if(len>=15){
    //0   1    2  3      4  5   6    7  8   9  10  11
    //01  10   01 01     00 03  06   00 00  00 00  00 00
    //id  fun  startAdd  num    len  d1     a2     d3
    int id= data[0];
    int fun=data[1];


    if(id!=Config::localAddress||fun!=16){

        return -1;

    }


    int startAdd=data[2]<<8|data[3];
    int num=data[5];
    qDebug()<<"id:"<<id<<" fun:"<<fun<<" startAdd:"<<startAdd<<" num:"<<num<<endl;

    int dataStart=7;
    int count=0;

    for(int i=0;i<num;i++){

        int value= data[dataStart+2*i]<<8|data[dataStart+2*i+1];
        qDebug()<<"value"<<i<<":"<<value<<endl;

        count=dataStart+2*i+1+1;
    }

    return count;

    //}




    return -1;


}

}
