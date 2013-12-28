#include "myserialport.h"
#include <QDebug>


/*******************************************************************************
 ******************************* PUBLIC ****************************************
 ******************************************************************************/
/******************************* Constructor **********************************/
MySerialPort::MySerialPort()
{
    initPrivateVariable();
}


MySerialPort::MySerialPort(const QString &name, const BaudRateType baudRate, const DataBitsType dataBits,
                           const ParityType parity, const StopBitsType stopBits, const FlowType flowControl,
                           ulong milliseconds)
{
    initPrivateVariable();
    setPortName(name);
    setBaudRate(baudRate);
    setDataBits(dataBits);
    setParity(parity);
    setStopBits(stopBits);
    setFlowControl(flowControl);
    setTimeout(milliseconds);
}


/******************************* Distructor ***********************************/
MySerialPort::~MySerialPort()
{


    if (sendThread)
    {
        delete sendThread;
        sendThread = NULL;
    }
    if (receiveThread)
    {
        delete receiveThread;
        receiveThread = NULL;
    }
    if (isOpen())
        port.close();
}


/*
  Private Functions
  */
void MySerialPort::initPrivateVariable()
{
    // Init private variable
    sendThread = NULL;
    receiveThread = NULL;
    sendingEnable = false;
    receivingEnable = false;
    closeCalled = false;
    saveStateSendingEnable = false;
    saveStateReceivingEnable = false;
    saveStateReceiveData = false;
}


/******************************* Methods **************************************/
// Open the SerialPort
bool MySerialPort::open()
{
    bool res = port.open(QIODevice::ReadWrite);


    // If the port is reopened after an earlier closure restores the previous state
    if (closeCalled)
    {
        if (saveStateSendingEnable)
            enableSending();
        if (saveStateReceivingEnable)
            enableReceiving();
        if (saveStateReceiveData)
            receiveData();
        closeCalled = false;
    }
    return res;
}


bool MySerialPort::open(const QString &name, const BaudRateType baudRate, const DataBitsType dataBits,
                        const ParityType parity, const StopBitsType stopBits, const FlowType flowControl,
                        ulong milliseconds)
{
    setPortName(name);
    setBaudRate(baudRate);
    setDataBits(dataBits);
    setParity(parity);
    setStopBits(stopBits);
    setFlowControl(flowControl);
    setTimeout(milliseconds);
    //return open();
    return port.open(QIODevice::ReadWrite);
}


// SerialPort is open?
bool MySerialPort::isOpen() const
{
    return port.isOpen();
}


// Close the SerialPort
void MySerialPort::close()
{
    closeCalled = true;
    // Save the state
    saveStateSendingEnable = isSendingEnable();
    saveStateReceivingEnable = isReceivingEnable();
    // Close the port
    disableReceiving();
    disableSending();
    port.close();
    // TODO: should I stop send and receive?
}


// Setter and getter for the basic property of the QextSerialPort
void MySerialPort::setPortName(const QString &name)
{
    port.setPortName(name);
}

QString MySerialPort::portName() const
{
    return port.portName();
}

void MySerialPort::setBaudRate(const BaudRateType baudRate)
{
    port.setBaudRate(baudRate);
}

BaudRateType MySerialPort::baudRate() const
{
    return port.baudRate();
}

void MySerialPort::setDataBits(const DataBitsType dataBits)
{
    port.setDataBits(dataBits);
}

DataBitsType MySerialPort::dataBits() const
{
    return port.dataBits();
}

void MySerialPort::setParity(const ParityType parity)
{
    port.setParity(parity);
}

ParityType MySerialPort::parity() const
{
    return port.parity();
}

void MySerialPort::setStopBits(StopBitsType stopBits)
{
    port.setStopBits(stopBits);
}

StopBitsType MySerialPort::stopBits() const
{
    return port.stopBits();
}

void MySerialPort::setFlowControl(const FlowType flowControl)
{
    port.setFlowControl(flowControl);
}

FlowType MySerialPort::flowControl() const
{
    return port.flowControl();
}

void MySerialPort::setTimeout(const ulong milliseconds)
{
    port.setTimeout(milliseconds);

}

/*
  Send
  */
// Enable the SerialPort to send data (init the thread)
void MySerialPort::enableSending()
{
    // If the Sending is not already active AND the sendThead is not initialized
    if (!sendingEnable && !sendThread)
    {
        sendThread = new SendThread(port);
        sendingEnable = true;
    }
}


// Disable the SerialPort to send data (terminate the thread)
void MySerialPort::disableSending()
{
    // If the Sending is already active AND there is a sendThread
    if (sendingEnable && sendThread)
    {
        delete sendThread;
        sendThread = NULL;
        sendingEnable = false;
    }
}


bool MySerialPort::isSendingEnable() const
{
    return sendingEnable;
}


