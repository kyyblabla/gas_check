#include "linkstatuswidget.h"
#include "ui_linkstatuswidget.h"
#include "config.h"


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

    lines.clear();

    int lineLeft=this->left_left+this->left_width+this->left_space;
    int lineRight=this->width()-this->right_right;

    int centerHeight=this->right_top+this->right_height+this->right_space/2;

    QPoint p_left_left(lineLeft,centerHeight);
    QPoint p_left_right(lineRight,centerHeight);

    QLine line_1(p_left_left,p_left_right);

    int lineRightRight=this->width()-this->right_right+this->right_space;
    int lineRightTop=centerHeight- this->right_space/2-this->right_height/2;
    int lineRightBottom= centerHeight+this->right_space/2+this->right_height/2;

    QPoint p_right_top_left(lineRightRight,lineRightTop);
    QPoint p_right_top_right(lineRightRight,lineRightBottom);

    QLine line_2(p_right_top_left,p_right_top_right);

    lines.append(line_1);
    lines.append(line_2);


}

void LinkStatusWidget::setLinkStatu(int index, bool statu){

    if(index==1){

        this->isBroken_1=statu;


    }else if(index==2){

        this->isBroken_2=statu;

    }

    this->repaint();


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
    left_top=0;
    left_space=6;
    left_width=110;
    left_height=90;

    right_right=20;
    right_top=0;
    right_space=6;
    right_width=70;
    right_height=70;

    line_width_main=100;
    line_width_sub=30;

    //this->isGuai=true;

    this->countMain=0;

    this->isBroken_1=true;
    this->isBroken_2=true;

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

    initLines();

    QPainter painter(this);

    QPixmap pic(QString::fromUtf8(":/computer_white.png"));

    QRectF dest(0,0,pic.width(),pic.height());



    QPixmap pic2(QString::fromUtf8(":/honeywell.png"));

    QRectF dest2(0,0,pic2.width(),pic2.height());
    //220*180

    QRectF target_0(this->left_left,this->left_top,this->left_width,this->left_height);

    QRectF target_1(this->width()-this->right_right-this->right_width,this->right_top,this->right_width,this->right_height);

    QRectF target_2(this->width()-this->right_right-this->right_width,this->right_top+this->right_height+this->right_space,this->right_width,this->right_height);

    painter.setPen(Qt::white);
    painter.drawPixmap(target_0,pic2,dest2);

    painter.drawText(this->left_left+this->left_width+this->left_space,this->left_top+painter.fontMetrics().height(),Config::LINKSTATUS_LABEL.split("#").at(2));



    painter.drawPixmap(target_1,pic,dest);

    QString text=Config::LINKSTATUS_LABEL.split("#").at(0);
    int f_w=painter.fontMetrics().width(text);

    painter.drawText(this->width()-this->right_right-this->right_width-this->right_space*2-f_w,this->right_top+painter.fontMetrics().height()+this->right_space,text);

    painter.drawPixmap(target_2,pic,dest);

    text=Config::LINKSTATUS_LABEL.split("#").at(1);
    f_w=painter.fontMetrics().width(text);


    painter.drawText(this->width()-this->right_right-this->right_width-this->right_space*2-f_w,this->right_top+this->right_height+this->right_space*2+painter.fontMetrics().height(),text);



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


    int mleft=this->width()-this->right_right-this->right_width-this->right_space-this->countMain;
    int mright=mleft+this->line_width_main;

    if(this->isBroken_1){

        QLinearGradient linearGradient = QLinearGradient(mleft,centerHeight,mright,centerHeight);
        linearGradient.setColorAt(0,co3);
        linearGradient.setColorAt(1,co4);

        QPen pen2(linearGradient,5);
        pen2.setCapStyle(Qt::RoundCap);
        painter.setPen(pen2);

    }else{

        QLinearGradient linearGradient = QLinearGradient(mleft,centerHeight,mright,centerHeight);
        linearGradient.setColorAt(0,co1);
        linearGradient.setColorAt(1,co2);

        QPen pen2(linearGradient,5);
        pen2.setCapStyle(Qt::RoundCap);
        painter.setPen(pen2);

    }

    painter.drawLine(mleft,centerHeight,mright,centerHeight);


    int sbottom= this->right_top+this->right_height/2+this->countSub;
    int stop= sbottom-this->line_width_sub;
    int sright=this->width()-this->right_right+this->right_space;

    //message 2
    if(this->isBroken_2){

        QLinearGradient linearGradient2 = QLinearGradient(sright,stop,sright,sbottom);
        linearGradient2.setColorAt(0,co4);
        linearGradient2.setColorAt(1,co3);

        QPen pen3(linearGradient2,4);
        pen3.setCapStyle(Qt::RoundCap);
        painter.setPen(pen3);

    }else{


        QLinearGradient linearGradient2 = QLinearGradient(sright,stop,sright,sbottom);
        linearGradient2.setColorAt(0,co2);
        linearGradient2.setColorAt(1,co1);

        QPen pen3(linearGradient2,4);
        pen3.setCapStyle(Qt::RoundCap);
        painter.setPen(pen3);


    }

    painter.drawLine(sright,stop,sright,sbottom);


}


void LinkStatusWidget::showEvent(QShowEvent *event){

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
