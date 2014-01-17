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
#include "qexcel.h"
#include <QTextCodec>
#include <QDateTime>


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

    static bool open();
    static bool close();

    static bool add(Log);//add date to sql
    static bool deltetAll();//delete all
    static bool delete_id(int );//delete date from sql
    static void getAll(QList<Log> *list);//get all date from sql
    static bool update(int , QString);//update sql
    static void getByKeyWord(QString , QList<Log> *list);//get some date from sql
    static void getByPage(int , int , QList<Log> *list);//get some date from sql
    static bool save_txt(QList<Log> *list ,QString fileName);//save date to word
    static bool save_excel(QList<Log> *list, QString fileName);//save date to excel

private:
    static QSqlDatabase dateBase;

signals:

public slots:

};
#endif // SQLUTIL_H
