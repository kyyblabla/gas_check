#include "dialpan.h"
#include <QPainter>
#include <QPen>
#include <QRectF>
#include <QLinearGradient>
#include <QPaintEvent>
#include <QtCore/qmath.h>
#include <QDebug>

dialpan::dialpan(QWidget *parent) :
    QLabel(parent)
{
    this->setRateValue(0);
    update();

    this->maxValue=200;
    this->minValue=0;

}

dialpan::~dialpan() {

    qDebug()<<"~dialpan"<<endl;

}


void dialpan::paintEvent(QPaintEvent *) {


    int commStartAngle=45;

    int commEndAngle= 180-commStartAngle*2;

    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    int r=(this->width()/2)/(qCos(commStartAngle*M_PI/180))-30;
    int weight=15;
    //移动坐标系,使得坐标原点在label的下方中间
    painter.translate(width() / 2,r+20);
    //int side = qMin(width(), height());
    //painter.scale(side / 120, side / 120.0);

    QColor co1 = QColor(0, 255, 0);
    QColor co2 = QColor(251, 200, 1);
    QColor co3 = QColor(249, 143, 1);
    QColor co4 = QColor(255, 0, 0);

    /*pen1是最外边的大圆弧*/
    QLinearGradient linearGradient = QLinearGradient(-60, 0, 60, 0);
    linearGradient.setColorAt(0.0,co1);
    linearGradient.setColorAt(0.4, co2);
    linearGradient.setColorAt(0.6, co3);
    linearGradient.setColorAt(1, co4);

    painter.setPen(QPen(linearGradient, weight));


    QRectF rectangle(-r, -r, 2*r, 2*r);
    int startAngle = commStartAngle * 16;
    int spanAngle = commEndAngle * 16;

    //画圆弧
    painter.drawArc(rectangle, startAngle, spanAngle);

    /*pen3是最里面的那个圆弧*/
    QPen pen3(Qt::white, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);


    painter.setPen(pen3);

    // painter.save();

    int len=3;

    int rote=commEndAngle/(len-1);

    //painter.rotate(-commEndAngle/2-2);

    painter.save();
    //painter.drawLine(88, 0, 80, 0);

    painter.rotate(-rote);

    int val_Width=painter.fontMetrics().width(QString::number(this->minValue));

    painter.drawText(0-val_Width/2,-r-10,QString::number(this->minValue));

    painter.rotate(rote);

    int midValue=(this->maxValue-this->minValue)/2;
    val_Width=painter.fontMetrics().width(QString::number(midValue));

    painter.drawText(0-val_Width/2,-r-10,QString::number(midValue));

    painter.rotate(rote);

    val_Width=painter.fontMetrics().width(QString::number(this->maxValue));

    painter.drawText(0-val_Width/2,-r-10,QString::number(this->maxValue));


    painter.restore();



    //painter.restore();


    //绘制圆心
    QBrush brush(Qt::white);
    painter.setBrush(brush);

    int c_r=3;
    painter.drawEllipse(-c_r,-c_r,2*c_r,2*c_r);


    painter.save();
    //绘制指针
    QPen pen4(Qt::red, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen4);

    int len_ro= commEndAngle*ratevalue -  commEndAngle/2;



    painter.rotate(len_ro);

    painter.drawLine(0,-c_r,0,-r+weight);

    painter.restore();



    //绘制文字
    //    QString val=QString::number(ratevalue);

    //    int valWidth=painter.fontMetrics().width(val);

    //    int valHeight=painter.fontMetrics().height();

    //    painter.drawText(0-valWidth/2,0+valHeight,val);



}

/*设置ratevalue*/
void dialpan::setRateValue(double ratevalue) {

    float tempRatevalue= ratevalue/(this->maxValue-this->minValue);
    this->ratevalue = tempRatevalue>1.0?1.0:tempRatevalue<0?0:tempRatevalue;
    this->repaint();
}

/*得到ratevalue*/
double dialpan::getRateValue() {
    return this->ratevalue;
}


void dialpan::setValueRange(int minValue, int maxValue){
    this->maxValue=maxValue;
    this->minValue=minValue;

}


