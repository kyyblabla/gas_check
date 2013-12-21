#include "modbusrequestthread.h"
#include "modbus-private.h"

#include <QMessageBox>
#include <QDebug>

modbus_t* ModbusRequestThread::m_modbus;

ModbusRequestThread::ModbusRequestThread()
{
    this->flag=true;
    this->sleepTime=1000;
}

ModbusRequestThread::~ModbusRequestThread(){

    stop();

}


void ModbusRequestThread::sendModbusRequest(){



    if( m_modbus == NULL )
    {
        return;
    }

    //int slaveID
    //int func
    //int startAddr
    //int numCoils
    //
    const int slave = 101;
    const int func = 4;
    const int addr = 0;
    int num = 1;

    uint8_t dest[1024];

    uint16_t * dest16 = (uint16_t *) dest;

    memset( dest, 0, 1024 );

    int ret = -1;
    bool is16Bit = false;
    bool writeAccess = false;
    const QString dataType = "1111";


    qDebug()<<"0"<<endl;
    modbus_set_slave( m_modbus, slave );
    qDebug()<<"1"<<endl;
    switch( func )
    {

    qDebug()<<func<<endl;
    case 1:
        ret = modbus_read_bits( m_modbus, addr, num, dest );
        break;
    case 2:
        ret = modbus_read_input_bits( m_modbus, addr, num, dest );
        break;
    case 3:
        ret = modbus_read_registers( m_modbus, addr, num, dest16 );
        is16Bit = true;
        break;
    case 4:
        ret = modbus_read_input_registers( m_modbus, addr, num, dest16 );
        is16Bit = true;
        break;
        /*case MODBUS_FC_WRITE_SINGLE_COIL:
            ret = modbus_write_bit( m_modbus, addr,
                    ui->regTable->item( 0, DataColumn )->
                        text().toInt(0, 0) ? 1 : 0 );
            writeAccess = true;
            num = 1;
            break;
        case MODBUS_FC_WRITE_SINGLE_REGISTER:
            ret = modbus_write_register( m_modbus, addr,
                    ui->regTable->item( 0, DataColumn )->
                        text().toInt(0, 0) );
            writeAccess = true;
            num = 1;
            break;

        case MODBUS_FC_WRITE_MULTIPLE_COILS:
        {
            uint8_t * data = new uint8_t[num];
            for( int i = 0; i < num; ++i )
            {
                data[i] = ui->regTable->item( i, DataColumn )->
                                text().toInt(0, 0);
            }
            ret = modbus_write_bits( m_modbus, addr, num, data );
            delete[] data;
            writeAccess = true;
            break;
        }
        case MODBUS_FC_WRITE_MULTIPLE_REGISTERS:
        {
            uint16_t * data = new uint16_t[num];
            for( int i = 0; i < num; ++i )
            {
                data[i] = ui->regTable->item( i, DataColumn )->
                                text().toInt(0, 0);
            }
            ret = modbus_write_registers( m_modbus, addr, num, data );
            delete[] data;
            writeAccess = true;
            break;
        }
        */
    default:
        break;
    }

    qDebug()<<"ret:"<<ret<<endl;
    if( ret == num  )
    {
        if( writeAccess )
        {
            qDebug()<<"Values successfully sent"<<endl;
        }
        else
        {
            qDebug()<<"here:"<<endl;
            bool b_hex = true;
            QString qs_num;

            for( int i = 0; i < num; ++i )
            {
                int data = is16Bit ? dest16[i] : dest[i];

                qs_num.sprintf( b_hex ? "0x%04x" : "%d", data);

                qDebug()<<"dt:"<<dataType<<endl;
                qDebug()<<"addr:"<<QString::number( addr+i )<<endl;
                qDebug()<<"data:"<<qs_num<<endl;
            }
        }
    }
    else
    {
        qDebug()<<"here2:"<<endl;
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
    }


}



void ModbusRequestThread::run(){

    while(flag){

        sendModbusRequest();

        this->sleep(this->sleepTime);

    }
}


void ModbusRequestThread::stop(){

    this->flag=false;

}

