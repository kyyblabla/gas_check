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

    const int grad_num = 6;
    const int kedu_num = 2;

    QPainter painter(this);

    //#EFF7FD

   // painter.setBrush(QBrush(QColor("#E6ECF1")));
  //  painter.drawRect(0,0,this->width(),this->height());


    painter.setRenderHint(QPainter::Antialiasing,true);

    int r=(this->width()/2)/(qCos(commStartAngle*M_PI/180))-30;
    int weight=8;
    //移动坐标系,使得坐标原点在label的下方中间
    painter.translate(width() / 2,r+31);
    //int side = qMin(width(), height());
    //painter.scale(side / 120, side / 120.0);

    QColor co1 = QColor(0, 255, 0);
    QColor co2 = QColor(251, 200, 1);
    QColor co3 = QColor(249, 143, 1);
    QColor co4 = QColor(255, 0, 0);
    QColor co5=  QColor(224, 224, 224);
    QColor co6=  QColor(160, 160, 160);


    QRadialGradient radialGradient(0,0,r,0,0);
    //创建了一个QRadialGradient对象实例，参数分别为中心坐标，半径长度和焦点坐标,如果需要对称那么中心坐标和焦点坐标要一致
    radialGradient.setColorAt(0,co5);
    radialGradient.setColorAt(1.0,co6);
    painter.setBrush(QBrush(radialGradient));

    painter.drawEllipse(-1*this->width(),-1*this->height(),this->width()*2,this->height()*2);



    //draw halo


    QLinearGradient linearGradient = QLinearGradient(-40, 0, 40, 0);
    linearGradient.setColorAt(0.0,co1);
    linearGradient.setColorAt(0.4, co2);
    linearGradient.setColorAt(0.6, co3);
    linearGradient.setColorAt(1, co4);

    painter.setPen(QPen(linearGradient, weight));

    int d_r=r+20;
    QRectF rectangle(-d_r, -d_r, 2*d_r, 2*d_r);




    //画圆弧
    painter.drawArc(rectangle, commStartAngle*16, commEndAngle*16);

    int angle_plud=2;

    commStartAngle-=angle_plud;

    commEndAngle= 180-commStartAngle*2;



    //画数字
    QPen pen3(Qt::white, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen3);
    // painter.save();

    painter.save();

    QPen pen_ziti(Qt::black , 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen_ziti);

    QFont font("Arial",8,QFont::Bold,true);

    font.setCapitalization(QFont::SmallCaps);

    font.setLetterSpacing(QFont::AbsoluteSpacing,0.1);

    painter.setFont(font);

    float precision = maxValue*1.0/grad_num;//precision


    painter.rotate(-commEndAngle/2);

    int num_r=r-6;

    for(int i = 0 ; i <= grad_num ; i++){

        int val_Width=painter.fontMetrics().width(QString::number(i*((int)precision)));

        painter.drawText(0-val_Width/2,-num_r,QString::number(i*((int)precision)));

        painter.rotate(commEndAngle*1.0/grad_num);
    }

    painter.restore();

    painter.save();

    //最顶层
    QPen pen_me(Qt::black,1.5 , Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    pen_me.setColor(QColor("#7D848B"));
    painter.setPen(pen_me);


    int x1 = r+12;
    int y1 = x1;
    int rect_weight = 2*x1;
    int rect_high = 2*y1;

    QRectF rectangle2(-x1, -y1, rect_weight, rect_high);

    painter.drawArc(rectangle2, commStartAngle*16,commEndAngle*16);

    /*画表盘刻度*/
    painter.rotate(-commEndAngle/2+2*angle_plud);

    QPen pen_kedu(Qt::black,1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    pen_kedu.setColor(QColor("#7D848B"));

    for (int i = 0; i <= grad_num + grad_num * (kedu_num-1); i++) {

        if( i % kedu_num == 0){

            painter.setPen(pen_kedu);

            painter.drawLine(x1, 0, x1 - 9, 0);

            painter.rotate( -commEndAngle*1.0 / (grad_num + grad_num * (kedu_num-1)) );

        }else{

            painter.setPen(pen_kedu);

            painter.drawLine(x1, 0, x1 - 4, 0);

            painter.rotate( -commEndAngle*1.0 / (grad_num + grad_num * (kedu_num-1)));

        }
    }
    painter.restore();

    painter.save();

    //  int c_r=r-8;

    //    //绘制指针
    //    QPen pen4(Qt::red, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    //    painter.setPen(pen4);

    QPixmap pic_needle(QString::fromUtf8(":/needle_red.png"));

    QRectF dest_needle(0,0,pic_needle.width(),pic_needle.height());

    QPixmap pic_needle_shadow(QString::fromUtf8(":/needle_shadow.png"));

    QRectF dest_needle_shadow(0,0,pic_needle_shadow.width(),pic_needle_shadow.height());

    int needle_width=8;
    int needle_height=pic_needle.height()*needle_width/pic_needle.width();
    //220*180
    QRectF target_needle(-needle_width/2,-needle_height+18,needle_width,needle_height);


    int len_ro= commEndAngle*ratevalue -  commEndAngle/2;
    painter.rotate(len_ro);

    painter.drawPixmap(target_needle,pic_needle,dest_needle);
    painter.drawPixmap(target_needle,pic_needle_shadow,dest_needle_shadow);

    //painter.drawLine(0,-c_r,0,-r+weight);

    painter.restore();

    //绘制圆心
    QBrush brush(Qt::black);
    painter.setBrush(brush);


    QPixmap pic_cir(QString::fromUtf8(":/overlay.png"));

    QRectF dest_cir(0,0,pic_cir.width(),pic_cir.height());

    int overlay=8;
    //220*180
    QRectF target_cir(-overlay,-overlay,2*overlay,2*overlay);

    painter.drawPixmap(target_cir,pic_cir,dest_cir);
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


