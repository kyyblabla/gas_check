#include "sqlite.h"
#include "QTextCodec"

QSqlDatabase SQLUtil::dateBase;

SQLUtil::SQLUtil(QObject *parent) :
    QObject(parent)
{

}

bool SQLUtil::open(){

    if(QSqlDatabase::contains("Date_sql")){

        dateBase = QSqlDatabase::database("Date_sql");
    }else{

        dateBase = QSqlDatabase::addDatabase("QSQLITE" , "Date_sql");
    }

    dateBase.setDatabaseName("FGcheck.db");
    if(!dateBase.open()){

        return false;

    }
    else{

        return true;
    }

}

bool SQLUtil::close(){

    if(dateBase.isOpen()){

        dateBase.close();
    }
    return !dateBase.isOpen();
}

bool SQLUtil::add(Log log){

    if(!open()){

        return false;

    }else{

        QSqlQuery sql_add(dateBase);

        sql_add.exec("create table if not exists FGCheck(logId int primary key, logDetail varchar(12) , logCreateTime varchar(12) , logSolveTime varchar(12) )");

        sql_add.clear();

        QString str_insert = "insert into FGCheck values(? ,? , ? , ?)";

        sql_add.prepare(str_insert);

        sql_add.addBindValue(log.logId);
        sql_add.addBindValue(log.logDetial);
        sql_add.addBindValue(log.logCreateTime);
        sql_add.addBindValue(log.logSolveTime);

        if(!sql_add.exec()){

            QString name ;
            {
                name = QSqlDatabase::database().connectionName();
            }
            QSqlDatabase::removeDatabase(name);
            close();

            return false;

        }
    }

    QString name ;
    {
        name = QSqlDatabase::database().connectionName();
    }
    QSqlDatabase::removeDatabase(name);
    return close();
}

QList<Log > SQLUtil::getAll(){

    QList<Log > list;

    if(!open()){

        cout<<"null"<<endl;

    }else{

        QSqlQuery sql_Find(dateBase);

        if(sql_Find.exec("select * from FGCheck")){

            Log log;
            while(sql_Find.next()){

                log.logId = sql_Find.value(0).toInt();
                log.logDetial = sql_Find.value(1).toString();
                log.logCreateTime = sql_Find.value(2).toString();
                log.logSolveTime = sql_Find.value(3).toString();

                list.append(log);

            }

        }

    }
    QString name ;
    {
        name = QSqlDatabase::database().connectionName();
    }
    QSqlDatabase::removeDatabase(name);
    close();
    return list;
}


int SQLUtil::count(){

    if(!open()){

        return false;
    }
    else{

        QSqlQuery sql_count(dateBase);

        sql_count.exec("select count(*) from FGCheck");

        if(sql_count.exec()){

            sql_count.next();

            int cc = sql_count.value(0).toInt();

            return cc;
        }

    }
    QString name ;
    {
        name = QSqlDatabase::database().connectionName();
    }
    QSqlDatabase::removeDatabase(name);
    close();
    return 0;

}

bool SQLUtil::deltetAll(){

    if(!open()){

        return false;
    }
    else{

        QSqlQuery sql_delAll(dateBase);

        if(!sql_delAll.exec("delete from FGcheck")){

            return false;

        }else{

            return true;
        }

    }
    QString name ;
    {
        name = QSqlDatabase::database().connectionName();
    }
    QSqlDatabase::removeDatabase(name);

    return close();
}

