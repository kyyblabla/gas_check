#include "config.h"
#include  <QString>
#include <QSettings>
#include <QDebug>
#include <QTextCodec>

QString Config::SQL_CONNECTION_NAME;
QString Config::SQL_HOST_NAME;
int Config::SQL_HOST_PORT;
QString Config::SQL_PASSWORD;
QString Config::SQL_USERNAME;
QString Config::SQL_DATEBASE_NAME;
QString Config::LINKSTATUS_LABEL;
QString Config::EQUIPMENT_LABEL;
QString Config::AREA_LABEL;
QString Config::MAIN_TITLE;

int Config::serialinterfaceActive;
QString Config::serialinterface;
int Config::serialBaudRate;
int Config::serialDatabits;
int Config::serialStopbits;
QString Config::serialParity;

Config::Config(QObject *parent) :
    QObject(parent)
{

}

Config::~Config(){

}

bool Config::initConfig(){

    QSettings settings("config.ini", QSettings::IniFormat);
    settings.setIniCodec(QTextCodec::codecForName("UTF-8"));


    Config::MAIN_TITLE=settings.value("SystemLabel/title").toString();
    Config::LINKSTATUS_LABEL=settings.value("SystemLabel/linkStatusLabel").toString();
    Config::EQUIPMENT_LABEL=settings.value("SystemLabel/equipmentsLabel").toString();
    Config::AREA_LABEL=settings.value("SystemLabel/areaLabel").toString();



    Config::serialinterfaceActive= settings.value("serialSetting/serialinterfaceActive").toInt();
    Config::serialinterface= settings.value("serialSetting/serialinterface").toString();
    Config::serialBaudRate = settings.value("serialSetting/serialBaudRate").toInt();
    Config::serialDatabits = settings.value("serialSetting/serialDatabits").toInt();
    Config::serialStopbits = settings.value("serialSetting/serialStopbits").toInt();
    Config::serialParity = settings.value("serialSetting/serialParity").toString();



    Config::SQL_CONNECTION_NAME="QMYSQL";
    Config::SQL_HOST_NAME="localhost";
    Config::SQL_DATEBASE_NAME="test";
    Config::SQL_HOST_PORT=3306;
    Config::SQL_PASSWORD="root";
    Config::SQL_USERNAME="qaz";

    return true;

}

bool Config::updateConfig(QString name, QString value){

    QSettings settings("config.ini", QSettings::IniFormat);
    settings.setIniCodec(QTextCodec::codecForName("UTF-8")); //在此添加设置，即可读写ini文件中的中文

    settings.setValue(name,value);

    return initConfig();
}



