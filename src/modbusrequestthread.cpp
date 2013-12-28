#include "modbusrequestthread.h"
#include "modbus-private.h"
#include "configxml.h"
#include "config.h"
#include "myserialport.h"

#include <QMessageBox>
#include <QDebug>
#include <QMutexLocker>

modbus_t* ModbusRequestThread::m_modbus;

ModbusRequestThread::ModbusRequestThread()
{
    this->stopFlag=false;
    this->sleepTime=10;
    //createModbus();

}

ModbusRequestThread::~ModbusRequestThread(){


     qDebug()<<"~ModbusRequestThread"<<endl;

    {

        QMutexLocker locker(&mutex);
        while(!this->transcations.isEmpty()){

            delete transcations.dequeue();
        }

        this->stopFlag=true;
        this->transcationAdded.wakeOne();

    }

    wait();

}


void ModbusRequestThread::createModbus(){


    char parity;
    if(Config::serialParity=="even"||Config::serialParity=="奇"){
        parity = 'E';
    }else if(Config::serialParity=="odd"||Config::serialParity=="偶"){
        parity = 'O';
    }else{
        parity = 'N';
    }


    qDebug()<<Config::serialinterface.toAscii().constData();
    ModbusRequestThread::m_modbus = modbus_new_rtu(  Config::serialinterface.toAscii().constData(),
                                                     Config::serialBaudRate,
                                                     parity,
                                                     Config::serialDatabits,
                                                     Config::serialStopbits );

    if( modbus_connect( ModbusRequestThread::m_modbus ) == -1 )
    {
        qDebug()<<"cant create"<<endl;
    }

}


void ModbusRequestThread::addTranscation(Transcation *transcation){

    QMutexLocker locker(&mutex);
    this->transcations.enqueue(transcation);
    this->transcationAdded.wakeOne();

}


void ModbusRequestThread::sendModbusRequest(Transcation *transcation){

    if( m_modbus == NULL )
    {
        return;
    }


    if( modbus_connect( m_modbus ) == -1 )
    {
        qDebug()<<"cant create"<<endl;
    }

    const int slaveId = transcation->addr->slaveId;
    const int func = transcation->funCode;
    const int satrtAddr = transcation->addr->startAddr;
    int coilNum = transcation->addr->coilNum;

    uint8_t dest[coilNum*sizeof(uint16_t)];

    uint16_t * dest16 = (uint16_t *) dest;

    memset( dest, 0, sizeof( dest ) );

    int ret = -1;
    bool is16Bit = false;
    bool writeAccess = false;
    //const QString dataType = "1111";

    modbus_set_slave( m_modbus, slaveId );

    switch( func )
    {
    case 2:
        ret = modbus_read_input_bits( m_modbus, satrtAddr, coilNum, dest );
        break;
    case 3:
        ret = modbus_read_registers( m_modbus, satrtAddr, coilNum, dest16 );
        is16Bit = true;
        break;
    case 4:
        ret = modbus_read_input_registers( m_modbus, satrtAddr, coilNum, dest16 );
        is16Bit = true;
        break;
    case 6:
        //        ret = modbus_write_register( m_modbus, addr,
        //                    ui->regTable->item( 0, DataColumn )->
        //                        text().toInt(0, 0) );
        //            writeAccess = true;
        //            num = 1;
        break;
    case 16:
        //        int modbus_write_registers(modbus_t *'ctx', int 'addr', int 'nb', const uint16_t *'src');*
        //                    ui->regTable->item( 0, DataColumn )->
        //                        text().toInt(0, 0) );
        //            writeAccess = true;
        //            num = 1;
        break;

    default:
        break;
    }

    qDebug()<<"ret:"<<ret<<endl;
    if( ret == coilNum  )
    {
        if( writeAccess )
        {
            qDebug()<<"Values successfully sent"<<endl;

            transcation->returnCode=1;
            transcation->returnData="";
        }
        else
        {
           // qDebug()<<"here:"<<endl;
            bool b_hex = true;
            QString qsCount="";


            for( int i = 0; i < coilNum; ++i )
            {
                int data = is16Bit ? dest16[i] : dest[i];
                QString qs_num="";
                qs_num=qs_num.sprintf("%d", data);

               // qDebug()<<"addr:"<<QString::number( satrtAddr+i )<<endl;
              //  qDebug()<<"data:"<<qs_num<<endl;

                qsCount+=qs_num+"#";
            }

            transcation->returnCode=1;
            transcation->returnData=qsCount;
        }
    }
    else
    {
       // qDebug()<<"here2:"<<endl;
        if( ret < 0 )
        {
            if(
        #ifdef WIN32
                    errno == WSAETIMEDOUT ||
        #endif
                    errno == EIO
                    )
            {

                qDebug()<<"I/O error: did not receive any data from slave."<<endl;


            }
            else
            {
                qDebug()<<tr( "Slave threw exception \"%1\" or function not implemented." ).arg( modbus_strerror( errno ) )<<endl;
            }
        }
        else
        {
            qDebug()<<"Protocol error:Number of registers returned does not match number of registers requested!"<<endl;

        }

        transcation->returnCode=-1;
        transcation->returnData="";
    }

    modbus_close(m_modbus);

    emit transcationDone(transcation);

}



void ModbusRequestThread::run(){

    forever{

        QMutexLocker locker(&mutex);

        if(this->transcations.isEmpty()){
            qDebug()<<"wait for transtation..."<<endl;
            this->transcationAdded.wait(&mutex);
        }

        if(this->stopFlag){
            break;
        }


        Transcation*trans=this->transcations.dequeue();

        qDebug()<<"get a transation:"<<trans->addr->slaveId<<endl;

        sendModbusRequest(trans);

        //this->msleep(this->sleepTime);

    }
}

