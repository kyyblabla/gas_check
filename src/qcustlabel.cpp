#include "qcustlabel.h"

#include <QPaintEvent>
#include <QLabel>
#include <QPainter>
#include <QTimer>
#include <QLineF>
#include <QPointF>
#include <QPen>

QCustLabel::QCustLabel(QWidget *parent) :
    QLabel(parent),labelType(QCustLabel::No)
{
    this->setAlignment(Qt::AlignCenter);
    this->timer=new QTimer();
    connect(this->timer,SIGNAL(timeout()),this,SLOT(repaint()));

    timeCount=0;

}

QCustLabel::~QCustLabel(){

    delete  timer;

}

void QCustLabel::setDesInfo(QString desInfo){

    this->desInfo=desInfo;

}

void QCustLabel::setLabelType(LabelType type){

    this->labelType=type;
}


void QCustLabel::paintEvent(QPaintEvent *event){



    QLabel::paintEvent(event);

    QPainter painter(this);

    painter.setPen(Qt::white);

    //QLabel::fontMetrics().width(QString s)
    //QLabel::fontMetrics().height()

    QString info=this->desInfo;

    int l=this->width()/2-(this->fontMetrics().width(info)/2);
    int t=this->height()/2+(this->fontMetrics().height()/2);

    painter.drawText(QPoint(l,t),info);

//     if(this->labelType==QCustLabel::MainDevice){

//        if(!this->timer->isActive()){
//            this->timer->start(300);
//        }

//        QPointF p1(30,15);
//        QPointF p2(30,75);
//        QLineF f(p1,p2);

//        if(this->timeCount/2==0){
//            painter.setPen(QPen(Qt::red,Qt::SolidLine));

//        }else{
//            painter.setPen(QPen(Qt::white,Qt::DotLine));
//        }

//        painter.drawLine(f);

//        this->timeCount++;

//     }


}

