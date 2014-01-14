#include <QSettings>
#include <QMessageBox>
#include <QDebug>

#include "qextserialenumerator.h"
#include "serialsettingswidget.h"
#include "ui_serialsettingswidget.h"
#include "modbusrequestthread.h"
#include "config.h"

extern modbus_t * m_modbus;

SerialSettingsWidget::SerialSettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SerialSettingsWidget)
{
    ui->setupUi(this);

    bool check=Config::serialinterfaceActive==1;

    ui->checkBox->setChecked(check);
    if(check){
        setOptions(true);
    }

    enableGuiItems(check);

}

SerialSettingsWidget::~SerialSettingsWidget()
{
    delete ui;
}




void SerialSettingsWidget::setOptions(bool first){


    int portIndex = 0;
    int i = 0;

    ui->serialPort->clear();

    foreach( QextPortInfo port, QextSerialEnumerator::getPorts() )
    {
        ui->serialPort->addItem( port.friendName );
        if( port.friendName == Config::serialinterface )
        {
            portIndex = i;
        }
        ++i;
    }

    ui->serialPort->setCurrentIndex( portIndex );
    ui->baud->setCurrentIndex( ui->baud->findText(QString::number(Config::serialBaudRate) ));
    ui->dataBits->setCurrentIndex( ui->dataBits->findText( QString::number(Config::serialDatabits)) );
    ui->stopBits->setCurrentIndex( ui->stopBits->findText( QString::number(Config::serialStopbits )) );
    ui->parity->setCurrentIndex( ui->parity->findText(Config::serialParity ) );


    connect( ui->serialPort, SIGNAL( currentIndexChanged( int )),
             this, SIGNAL( selectIndexChanged( int ) ) );
    connect( ui->baud, SIGNAL( currentIndexChanged( int ) ),
             this, SIGNAL( selectIndexChanged( int ) ) );
    connect( ui->dataBits, SIGNAL( currentIndexChanged( int ) ),
             this, SIGNAL( selectIndexChanged( int ) ) );
    connect( ui->stopBits, SIGNAL( currentIndexChanged( int ) ),
             this, SIGNAL( selectIndexChanged( int ) ) );
    connect( ui->parity, SIGNAL( currentIndexChanged( int ) ),
             this, SIGNAL( selectIndexChanged( int ) ) );

}

int SerialSettingsWidget::setupModbusPort()
{
    setOptions(false);
    int portIndex=ui->serialPort->currentIndex();
    changeSerialPort(portIndex);
    return portIndex;
}


void SerialSettingsWidget::releaseSerialModbus()
{
    if(  m_modbus )
    {
        modbus_close(  m_modbus);
        modbus_free(  m_modbus );
        m_modbus = NULL;
    }
}

void SerialSettingsWidget::changeModbusInterface(const QString& port, char parity)
{
    releaseSerialModbus();

    qDebug()<<port.toAscii().constData();
    m_modbus = modbus_new_rtu( port.toAscii().constData(),
                               ui->baud->currentText().toInt(),
                               parity,
                               ui->dataBits->currentText().toInt(),
                               ui->stopBits->currentText().toInt() );

    //modbus_set_slave(ModbusRequestThread::m_modbus,112);

    if( modbus_connect( m_modbus ) == -1 ) {
        QMessageBox::critical( this, tr( "Connection failed" ),
                               tr( "Could not connect serial port!" ) );
    }
}


static inline QString embracedString( const QString & s )
{
    return s.section( '(', 1 ).section( ')', 0, 0 );
}


void SerialSettingsWidget::changeSerialPort( int )
{
    const int iface = ui->serialPort->currentIndex();

    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();
    if( !ports.isEmpty() )
    {


#ifdef Q_OS_WIN32
        QString port = ports[iface].portName;

        // is it a serial port in the range COM1 .. COM9?
        if ( port.startsWith( "COM" ) )
        {
            // use windows communication device name "\\.\COMn"
            port = "\\\\.\\" + port;
        }
#else
        const QString port = ports[iface].physName;
#endif


        Config::updateConfig("serialSetting/serialinterface",port);
        Config::updateConfig("serialSetting/serialBaudRate",ui->baud->currentText());
        Config::updateConfig("serialSetting/serialDatabits",ui->dataBits->currentText());
        Config::updateConfig("serialSetting/serialStopbits",ui->stopBits->currentText());
        Config::updateConfig("serialSetting/serialParity",ui->parity->currentText());

        char parity;
        switch( ui->parity->currentIndex() )
        {
        case 1: parity = 'O'; break;
        case 2: parity = 'E'; break;
        default:
        case 0: parity = 'N'; break;
        }

        changeModbusInterface(port, parity);
    }
    else
    {
        QMessageBox::critical( this, tr( "No serial port found" ),
                               tr( "Could not find any serial port "
                                   "on this computer!" ) );
    }
}


void SerialSettingsWidget::enableGuiItems(bool checked)
{
    ui->serialPort->setEnabled(checked);
    ui->baud->setEnabled(checked);
    ui->dataBits->setEnabled(checked);
    ui->stopBits->setEnabled(checked);
    ui->parity->setEnabled(checked);
}

void SerialSettingsWidget::on_checkBox_clicked(bool checked)
{
    int bo=0;
    if (checked) {
        setupModbusPort();
        bo=1;
    }
    else {
        releaseSerialModbus();
    }


    Config::updateConfig("serialSetting/serialinterfaceActive",QString::number(bo));

    enableGuiItems(checked);

    emit serialPortActive(checked);
}
