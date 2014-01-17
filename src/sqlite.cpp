#include "SQLUtil.h"
#include "QTextCodec"

QSqlDatabase SQLUtil::dateBase;

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

        sql_add.exec("create table FGCheck(logId INTEGER primary key, logDetail TEXT , logCreateTime DateTime , logSolveTime DateTime)");

        if(sql_add.exec()){

            qDebug()<<"table create successfully";
        }
        else{

            qDebug()<<"table had been created";
        }

        QString str_insert = "insert into FGCheck(logDetail ,logCreateTime , logSolveTime) values(:detail, :create , :end)";

        sql_add.prepare(str_insert);
        sql_add.bindValue(":detail", log.logDetial);
        sql_add.bindValue(":create" , log.logCreateTime);
        sql_add.bindValue(":end" , log.logSolveTime);

        if(!sql_add.exec()){

            QString name ;
            {
                name = QSqlDatabase::database().connectionName();
            }
            QSqlDatabase::removeDatabase(name);
            close();

            return false;

        }else{

            QString name ;
            {
                name = QSqlDatabase::database().connectionName();
            }
            QSqlDatabase::removeDatabase(name);
            close();
            return true ;
        }
    }
    return false;
}

void SQLUtil::getAll(QList<Log> *list){

    if(!open()){

        qDebug()<<"sqlite open fail"<<endl;

    }else{

        QSqlQuery sql_Find(dateBase);

        if(sql_Find.exec("select * from FGCheck order by logCreateTime desc")){

            Log log;

            while(sql_Find.next()){

                log.logId = sql_Find.value(0).toInt();
                log.logDetial = sql_Find.value(1).toString();
                log.logCreateTime = sql_Find.value(2).toString();
                log.logSolveTime = sql_Find.value(3).toString();
                list->append(log);
            }
        }
    }

    QString name ;
    {
        name = QSqlDatabase::database().connectionName();
    }
    QSqlDatabase::removeDatabase(name);
    close();
}

bool SQLUtil::deltetAll(){

    if(!open()){

        qDebug()<<"sql open fail";
        return false;
    }
    else{

        QSqlQuery sql_delAll(dateBase);

        if(!sql_delAll.exec("delete from FGcheck")){

            QString name ;
            {
                name = QSqlDatabase::database().connectionName();
            }
            QSqlDatabase::removeDatabase(name);

            close();

            return false;

        }else{

            QString name ;
            {
                name = QSqlDatabase::database().connectionName();
            }
            QSqlDatabase::removeDatabase(name);

            close();
            return true;
        }
    }
    return false;
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
            qDebug()<<"the id is not existing";
            return false;
        }
        else{

            QString name ;
            {
                name = QSqlDatabase::database().connectionName();
            }
            QSqlDatabase::removeDatabase(name);
            close();
            qDebug()<<"the id is existing ,but had been deleted";
            return true;

        }
    }
    return false;
}

