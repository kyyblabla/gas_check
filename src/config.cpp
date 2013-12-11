#include "config.h"
#include "QString"
#include "QSettings"
#include "QDebug"
#include "QTextCodec"

QString Config::SQL_CONNECTION_NAME;
QString Config::SQL_HOST_NAME;
int Config::SQL_HOST_PORT=3306;
QString Config::SQL_PASSWORD;
QString Config::SQL_USERNAME;
QString Config::SQL_DATEBASE_NAME;
QString Config::LINKSTATUS_LABEL;
QString Config::EQUIPMENT_LABEL;
QString Config::AREA_LABEL;
QString Config::MAIN_TITLE;
Config::Config(QObject *parent) :
    QObject(parent)
{

}

Config::~Config(){

}

bool Config::initConfig(){

    QSettings settings("config.ini", QSettings::IniFormat);
    settings.setIniCodec(QTextCodec::codecForName("UTF-8")); //在此添加设置，即可读写ini文件中的中文

    //int speed = settings.value("DevOption/speed").toInt();
    // int CarNum = settings.value("DevOption/CarNum").toInt();
    // QString geometry = settings.value("DevOption/geometry").toString();
    Config::MAIN_TITLE=settings.value("SystemLabel/title").toString();
    Config::LINKSTATUS_LABEL=settings.value("SystemLabel/linkStatusLabel").toString();
    Config::EQUIPMENT_LABEL=settings.value("SystemLabel/equipmentsLabel").toString();
    Config::AREA_LABEL=settings.value("SystemLabel/areaLabel").toString();

    // qDebug()<<"Config::LINKSTATUS_LABEL"<<Config::LINKSTATUS_LABEL<<endl;
    // qDebug()<<"Config::EQUIPMENT_LABEL"<<Config::EQUIPMENT_LABEL<<endl;


    Config::SQL_CONNECTION_NAME="QMYSQL";
    Config::SQL_HOST_NAME="localhost";
    Config::SQL_DATEBASE_NAME="test";
    Config::SQL_HOST_PORT=3306;
    Config::SQL_PASSWORD="root";
    Config::SQL_USERNAME="qaz";

    return true;

}