// Stop the currently sending data operation (don't terminate the thread)
void MySerialPort::stopSending()
{
    // If the Sending is not alread active OR the sendThread is not initialized
    if (!sendingEnable || !sendThread)
        return;
    // If the SerialPort is currently sending data, stop
    if (sendThread->isRunning())
    {
        sendThread->stopSending();
        //wait(); ??????????
        sendThread->wait();
    }
}


// Enqueue data to the sendThread queue
// return 1     OK
// return 2     port closed
// return 3     sending operation disable
uchar MySerialPort::sendData(const QByteArray &data)
{
    // check the port if is open
    if (!isOpen())
        return 2;
    // check if sending operation is enable
    if (!sendingEnable || !sendThread)
        return 3;
    sendThread->addDataToSend(data);
    return 1;
}


/*
  Receive
  */
// Enable the SerialPort to receive data (init the thread)
void MySerialPort::enableReceiving()
{
    // If the Receiving is not already active AND the receiveThead is not initialized
    if (!receivingEnable && !receiveThread)
    {
        receiveThread = new ReceiveThread(port);
        connect(receiveThread, SIGNAL(dataReceived(const QByteArray &)),
                this, SIGNAL(dataReceived(const QByteArray &)));
        receivingEnable = true;
    }
}


// Disable the SerialPort to receive data (terminate the thread)
void MySerialPort::disableReceiving()
{
    // If the Receiving is already active AND there is a receiveThread
    if (receivingEnable && receiveThread)
    {
        delete receiveThread;
        receiveThread = NULL;
        receivingEnable = false;
    }
}


bool MySerialPort::isReceivingEnable() const
{
    return receivingEnable;
}


// Stop the currently receiving data operation (don't terminate the thread)
void MySerialPort::stopReceiving()
{
    // If the Receiving is not alread active OR the receiveThread is not initialized
    if (!receivingEnable || !receiveThread)
        return;
    // If the SerialPort is currently receiving data, stop
    if (receiveThread->isRunning())
    {
        saveStateReceiveData = false;
        receiveThread->stopReceiving();
        // wait();
        receiveThread->wait();
    }
}


// Start the receiving thread
// return 1     OK
// return 2     port closed
// return 3     receiving operation disable
uchar MySerialPort::receiveData()
{
    // check the port if is open
    if (!isOpen())
        return 2;
    // check if receiving operation is enable
    if (!receivingEnable && !receiveThread)
        return 3;
    // If the SerialPort receiving thread is not currently active, start it
    if (!receiveThread->isRunning())
    {
        saveStateReceiveData = true;
        receiveThread->start();
    }
    return 1;
}


/*******************************************************************************
 ******************************* SENDTHREAD ************************************
 ******************************************************************************/
/******************************* Constructor **********************************/
SendThread::SendThread(QextSerialPort &adrPort): port(adrPort)
{
    dataToSend.clear();
    stopped = false;
}


/******************************* Distructor ***********************************/
SendThread::~SendThread()
{
    if (isRunning())
    {
        stopSending();
        wait();
    }
}


/******************************* Methods **************************************/
// Add the data to the Send Queue
void SendThread::addDataToSend(const QByteArray &dataToAdd)
{
    QMutexLocker locker(&mutexSend);
    for (int i=0; i<dataToAdd.size(); i++)
        dataToSend.enqueue(QByteArray(1,dataToAdd.at(i)));
    if (!isRunning())
        start();
}


// Stop the sending operation
void SendThread::stopSending()
{
    stopped = true;
}


// Thread Send Loop
void SendThread::run()
{
    QByteArray byteArray;
    forever
    {
        mutexSend.lock();
        if (dataToSend.isEmpty() || stopped)
        {
            mutexSend.unlock();
            stopped = false;
            break;
        }
        byteArray = dataToSend.dequeue();
        mutexSend.unlock();
        port.write(byteArray, 1);
    }
}


/*******************************************************************************
 ******************************* RECEIVETHREAD *********************************
 ******************************************************************************/
/******************************* Constructor **********************************/
ReceiveThread::ReceiveThread(QextSerialPort &adrPort) : port(adrPort)
{
    stopped = false;
}


/******************************* Distructor ***********************************/
ReceiveThread::~ReceiveThread()
{
    if (isRunning())
    {
        stopReceiving();
        wait();
    }
}


/******************************* Methods **************************************/
// Stop the sending operation
void ReceiveThread::stopReceiving()
{
    stopped = true;
}


// Thread Receive Loop
void ReceiveThread::run()
{
    int numBytes = 0;
    QByteArray data;
    forever
    {
        if (stopped)
        {
            stopped = false;
            break;
        }
        numBytes = port.bytesAvailable();
        if (numBytes>0)
        {
            mutexReceive.lock();
            data = port.read(numBytes);
            mutexReceive.unlock();
            emit dataReceived(data);
        }
    }
}
