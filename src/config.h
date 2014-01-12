#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>

class QString;

class Config : public QObject
{
    Q_OBJECT
public:
    explicit Config(QObject *parent = 0);
    ~Config();
    static bool initConfig();
    static bool updateConfig(QString name,QString value);

    static QString SQL_CONNECTION_NAME;
    static QString SQL_HOST_NAME;
    static int SQL_HOST_PORT;
    static QString SQL_DATEBASE_NAME;
    static QString SQL_USERNAME;
    static QString SQL_PASSWORD;
    static QString LINKSTATUS_LABEL;
    static QString EQUIPMENT_LABEL;
    static QString  AREA_LABEL;
    static QString  MAIN_TITLE;

    static int serialinterfaceActive;
    static QString serialinterface;
    static int serialBaudRate;
    static int serialDatabits;
    static int serialStopbits;
    static QString serialParity;

    static QString colorLevel;
    static int sleepTime;
    static bool isSlave;

    static int ndLableMin;
    static int ndLableMax;
    static double ndLableStep;
    static QString ndLableName;

    static int localAddress;
    static int remoteAddress;


signals:

public slots:

};

#endif // CONFIG_H
