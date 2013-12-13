#include "sqlutil.h"
#include "config.h"

QSqlDatabase SQLUtil::dateBase;

SQLUtil::SQLUtil(QObject *parent) :
    QObject(parent)
{

}

bool SQLUtil::initConnection(){


    bool re=Config::initConfig();

    if(re){

        dateBase = QSqlDatabase::addDatabase("QMYSQL");
        dateBase.setHostName("localhost");
        dateBase.setDatabaseName("test");
        dateBase.setPort(3306);
        dateBase.setUserName("root");
        dateBase.setPassword("qaz");

    }


    return re;
}

bool SQLUtil::open(){

    if(!dateBase.isValid()){

        if(!initConnection()){
            qDebug()<<"false"<<endl;
            return false;
        }

    }else{

        if(dateBase.isOpen()){
            return true;
        }
    }


    bool re=dateBase.open();

    if(re){
        qDebug()<<"success !"<<endl;
    }

    return dateBase.isOpen();

}

bool SQLUtil::close(){

    if(dateBase.isOpen()){
        dateBase.close();
    }

    return !dateBase.isOpen();

}

void SQLUtil::test(){

     bool isOpen=open();

     qDebug()<<"isOpen:"<<isOpen<<endl;

    QSqlQuery qsql(dateBase);

    bool ret = qsql.exec("SELECT * FROM test");

    if(ret){

        while(qsql.next()){

            QString a=qsql.value(1).toString();
            qDebug()<<a<<endl;

        }

    }


}



