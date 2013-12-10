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
    static QString SQL_CONNECTION_NAME;
    static QString SQL_HOST_NAME;
    static int SQL_HOST_PORT;
    static QString SQL_DATEBASE_NAME;
    static QString SQL_USERNAME;
    static QString SQL_PASSWORD;
    static QString LINKSTATUS_LABEL;
    static QString EQUIPMENT_LABEL;
    static QString  AREA_LABEL;

signals:

public slots:

};

#endif // CONFIG_H