bool SQLUtil::update(int logId , QString logEndTime){

    if(!open()){

        qDebug()<<"sql open fail";
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
    return  false;
}

void SQLUtil::getByKeyWord(QString keyWord, QList<Log> *list){

    if(!open()){

        qDebug()<<"sql open fail"<<endl;

    }else{

        QSqlQuery sql_FindKey(dateBase);

        sql_FindKey.prepare("select * from FGCheck where logDetail like ?");

        sql_FindKey.bindValue(0 , "%"+keyWord+"%");

        if(sql_FindKey.exec()){

            Log log;

            while(sql_FindKey.next()){

                log.logId = sql_FindKey.value(0).toInt();

                log.logDetial = sql_FindKey.value(1).toString();

                log.logCreateTime = sql_FindKey.value(2).toString();

                log.logSolveTime = sql_FindKey.value(3).toString();

                list->append(log);

            }
        }
    }
    QString name ;
    {
        name = QSqlDatabase::database().connectionName();
    }
    QSqlDatabase::removeDatabase(name);
    close();
}

void SQLUtil::getByPage(int PageNum, int PageCount, QList<Log> *list){

    if(!open()){

        qDebug()<<"sql open fail"<<endl;

    }else{
        QSqlQuery sql_get(dateBase);

        int x = (PageNum-1) * PageCount ;

        sql_get.prepare("select * from FGCheck limit ? offset ?");

        sql_get.bindValue(0 , PageCount);
        sql_get.bindValue(1 , x);

        if(sql_get.exec()){

            Log l;

            while(sql_get.next()){

                l.logId = sql_get.value(0).toInt();

                l.logDetial = sql_get.value(1).toString();

                l.logCreateTime = sql_get.value(2).toString();

                l.logSolveTime = sql_get.value(3).toString();

                list->append(l);
            }
        }
    }

    QString name ;
    {
        name = QSqlDatabase::database().connectionName();
    }
    QSqlDatabase::removeDatabase(name);
    close();
}
bool SQLUtil::save_txt(QList<Log> *list , QString fileName){

    QFile file(fileName);
    file.open(QIODevice::WriteOnly);

    QTextStream save(&file);

    save.setCodec("UTF-8");
    for(int i = -1 ; i < list->length(); i++){

        if(i == -1){

            save.setFieldAlignment(QTextStream::AlignLeft);
            save<<qSetFieldWidth(8)<<QObject::tr("Id");

            save.setFieldAlignment(QTextStream::AlignLeft);
            save<<qSetFieldWidth(22)<<QObject::tr("CreateTime");

            save.setFieldAlignment(QTextStream::AlignLeft);
            save<<qSetFieldWidth(22)<<QObject::tr("SolveTime");

            save.setFieldAlignment(QTextStream::AlignLeft);
            save<<QObject::tr("Detail");
            save<<qSetFieldWidth(1)<<"\r\n";
            continue;
        }

        save.setFieldAlignment(QTextStream::AlignLeft);
        save<<qSetFieldWidth(8)<<list->at(i).logId;

        save.setFieldAlignment(QTextStream::AlignLeft);
        save<<qSetFieldWidth(22)<<list->at(i).logCreateTime;

        save.setFieldAlignment(QTextStream::AlignLeft);
        save<<qSetFieldWidth(22)<<list->at(i).logSolveTime;

        save.setFieldAlignment(QTextStream::AlignLeft);
        save<<list->at(i).logDetial;
        save<<qSetFieldWidth(1)<<"\r\n";
    }
    save.flush();
    file.close();
    return true;
}
bool SQLUtil::save_excel(QList<Log> *list, QString fileName){

    QExcel excel(fileName);

    excel.selectSheet(1);

    int row_count = excel.getUsedRowsCount();

    qDebug()<<"row"<<row_count;

    row_count = 1;
    if(row_count == 1){

        excel.setCellTextCenter(row_count, 1);
        excel.setCellTextCenter(row_count, 2);
        excel.setCellTextCenter(row_count, 3);
        excel.setCellTextCenter(row_count, 4);
        excel.setCellString(row_count , 1 ,QObject::tr("Id"));
        excel.setCellString(row_count , 2 ,QObject::tr("Detail"));
        excel.setCellString(row_count , 3 ,QObject::tr("CreateTime"));
        excel.setCellString(row_count , 4 ,QObject::tr("SolveTime"));
    }

    for(int i = 0 ; i < list->length() ; i++){

        excel.setCellTextCenter(row_count+i+1, 1);
        excel.setCellTextCenter(row_count+i+1, 2);
        excel.setCellTextCenter(row_count+i+1, 3);
        excel.setCellTextCenter(row_count+i+1, 4);
        excel.setCellString(row_count+i+1 , 1 ,QString::number(list->at(i).logId));
        excel.setCellString(row_count+i+1 , 2 ,list->at(i).logDetial);
        excel.setCellString(row_count+i+1 , 3 ,"'"+list->at(i).logCreateTime);
        excel.setCellString(row_count+i+1 , 4 ,"'"+list->at(i).logSolveTime);
    }
    excel.save();
    excel.close();
    return true;
}
