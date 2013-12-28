﻿#ifndef MODBUSREQUESTTHREAD_H
#define MODBUSREQUESTTHREAD_H

#include "configxml.h"
#include "modbus.h"
#include <QThread>
#include <QMutex>
#include <QQueue>
#include <QWaitCondition>


class Transcation{

public:
    int funCode;
    Addr*addr;
    QString returnData;
    int returnCode;

};

class ModbusRequestThread : public QThread
{
    Q_OBJECT
public:
    ModbusRequestThread();
    ~ModbusRequestThread();
    void addTranscation(Transcation*transcation);
    static modbus_t * m_modbus;
    void createModbus();
signals:

    void transcationDone(Transcation*transcation);

public slots:

private:
    void sendModbusRequest(Transcation *transcation);
    bool stopFlag;
    long sleepTime;
    QMutex mutex;
    QQueue<Transcation*> transcations;
    QWaitCondition transcationAdded;

protected:
    void run();

    
};

#endif // MODBUSREQUESTTHREAD_H