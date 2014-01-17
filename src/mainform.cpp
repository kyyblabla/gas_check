#include "mainform.h"
#include "ui_mainform.h"
#include "settingdialog.h"
#include "logviewdialog.h"

#include "config.h"
#include "qcustlabel.h"
#include "equipmentwidget.h"
#include "configxml.h"
#include "dialpan.h"

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
#include <QShowEvent>
#include <QGridLayout>
#include <QDesktopWidget>
#include <QSound>
#include <QTimer>
#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsOpacityEffect>
#include <QStackedLayout>
#include <QHBoxLayout>
#include <QFrame>



extern MainForm * globalMainWin;
extern modbus_t * m_modbus;

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

    startMiontor();


}


void MainForm::initTimerAndThread(){


   // qDebug()<<"initTimerAndThread"<<endl;

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



}


bool MainForm::checkModbus(){

    if(m_modbus!=NULL){

        modbus_close(  m_modbus);
        modbus_free(  m_modbus );
        m_modbus = NULL;

    }

    char parity;
    if(Config::serialParity=="even"){
        parity = 'E';
    }else if(Config::serialParity=="odd"){
        parity = 'O';
    }else{
        parity = 'N';
    }

    m_modbus = modbus_new_rtu(Config::serialinterface.toAscii().constData(), Config::serialBaudRate,  parity,Config::serialDatabits,Config::serialStopbits );

    int re=  modbus_connect( m_modbus );

   // qDebug()<<"re:"<<re<<endl;

    return re != -1;
}

void MainForm::startMiontor(){


  //  qDebug()<<"showEvent"<<endl;

    m_modbus = NULL;

    if(!checkModbus())
    {
        int re= QMessageBox::critical( this, tr( "Connection failed" ),tr( "Could not connect serial port! Do you want to have a setting?" ),QMessageBox::Yes,QMessageBox::No);

        if(re==QMessageBox::Yes){
            this->doSetting();
        }

    }else{

        if(Config::isSlave){

            modelChange(Sub);

        }else{

            modelChange(Master);

        }


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

        updateLastWaitTime();

        break;
    default:
        break;
    }

    this->linkHostFailCount=0;

    ui->widget_8->isConnection(true);
}

void MainForm::pollForDataOnBus()
{

   // qDebug()<<"pollForDataOnBus"<<endl;

    if(m_modbus!=NULL)
    {
        long currt=QDateTime::currentMSecsSinceEpoch();

      //  qDebug()<<"curr:"<<currt<<" last:"<<this->lastUpdateTime<<" plus:"<<currt-this->lastUpdateTime<<endl;

        if(currt-this->lastUpdateTime>=Config::slaveWaitTimeOut){

            this->modelChange(Master);
            this->addLogInfo(0,-1,0,"");
            Config::updateConfig("model/isSlave","false");

        }else{

            modbus_poll(m_modbus);

        }
    }
}

void MainForm::updateLastWaitTime(){


    this->lastUpdateTime=QDateTime::currentMSecsSinceEpoch();

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

   // qDebug()<<"==============================="<<endl;

    int funCode=trans->funCode;
    int index=trans->addr->index;




  //  qDebug()<<"thread message index:"<<index<<endl;
   // qDebug()<<"thread message returnCode:"<<trans->returnCode<<endl;
   // qDebug()<<"thread message funccode:"<<trans->funCode<<endl;


    switch (funCode) {
    case 2:

        if(trans->returnCode>0){

            changeEquipmentStatus(index,2,0);


           // qDebug()<<"thread message Data:"<<trans->returnData<<endl;

            QStringList list=trans->returnData.split("#");

            int fault=list.at(7).toInt()==1?1:0;

            int a1=list.at(5).toInt()==1?2:0;
            int a2=list.at(4).toInt()==1?2:0;
            int a3=list.at(3).toInt()==1?3:0;

            if(fault==1){

                changeEquipmentStatus(index,3,1);

                return;

            }else{

                changeEquipmentStatus(index,3,0);

            }

            int waringLevel=((a3>a2)?(a3>a1?a3:(a1>a2?a1:a3)):(a2>a1?a2:a1>a3?a1:a2));

            changeEquipmentStatus(index,4,waringLevel);


        }else{  //fult to link

            changeEquipmentStatus(index,2,1);
        }

        break;
    case 4:

        if(trans->returnCode>0){

            //    qDebug()<<"thread message Data 4:"<<trans->returnData<<endl;
            QStringList list=trans->returnData.split("#");

            int gasNd=list.at(0).toInt();

            changeEquipmentStatus(index,1,gasNd);

        }else{

            changeEquipmentStatus(index,1,0);
        }
        break;

    default:
        break;
    }

}

