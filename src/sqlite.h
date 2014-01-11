#ifndef SQLUTIL_H
#define SQLUTIL_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QString>
#include <QList>
#include <iostream>
#include <QFile>
#include <QTextStream>

using namespace std;


class Log
{
public:
    int logId;
    QString logDetial;
    QString logCreateTime;
    QString logSolveTime;

};

class SQLUtil : public QObject
{
    Q_OBJECT
public:
    explicit SQLUtil(QObject *parent = 0);

    static bool open();
    static bool close();

    static int count();//select count from sql
    static bool add(Log);//add date to sql
    static bool deltetAll();//delete all
    static bool delete_id(int );//delete date from sql
    static QList<Log > getAll();//get all date from sql
    static bool update(int , QString);//update sql
    static QList<Log > getByKeyWord(QString );//get some date from sql
    static QList<Log > getByPage(int , int );//get some date from sql
    static bool save();//save date to word


    /*
    */


private:
    static QSqlDatabase dateBase;

signals:

public slots:

};

#endif // SQLUTIL_H
