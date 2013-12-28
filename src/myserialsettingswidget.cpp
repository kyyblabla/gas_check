#include "myserialsettingswidget.h"
#include "ui_myserialsettingswidget.h"
#include "qextserialenumerator.h"
#include "config.h"

MySerialSettingsWidget::MySerialSettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MySerialSettingsWidget)
{
    ui->setupUi(this);
}



MySerialSettingsWidget::~MySerialSettingsWidget()
{
    delete ui;
}


void MySerialSettingsWidget::creatConnects(){

    connect( ui->serialPort, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( changeSerialPort( int ) ) );
    connect( ui->baud, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( changeSerialPort( int ) ) );
    connect( ui->dataBits, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( changeSerialPort( int ) ) );
    connect( ui->stopBits, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( changeSerialPort( int ) ) );
    connect( ui->parity, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( changeSerialPort( int ) ) );

}

void MySerialSettingsWidget::changeSerialPort(int index){


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

    }
}