void MainForm::addLogInfo(int equipmentIndex, int labelIndex, int statu,QString data){

    Addr*addr=ConfigXml::addrs.at(equipmentIndex);

    QString labName= (addr->location==1)? Config::AREA_LABEL.split("#").at(0):Config::AREA_LABEL.split("#").at(1);

    labName=labName+addr->num;

    QString detila="";

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

    }else{

        detila+= tr("can't receive any data from master! Try to be Master!");
    }


    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss");

    Log log;

    log.logCreateTime=str;
    log.logDetial=detila;

    SQLUtil::add(log);

    ui->textEdit->append("["+str+"]"+detila);


}


void MainForm::changeEquipmentStatus(int index,int labelIndex,int data){

    if(index<equipmentsList.length()){

        EquipmentWidget*e=equipmentsList.at(index);
        if(e->updateLableValue(labelIndex,data)){
            addLogInfo(index,labelIndex,data,"");
        }

        if(labelIndex==2&&data>0){

            linkHostFailCount++;

            if(linkHostFailCount>Config::linkHostFailMaxCount){

                ui->widget_8->setLinkStatu(1,true);

            }


        }else if(labelIndex==2&&data==0){

            linkHostFailCount=0;
            ui->widget_8->setLinkStatu(1,false);

        }

    }


}

bool MainForm::changeEquipmentStatusById(int id,int labelIndex,int data){

    for(int i=0;i<ConfigXml::addrs.length();i++){

        if(ConfigXml::addrs.at(i)->slaveId==id){

            EquipmentWidget*e=this->equipmentsList.at(i);

            if(e->updateLableValue(labelIndex,data)){

                addLogInfo(i,labelIndex,data,"");

            }

        }

    }

}




MainForm::~MainForm()
{

    qDebug()<<"~MainForm"<<endl;

    if(this->pollTimer->isActive()){

        pollTimer->stop();
    }

    qDebug()<<"~MainForm11111"<<endl;

    if(this->transcationCreate->isActive()){

        transcationCreate->stop();
    }

    qDebug()<<"~MainForm22222"<<endl;

        if(this->reqThread->isRunning()){

           reqThread->exit();
        }


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


    //QGraphicsOpacityEffect *effect1 = new QGraphicsOpacityEffect(this);
    //  effect1->setOpacity(0.8);
    // ui->widget_6->setStyleSheet("background-color:#000");
    // ui->widget_6->setGraphicsEffect(effect1);



    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(this);
    effect->setOpacity(0.9);
    // ui->widget_4->setStyleSheet("background-color:#fff");
    ui->widget_4->setGraphicsEffect(effect);


    //ui->widget->setStyleSheet("border-color:#fff;border-width:1px;border-style:solid");

    //ui->widget_8->isConnection(true);

}

/**
 * @brief MainForm::initEventerFilter
 *
 */
void MainForm::initEventerFilter(){


    ui->label_16->installEventFilter(this);

    ui->label_17->installEventFilter(this);
    ui->label_18->installEventFilter(this);

    ui->label_2->installEventFilter(this);

    ui->label_3->installEventFilter(this);



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

        e->setVisible(i);

        ui->widget_5->layout()->addWidget(e);


        this->equipmentsList.append(e);

    }


    //ui->widget_5->setStyleSheet("border-bottom-color:#fff;border-bottom-style:solid;border-bottom-width:1px;");


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

    }else if(obj==ui->label_2){

        if (event->type() == QEvent::MouseButtonPress) {




            return true;

        }

    }else if(obj==ui->label_3){

        if (event->type() == QEvent::MouseButtonPress) {

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

    QMessageBox message(QMessageBox::Information,tr("sure to exit"),tr("Are you sure?"), QMessageBox::Yes | QMessageBox::No, NULL);

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


void MainForm::doReceiveData(QString data){

   // qDebug()<<"data"<<data<<endl;

}


extern "C" {

void busMonitorAddItem( uint8_t isRequest, uint8_t slave, uint8_t func, uint16_t addr, uint16_t nb, uint16_t expectedCRC, uint16_t actualCRC )
{



}

void busMonitorRawData( uint8_t * data, uint8_t dataLen, uint8_t addNewline )
{
   // qDebug()<<"busMonitorRawData:"<<endl;

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

      //  qDebug()<<dump<<endl;
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
   // qDebug()<<"id:"<<id<<" fun:"<<fun<<endl;

    if(id!=Config::localAddress||fun!=16){

        return -1;

    }

    int startAdd=data[2]<<8|data[3];
    int num=data[5];
   // qDebug()<<" startAdd:"<<startAdd<<" num:"<<num<<endl;


    int dataStart=7;

    int count=dataStart+2*num+1;

    int  equpmentId= data[dataStart]<<8|data[dataStart+1];

    dataStart+=2;
    int  labelIndex= data[dataStart]<<8|data[dataStart+1];

    dataStart+=2;
    int  labelStatus=data[dataStart]<<8|data[dataStart+1];


    globalMainWin->changeEquipmentStatusById(equpmentId,labelIndex,labelStatus);
    globalMainWin->updateLastWaitTime();

    return count;

}

}
