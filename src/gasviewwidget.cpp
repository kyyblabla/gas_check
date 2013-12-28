#include "gasviewwidget.h"
#include "ui_gasviewwidget.h"

#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QRectF>
#include <QImage>
#include <QPixmap>


GasViewWidget::GasViewWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GasViewWidget)
{
    ui->setupUi(this);
    initPainter();
}

void GasViewWidget::initPainter(){


    this->startAngle=-45*16;
    this->endAngle=270*16;

}

void GasViewWidget::paintEvent(QPaintEvent *event){

    QPainter paint(this);

    paint.setRenderHint(QPainter::Antialiasing,true);

    paint.setPen(QPen(Qt::white,0,Qt::NoPen));
    paint.setBrush(QBrush(Qt::white,Qt::SolidPattern));
    paint.drawRect(0,0,this->width(),this->height());


    this->picWidth = this->width()*2/3;
    this->pixHeight=this->picWidth;

    this->x=this->width()*1/6;

    this->y=this->height()*1/10;

    paint.setPen(QPen(Qt::green,2,Qt::SolidLine));

    paint.drawArc(this->x,this->y,this->picWidth,this->pixHeight,this->startAngle,this->endAngle);


    int cx=this->x+ this->picWidth/2;
    int cy=this->y+ this->pixHeight/2;

    this->picWidth-=20;
    this->pixHeight=this->picWidth;

    this->x=cx-this->picWidth/2;
    this->y=cy-this->pixHeight/2;

    paint.setPen(QPen(Qt::green,10,Qt::SolidLine));

    paint.drawArc(this->x,this->y,this->picWidth,this->pixHeight,this->startAngle,this->endAngle);

    //paint.drawImage();

   // QImage image(":/pan.png"); //建立QImage类对象image

    QPixmap image; //建立QImage类对象image

    image.load( ":/pan.png",0,Qt::AvoidDither|Qt::ThresholdDither|Qt::ThresholdAlphaDither);


    QRectF source(0, 0, image.width(), image.height()); //建立源矩形，用来框定源图像文件中要显示的部分

    int taHeight=this->width()*image.height()/image.width();

    QRectF target(0, 0, this->width(),taHeight); //建立目标矩形


   // paint.drawImage(target, image, source);

    paint.drawPixmap(target, image, source);

}

GasViewWidget::~GasViewWidget()
{
    delete ui;
}
