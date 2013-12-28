#include "sqlutil.h"
#include "config.h"


QSqlDatabase SQLUtil::dateBase;

Log::Log(){


}

SQLUtil::SQLUtil(QObject *parent) :
    QObject(parent)
{

}

bool SQLUtil::initConnection(){

    /*
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
    */
}

bool SQLUtil::open(){

    dateBase = QSqlDatabase::addDatabase("QSQLITE");//添加驱动

    dateBase.setDatabaseName("FGcheck.db");

    if(!dateBase.open()){

        qDebug()<<"open false1"<<endl;//需要修改
        return false;

    }
    else{

        if(!dateBase.contains("FGCheck")){

            QSqlQuery sql_add(dateBase);

            sql_add.exec("create table FGCheck(logId varchar primary key, logDetail varchar , logCreateTime varchar , logSolveTime varchar )");

        }

        return true;
    }

}

bool SQLUtil::close(){

    if(dateBase.isOpen()){
        dateBase.close();
    }

    return !dateBase.isOpen();

}


bool SQLUtil::deltetAll(){

    if(!open()){

        return false;
    }
    else{

        QSqlQuery sql_exec(dateBase);

        sql_exec.exec("delete from FGcheck");

        if(!sql_exec.exec()){

            qDebug()<<"deleteAll fail1";
        }else{

            qDebug()<<"deleteAll success";
        }

    }


    close();
    return true;
}

bool SQLUtil::add(Log log){

    if(!open()){

        return false;

    }else{

        QSqlQuery sql_add(dateBase);

        sql_add.exec("insert into FGCheck values(? , ? , ? , ?)");

        sql_add.bindValue(0 , log.logId );

        sql_add.bindValue(1 , log.logDetial);

        sql_add.bindValue(2 , log.logCreateTime);

        sql_add.bindValue(3 , log.logSolveTime);
    }

    close();
    return true;

}
bool SQLUtil::delete_id(QString logId){

    if(!open()){

        return false;

    }else{

        QSqlQuery sql_del(dateBase);

        sql_del.exec("delete from FGCheck where logId = ?");

        sql_del.bindValue(0 , logId);

        if(!sql_del.exec()){

            qDebug()<<"deleteid fail1";
        }
        else{

            qDebug()<<"deleteid success";

        }

    }
    close();
    return true;
}


bool SQLUtil::update(QString logId , QString logEndTime){

    if(!open()){

        return false;

    }else{

        QSqlQuery sql_del(dateBase);

        sql_del.exec("update FGCheck set logSolveTime = ?  where logId = ?");

        sql_del.bindValue(0 , logEndTime);

        sql_del.bindValue(1 , logId);

        if(!sql_del.exec()){

            qDebug()<<"deleteid fail1";
        }
        else{

            qDebug()<<"deleteid success";

        }

    }
    close();
    return true;
}
QList<Log *> SQLUtil::getAll(){

    QList<Log *> list;

    if(open()){

        QSqlQuery sql_Find(dateBase);

        sql_Find.exec("select * from FGCheck");

        if(sql_Find.exec()){

            while(sql_Find.next()){

                Log*l = new Log();

                l->logId = sql_Find.value(0).toString();

                l->logId = sql_Find.value(1).toString();

                l->logId = sql_Find.value(2).toString();

                l->logSolveTime = sql_Find.value(3).toString();

                list.append(l);
            }
        }


        close();


    }
    return list;
}

QList<Log *> SQLUtil::getByKeyWord(QString keyWord){

    QList<Log *> list;

    if(open()){

        QSqlQuery sql_Find(dateBase);

        sql_Find.exec("select * from FGCheck where ? = logId)");

        sql_Find.bindValue(0 , keyWord);

        sql_Find.exec("select * from FGCheck where ? = logDetail )");

        sql_Find.bindValue(0 , keyWord);

        sql_Find.exec("select * from FGCheck where ? =logCreateTime )");

        sql_Find.bindValue(0 , keyWord);

        sql_Find.exec("select * from FGCheck where ? =logSolveTime)");

        sql_Find.bindValue(0 , keyWord);

        if(sql_Find.exec()){

            while(sql_Find.next()){

                Log*l = new Log();

                l->logId = sql_Find.value(0).toString();

                l->logId = sql_Find.value(1).toString();

                l->logId = sql_Find.value(2).toString();

                l->logSolveTime = sql_Find.value(3).toString();

                list.append(l);
            }
        }
        close();

    }
    return list;
}

QList<Log*> SQLUtil::getByPage(int PageStart, int PageEnd){

    QList<Log *> list;

    if(open()){



        QSqlQuery sql_get(dateBase);

        sql_get.exec("select * from FGCheck where logId >= ?*10 and logId < ?*10");

        sql_get.bindValue(0 , PageStart);
        sql_get.bindValue(1 , PageEnd);

        while(sql_get.next()){

            Log*l = new Log();

            l->logId = sql_get.value(0).toString();

            l->logId = sql_get.value(1).toString();

            l->logId = sql_get.value(2).toString();

            l->logSolveTime = sql_get.value(3).toString();

            list.append(l);
        }

        close();
    }

    return list;
}

