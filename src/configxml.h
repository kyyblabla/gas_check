#ifndef CONFIGXML_H
#define CONFIGXML_H

#include <QObject>
#include <QList>

class Addr{

public:
    int id;
    int slaveId;
    int startAddr;
    int coilNum;
    int location;
    int index;
    QString num;
};


class ConfigXml : public QObject
{
    Q_OBJECT
public:
    explicit ConfigXml(QObject *parent = 0);
    static void init();
    static  QList<Addr*> addrs;
    static void update();

signals:
    
public slots:



    
};

#endif // CONFIGXML_H