bool SQLUtil::delete_id(int Id){

    if(!open()){

        return false;

    }else{

        QSqlQuery sql_del(dateBase);

        QString str_del = "delete from FGCheck where logId = ?";

        sql_del.prepare(str_del);

        sql_del.addBindValue(Id);

        if(!sql_del.exec()){

            QString name ;
            {
                name = QSqlDatabase::database().connectionName();
            }
            QSqlDatabase::removeDatabase(name);
            close();

            return false;
        }
        else{

            QString name ;
            {
                name = QSqlDatabase::database().connectionName();
            }
            QSqlDatabase::removeDatabase(name);
            close();

            return true;

        }
    }

    QString name ;
    {
        name = QSqlDatabase::database().connectionName();
    }
    QSqlDatabase::removeDatabase(name);

    return close();
}
bool SQLUtil::update(int logId , QString logEndTime){

    if(!open()){

        return false;

    }else{

        QSqlQuery sql_del(dateBase);

        sql_del.exec("update FGCheck set logSolveTime = ?  where logId = ?");

        sql_del.bindValue(0 , logEndTime);

        sql_del.bindValue(1 , logId);

        if(!sql_del.exec()){

            QString name ;
            {
                name = QSqlDatabase::database().connectionName();
            }
            QSqlDatabase::removeDatabase(name);
            close();

            return false;
        }
        else{

            QString name ;
            {
                name = QSqlDatabase::database().connectionName();
            }
            QSqlDatabase::removeDatabase(name);
            close();

            return true;

        }

    }

    QString name ;
    {
        name = QSqlDatabase::database().connectionName();
    }
    QSqlDatabase::removeDatabase(name);

    return  close();

}


QList<Log> SQLUtil::getByKeyWord(QString keyWord){

    QList<Log> list;

    if(!open()){

        cout<<"fail"<<endl;

    }else{

        QSqlQuery sql_FindKey(dateBase);

        sql_FindKey.prepare("select * from FGCheck where logDetail = :name ");

        sql_FindKey.bindValue(":name ", keyWord);

        if(sql_FindKey.exec()){

            Log log ;
            while(sql_FindKey.next()){

                log.logId = sql_FindKey.value(0).toInt();

                log.logDetial = sql_FindKey.value(1).toString();

                log.logCreateTime = sql_FindKey.value(2).toString();

                log.logSolveTime = sql_FindKey.value(3).toString();

                list.append(log);

            }
        }

    }
    QString name ;
    {
        name = QSqlDatabase::database().connectionName();
    }
    QSqlDatabase::removeDatabase(name);
    close();

    return list;
}

QList<Log > SQLUtil::getByPage(int PageStart, int PageCount){

    QList<Log> list;

    if(!open()){

        cout<<"NULL"<<endl;

    }else{

        QSqlQuery sql_get(dateBase);

        int x = PageStart - 2 ;

        sql_get.prepare("select * from FGCheck limit :num , :count");

        sql_get.bindValue(":num ", x);
        sql_get.bindValue(":count" , PageCount);

        if(sql_get.exec()){
            Log l;
            while(sql_get.next()){

                l.logId = sql_get.value(0).toInt();

                l.logDetial = sql_get.value(1).toString();

                l.logCreateTime = sql_get.value(2).toString();

                l.logSolveTime = sql_get.value(3).toString();

                list.append(l);
            }
        }
    }

    QString name ;
    {
        name = QSqlDatabase::database().connectionName();
    }
    QSqlDatabase::removeDatabase(name);
    close();
    return list;

}
bool SQLUtil::save(){

    if(!open()){

        return false;
    }else{

        QFile file("save.txt");
        file.open(QIODevice::WriteOnly|QIODevice::Append);

        QTextStream save(&file);
        QSqlQuery sql_save(dateBase);

        if(sql_save.exec("select * from FGCheck")){

            Log log;
            while(sql_save.next()){

                log.logId = sql_save.value(0).toInt();
                log.logDetial = sql_save.value(1).toString();
                log.logCreateTime = sql_save.value(2).toString();
                log.logSolveTime = sql_save.value(3).toString();

                save<<log.logId<<"     "<<log.logDetial<<"     "<<log.logCreateTime<<"     "<<log.logSolveTime<<"\r\n";

            }

        }

        QString name ;
        {
            name = QSqlDatabase::database().connectionName();
        }
        QSqlDatabase::removeDatabase(name);
        close();

        file.close();
    }

    return true;
}

/**/
