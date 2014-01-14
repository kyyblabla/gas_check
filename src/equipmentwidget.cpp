#include "equipmentwidget.h"
#include "config.h"
#include "dialpan.h"

#include <QStringList>
#include <QVBoxLayout>
#include <QDebug>
#include <QSpacerItem>
#include <QSizePolicy>
#include <QPushButton>
#include <QPainter>
#include <QPen>



EquipmentWidget::EquipmentWidget(QWidget *parent) :
    QWidget(parent)
{
    initLables();

    this->dPan->setValueRange(Config::ndLableMin,Config::ndLableMax);

    this->setStyleSheet("color:#fff");

    this->setTitle("");

}

void EquipmentWidget::setTitle(QString title){

    this->ltitle->setText(title);


}

EquipmentWidget::~EquipmentWidget(){

    delete infoLabel;
    delete dPan;

}


bool EquipmentWidget::updateLableValue(int labelIndex, int value){

    bool change=false;

    switch(labelIndex){
    case 1:
        this->gasValue=value;
        break;
    case 2:
        if(value != this->onOffValue){
            this->onOffValue=value;
            change=true;
        }
        break;
    case 3:
        if(value != this->workBreakValue){
            this->workBreakValue=value;
            change=true;
        }
        break;
    case 4:
        if(value != this->waringValue){
            this->waringValue=value;
            change=true;
        }
        break;
    default:
        break;
    }

    updateLables();

    return change;

}


void EquipmentWidget::updateLables(){

    // qDebug()<<"gasValue:"<<gasValue<<endl;



    this->dPan->setRateValue(this->gasValue);

    this->lNongDuLabel->setText(lNongDuLabelName+QString::number(gasValue)+lNongDuLabelValue);

    this->waringLevelValue = this->waringValue>0?waringValue:(this->workBreakValue>0||this->onOffValue>0?1:0);

    if(waringLevelValue==3){

        this->infoLabel->setText(lWaringLabelName+lWaringLabelValue.split("/").at(2));

    }else if(waringLevelValue==2){

        this->infoLabel->setText(lWaringLabelName+lWaringLabelValue.split("/").at(1));

    }else if(waringLevelValue==1){

        if(this->workBreakValue==1){

            infoLabel->setText(lWorkOrBreakLabelName+lWorkOrBreakLabelValue.split("/").at(1));

        }else{

            infoLabel->setText(lOnOrOffLabelName+lOnOrOffLabelValue.split("/").at(1));
        }



    }else{

        infoLabel->setText(tr("work normal"));
    }

}





void EquipmentWidget::initLables(){


    QStringList list= Config::EQUIPMENT_LABEL.split("#");
    lNongDuLabelName=list.at(0).split("|").at(0);
    lNongDuLabelValue=list.at(0).split("|").at(1);
    this->gasValue=0;


    lOnOrOffLabelName=list.at(1).split("|").at(0);
    lOnOrOffLabelValue=list.at(1).split("|").at(1);
    this->onOffValue=0;


    lWorkOrBreakLabelName=list.at(2).split("|").at(0);
    lWorkOrBreakLabelValue=list.at(2).split("|").at(1);
    this->workBreakValue=0;


    lWaringLabelName=list.at(3).split("|").at(0);
    lWaringLabelValue=list.at(3).split("|").at(1);
    this->waringValue=0;

    setLabels();


}

void EquipmentWidget::setLabels(){


    QGridLayout *layout=new QGridLayout;
    this->setLayout(layout);
    layout->setMargin(0);
    layout->setSpacing(0);

    ltitle=new QLabel;
    ltitle->setAlignment(Qt::AlignCenter);
    layout->addWidget(ltitle,0,0);

    this->dPan=new dialpan;

    this->lNongDuLabel=new QLabel;
    lNongDuLabel->setAlignment(Qt::AlignCenter);

    this->infoLabel=new QLabel;
    infoLabel->setAlignment(Qt::AlignCenter);


    layout->addWidget(dPan,1,0,4,1);

    lNongDuLabel->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Ignored);

    layout->addWidget(lNongDuLabel,5,0);

    infoLabel->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Ignored);
    layout->addWidget(infoLabel,6,0);

    //    qb1=new QPushButton;
    //    qb1->setText(tr("Close1"));

    //    layout->addWidget(qb1,7,0);

    //    qb2=new QPushButton;
    //    qb2->setText(tr("Close2"));

    //    layout->addWidget(qb2,8,0);

    updateLables();


}

void EquipmentWidget::setVisible(int i){



}

void EquipmentWidget::paintEvent(QPaintEvent *event){


    QPainter painter(this);

    QPen pen;
    pen.setColor(Qt::gray);
    pen.setStyle(Qt::DotLine);

    int plud=20;
    int x1=this->width()-1;
    int y1=plud;
    int x2=x1;
    int y2=this->height()-plud;

    painter.setPen(pen);
    painter.drawLine(x1,y1,x2,y2);


    x1=0;
    y1=this->height()-1;
    x2=this->width();
    y2=y1;

    painter.setPen(pen);
    painter.drawLine(x1,y1,x2,y2);


}

