#ifndef MYSERIALPORT_H
#define MYSERIALPORT_H
#include <QObject>
#include <QQueue>
#include <QMetaType>
#include <QThread>
#include <QMutex>
#include "qextserialport.h"

Q_DECLARE_METATYPE(BaudRateType);
Q_DECLARE_METATYPE(DataBitsType);
Q_DECLARE_METATYPE(ParityType);
Q_DECLARE_METATYPE(StopBitsType);
Q_DECLARE_METATYPE(FlowType);

class SendThread;
class ReceiveThread;

class MySerialPort : public QObject
{
    Q_OBJECT
public:
    MySerialPort();
    MySerialPort(const QString &name, const BaudRateType baudRate, const DataBitsType dataBits,
                 const ParityType parity, const StopBitsType stopBits, const FlowType flowControl, ulong milliseconds = 10);
    ~MySerialPort();
    bool open();
    bool open(const QString &name, const BaudRateType baudRate, const DataBitsType dataBits,
              const ParityType parity, const StopBitsType stopBits, const FlowType flowControl,
               ulong milliseconds = 10);
    bool isOpen() const;
    void close();

    // Setter and getter for the basic property of the QextSerialPort
    void setPortName(const QString &name);
    QString portName() const;
    void setBaudRate(const BaudRateType baudRate);
    BaudRateType baudRate() const;
    void setDataBits(const DataBitsType dataBits);
    DataBitsType dataBits() const;
    void setParity(const ParityType parity);
    ParityType parity() const;
    void setStopBits(StopBitsType stopBits);
    StopBitsType stopBits() const;
    void setFlowControl(const FlowType flowControl);
    FlowType flowControl() const;
    void setTimeout(const ulong milliseconds);
    /*
      Send
      */
    void enableSending();           // enable the SerialPort to send data (init the thread)
    void disableSending();          // disable the SerialPort to send data (terminate the thread)
    bool isSendingEnable() const;
    void stopSending();             // stop the currently sending data operation (don't terminate the thread)
    uchar sendData(const QByteArray &data); // send data to the SerialPort (enqueue data to the sendThread queue)
    // return 1     OK
    // return 2     port not open
    // return 3     sending operation disable
    /*
      Receive
      */
    void enableReceiving();         // enable the SerialPort to receive data (init the thread)
    void disableReceiving();        // disable the SerialPort to receive data (terminate the thread)
    bool isReceivingEnable() const;
    void stopReceiving();           // stop the currently receiving data operation (don't terminate the thread)
    uchar receiveData();                    // Start the receiving thread
    // return 1     OK
    // return 2     port closed
    // return 3     receiving operation disable
signals:
    void dataReceived(const QByteArray &dataReceived);
private:
    void initPrivateVariable();
private:
    QextSerialPort port;
    SendThread *sendThread;
    ReceiveThread *receiveThread;
    bool sendingEnable;
    bool receivingEnable;
    // Variables to restore the previous state to a reopening of the SerialPort
    bool closeCalled;
    bool saveStateSendingEnable;
    bool saveStateReceivingEnable;
    bool saveStateReceiveData;
};
class SendThread : public QThread
{
    Q_OBJECT
public:
    SendThread(QextSerialPort &adrPort);
    ~SendThread();
    void addDataToSend(const QByteArray &dataToAdd);
    void stopSending();
protected:
    void run();
private:
    QextSerialPort &port;
    QQueue<QByteArray> dataToSend;
    QMutex mutexSend;
    bool stopped;
};
class ReceiveThread : public QThread
{
    Q_OBJECT
public:
    ReceiveThread(QextSerialPort &adrPort);
    ~ReceiveThread();
    void stopReceiving();
protected:
    void run();
signals:
    void dataReceived(const QByteArray &dataReceived);
private :
    QextSerialPort &port;
    QMutex mutexReceive;
    bool stopped;
};
#endif // MYSERIALPORT_H
