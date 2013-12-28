#ifndef SQLUTIL_H
#define SQLUTIL_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>

class Log
{
public:
    Log();

    QString logId;
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
    static QList<Log *> getAll();//get all date from sql
    static QList<Log *> getByKeyWord(QString );//get some date from sql
    static QList<Log *> getByPage(int , int );//get some date from sql

    static bool add(Log);//add date to sql
    static bool update(QString , QString);//update sql
    static bool delete_id(QString );//delete date from sql
    static bool deltetAll();//delete all


private:
    static QSqlDatabase dateBase;
    static bool initConnection();

signals:

public slots:
};

#endif // SQLUTIL_H
