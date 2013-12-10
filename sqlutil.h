#ifndef SQLUTIL_H
#define SQLUTIL_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QString>

class SQLUtil : public QObject
{
    Q_OBJECT
public:
    explicit SQLUtil(QObject *parent = 0);

    static bool open();
    static bool close();
    static void test();

private:
    static QSqlDatabase dateBase;
    static bool initConnection();

signals:
    
public slots:
    
};

#endif // SQLUTIL_H
