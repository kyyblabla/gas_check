#include "linkstatuswidget.h"
#include "ui_linkstatuswidget.h"

#include <QPainter>
#include <QPaintEvent>
#include <QShowEvent>
#include <QTimerEvent>
#include <QRectF>
#include <QPixmap>
#include <QColor>
#include <QLinearGradient>
#include <QPoint>
#include <QVector>
#include <QDebug>
#include <QTimer>


LinkStatusWidget::LinkStatusWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LinkStatusWidget)
{
    ui->setupUi(this);

    this->paintTimer=new QTimer;

    connect(paintTimer, SIGNAL(timeout()), this, SLOT(updateData()));

    this->init();

}


int LinkStatusWidget::getLineLength(int index,int type){

    if(this->lines.size()==0||index<0||index>=this->lines.size()){
        return 0;
    }

    return type==0?qAbs(lines.at(index).dx()):qAbs(lines.at(index).dy());

}

void LinkStatusWidget::initLines(){



    int lineLeft=this->left_left+this->left_width+this->left_space;
    int lineRight=this->width()-this->right_right;


    int centerHeight=this->right_top+this->right_height+this->right_space/2;

    QPoint p_left_left(lineLeft,centerHeight);
    QPoint p_left_right(lineRight,centerHeight);

    QLine line_1(p_left_left,p_left_right);

    int lineRightRight=lineRight+this->right_space;
    int lineRightTop=centerHeight- this->right_space/2-this->right_height/2;
    int lineRightBottom= centerHeight+this->right_space/2+this->right_height/2;

    QPoint p_right_top_left(lineRightRight,lineRightTop);
    QPoint p_right_top_right(lineRightRight,lineRightBottom);

    QLine line_2(p_right_top_left,p_right_top_right);

    lines.append(line_1);
    lines.append(line_2);


}


void LinkStatusWidget::isConnection(bool isConn){

    this->isConn=isConn;

    if(  this->isConn){

        this->paintTimer->start(15);

    }else{

        this->paintTimer->stop();
    }

    this->repaint();
}

void LinkStatusWidget::init(){



    left_left=10;
    left_top=10;
    left_space=6;
    left_width=100;
    left_height=100;

    right_right=20;
    right_top=10;
    right_space=6;
    right_width=70;
    right_height=70;

    line_width_main=100;
    line_width_sub=30;

    //this->isGuai=true;

    this->countMain=0;

    this->isBroken_1=false;
    this->isBroken_2=false;

    this->isConn=false;

}

LinkStatusWidget::~LinkStatusWidget()
{

    qDebug()<<"~LinkStatusWidget"<<endl;

    delete paintTimer;
    delete ui;

    qDebug()<<"~LinkStatusWidget"<<endl;

}

void LinkStatusWidget::paintEvent(QPaintEvent *event){


    QPainter painter(this);

    QPixmap pic(QString::fromUtf8(":/computer_white.png"));

    QRectF dest(0,0,pic.width(),pic.height());


    QRectF target_0(this->left_left,this->left_top,this->left_width,this->left_height);

    QRectF target_1(this->width()-this->right_right-this->right_width,this->right_top,this->right_width,this->right_height);

    QRectF target_2(this->width()-this->right_right-this->right_width,this->right_top+this->right_height+this->right_space,this->right_width,this->right_height);


    painter.drawPixmap(target_0,pic,dest);

    painter.drawPixmap(target_1,pic,dest);

    painter.drawPixmap(target_2,pic,dest);


    //draw base line
    painter.save();
    //#353942
    QPen pen1(Qt::white,8,Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    pen1.setColor(QColor(53, 57, 66));

    painter.setPen(pen1);
    painter.drawLines(lines);
    painter.restore();

    if(!this->isConn){
        return;
    }

    int centerHeight=this->right_top+this->right_height+this->right_space/2;

    QColor co1 =QColor(146, 196, 15) ;
    QColor co2 =QColor(0, 255, 0, 0);

    QColor co3 =QColor( 255,0, 0,200);
    QColor co4 =QColor( 255,0,0, 0);


    if(this->isBroken_1){

        int mleft=this->left_left+this->left_width+this->left_space;
        int mright=this->width()-this->right_right;

        int mcenter= mleft+(mright-mleft)/2;

        int lineWeight=10;
        int mbottom= centerHeight-lineWeight/2;
        int mtop=centerHeight+ lineWeight/2;

        QLinearGradient linearGradient2 = QLinearGradient(mcenter,mtop,mcenter,mbottom);
        linearGradient2.setColorAt(0,co3);
        linearGradient2.setColorAt(0.5,co4);
        linearGradient2.setColorAt(1,co3);

        QPen pen_w(linearGradient2,lineWeight);
        pen_w.setCapStyle(Qt::RoundCap);
        painter.setPen(pen_w);
        painter.drawLine(mleft,centerHeight,mright,centerHeight);


    }else{

        //message
        int mleft=this->width()-this->right_right-this->right_width-this->right_space-this->countMain;
        int mright=mleft+this->line_width_main;


        QLinearGradient linearGradient = QLinearGradient(mleft,centerHeight,mright,centerHeight);
        linearGradient.setColorAt(0,co1);
        linearGradient.setColorAt(1,co2);

        QPen pen2(linearGradient,5);
        pen2.setCapStyle(Qt::RoundCap);
        painter.setPen(pen2);
        painter.drawLine(mleft,centerHeight,mright,centerHeight);

    }

    //message 2
    if(this->isBroken_2){


    }else{
        int sbottom= this->right_top+this->right_height/2+this->countSub;
        int stop= sbottom-this->line_width_sub;
        int sright=this->width()-this->right_right+this->right_space;

        QLinearGradient linearGradient2 = QLinearGradient(sright,stop,sright,sbottom);
        linearGradient2.setColorAt(0,co2);
        linearGradient2.setColorAt(1,co1);

        QPen pen3(linearGradient2,4);
        pen3.setCapStyle(Qt::RoundCap);
        painter.setPen(pen3);

        painter.drawLine(sright,stop,sright,sbottom);
    }


    //   painter.save();

    //    painter.translate(this->left_left+this->left_width-this->left_space,centerHeight);

    //    int pi_r=70;

    //    QColor co5 =QColor(0,225,0,100);
    //    QColor co6 =QColor(0,225,0,0);

    //    QLinearGradient linearGradient3 = QLinearGradient(0,0,pi_r,0);
    //    linearGradient3.setColorAt(0,co5);
    //    linearGradient3.setColorAt(1,co6);


    //    painter.setBrush( QBrush(linearGradient3));
    //    painter.drawPie(-pi_r,-pi_r,2*pi_r,2*pi_r,-70*16,140*16);

    //   painter.restore();


}


void LinkStatusWidget::showEvent(QShowEvent *event){

    initLines();




}


void LinkStatusWidget::updateData(){

    countMain+=3;

    if(countMain>=(getLineLength(0,0)-this->line_width_main+20)){
        countMain=0;
    }

    countSub+=1;
    if(countSub>=getLineLength(1,1)){
        countSub=0;
    }

    repaint();

}


