#ifndef MODBUSREQUESTTHREAD_H
#define MODBUSREQUESTTHREAD_H

#include "modbus.h"
#include <QThread>


class Transcation{



};

class ModbusRequestThread : public QThread
{
    Q_OBJECT
public:
    ModbusRequestThread();
    ~ModbusRequestThread();
    void stop();
    static modbus_t * m_modbus;
signals:
    
public slots:

private:
    void sendModbusRequest();
    bool flag;
    long sleepTime;
protected:
    void run();

    
};

#endif // MODBUSREQUESTTHREAD_H
