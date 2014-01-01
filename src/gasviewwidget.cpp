#include "gasviewwidget.h"
#include "ui_gasviewwidget.h"
#include "speedo_meter.h"
#include "config.h"

#include "Qwt/qwt_compass.h"
#include "Qwt/qwt_compass_rose.h"
#include "Qwt/qwt_dial_needle.h"

#include <QGridLayout>
#include <QPalette>
#include <QTimer>



GasViewWidget::GasViewWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GasViewWidget)
{
    ui->setupUi(this);

    setAutoFillBackground( true );

    setPalette( colorTheme( QColor( Qt::darkGray ).dark( 150 ) ) );

    QVBoxLayout *layout=new QVBoxLayout(this);
    layout->setSpacing( 5 );
    layout->setMargin( 0 );

    QwtDial *dial = createDial();
    layout->addWidget(dial);
}


GasViewWidget::~GasViewWidget()
{
    delete ui;
}

QwtDial *GasViewWidget::createDial(  )
{
    QwtDial *dial = NULL;

    d_speedo = new SpeedoMeter( this );
    d_speedo->setScaleStepSize( Config::ndLableStep );
    d_speedo->setScale( Config::ndLableMin, Config::ndLableMax );
    d_speedo->scaleDraw()->setPenWidth( 2 );

    d_speedo->setLabel(Config::ndLableName);

    d_speedo->setValue(0);

    dial = d_speedo;

    if ( dial )
    {
        dial->setReadOnly( true );
        dial->setLineWidth( 4 );
        dial->setFrameShadow( QwtDial::Sunken );
    }

    return dial;
}

QPalette GasViewWidget::colorTheme( const QColor &base ) const
{
    QPalette palette;
    palette.setColor( QPalette::Base, base );
    palette.setColor( QPalette::Window, base.dark( 150 ) );
    palette.setColor( QPalette::Mid, base.dark( 110 ) );
    palette.setColor( QPalette::Light, base.light( 170 ) );
    palette.setColor( QPalette::Dark, base.dark( 170 ) );
    palette.setColor( QPalette::Text, base.dark( 200 ).light( 800 ) );
    palette.setColor( QPalette::WindowText, base.dark( 200 ) );

    return palette;
}


void GasViewWidget::setGanNd(double nd){


    if(nd<Config::ndLableMin){

        nd=0;

    }else if(nd>Config::ndLableMin){

        nd=Config::ndLableMax;
    }

    d_speedo->setValue(nd);

}



