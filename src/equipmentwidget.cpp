#include "equipmentwidget.h"
#include "config.h"
#include "dialpan.h"

#include <QStringList>
#include <QVBoxLayout>
#include <QDebug>
#include <QSpacerItem>
#include <QSizePolicy>



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


    layout->addWidget(dPan,1,0,3,1);

    lNongDuLabel->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Ignored);

    layout->addWidget(lNongDuLabel,4,0);

    infoLabel->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Ignored);
    layout->addWidget(infoLabel,5,0);


    updateLables();


}


//void EquipmentWidget::updateLabelInfo(int labelName, int status, QString info){

//    switch (labelName) {
//    case 0:
//        switch(status){
//        case 1:
//            this->lLightLabel->setPixmap(QPixmap(QString::fromUtf8(":/yellow.png")));
//            break;
//        case 2:
//            this->lLightLabel->setPixmap(QPixmap(QString::fromUtf8(":/orange.png")));
//            break;
//        case 3:
//            this->lLightLabel->setPixmap(QPixmap(QString::fromUtf8(":/red.png")));
//            break;
//        default:
//            this->lLightLabel->setPixmap(QPixmap(QString::fromUtf8(":/green.png")));
//            break;
//        }
//        break;
//    case  1:
//        this->lNongDuLabel->setText(lNongDuLabelName+info+lNongDuLabelValue);
//        lNongDuLabel->setStyleSheet("color:"+Config::colorLevel.split("|").at(0));
//        break;
//    case  2:

//        if(status==1){

//            this->lOnOrOffLabel->setText(lOnOrOffLabelName+lOnOrOffLabelValue.split("/").at(1));
//            lOnOrOffLabel->setStyleSheet("color:"+Config::colorLevel.split("|").at(1));

//        }else{

//            this->lOnOrOffLabel->setText(lOnOrOffLabelName+lOnOrOffLabelValue.split("/").at(0));
//            lOnOrOffLabel->setStyleSheet("color:"+Config::colorLevel.split("|").at(0));
//        }

//        break;
//    case  3:
//        if(status==1){
//            lWorkOrBreakLabel->setText(lWorkOrBreakLabelName+lWorkOrBreakLabelValue.split("/").at(1));
//            lWorkOrBreakLabel->setStyleSheet("color:"+Config::colorLevel.split("|").at(1));
//        }else{

//            lWorkOrBreakLabel->setText(lWorkOrBreakLabelName+lWorkOrBreakLabelValue.split("/").at(0));
//            lWorkOrBreakLabel->setStyleSheet("color:"+Config::colorLevel.split("|").at(0));
//        }
//        break;
//    case  4:
//        if(status==1){

//            lWaringLabel->setStyleSheet("color:"+Config::colorLevel.split("|").at(2));
//            lWaringLabel->setText(lWaringLabelName+lWaringLabelValue.split("/").at(1));

//        }else if(status==2){
//            lWaringLabel->setStyleSheet("color:"+Config::colorLevel.split("|").at(3));
//            lWaringLabel->setText(lWaringLabelName+lWaringLabelValue.split("/").at(2));

//        }else{
//            lWaringLabel->setStyleSheet("color:"+Config::colorLevel.split("|").at(0));
//            lWaringLabel->setText(lWaringLabelName+lWaringLabelValue.split("/").at(0));
//        }
//        break;
//    default:
//        break;
//    }

//}


//bool EquipmentWidget::updateLabelVlaue(int labelIndex, int status){

//    bool change=false;
//    switch (labelIndex) {
//    case  1:
//        this->lNongDuLabelStatus=status;
//        break;
//    case  2:
//        if(this->lOnOrOffLabelStatus!=status){
//            change=true;
//            this->lOnOrOffLabelStatus=status;
//        }

//        break;
//    case  3:
//        if( this->lWorkOrBreakLabelStatus!=status){
//            change=true;
//            this->lWorkOrBreakLabelStatus=status;
//        }

//        break;
//    case  4:

//        qDebug()<<"lWaringLabelStatus:"<<lWaringLabelStatus<<endl;
//        qDebug()<<"status:"<<status<<endl;
//        if(this->lWaringLabelStatus!=status){
//            change=true;
//            this->lWaringLabelStatus=status;
//        }
//        break;
//    default:
//        break;
//    }

//    updateInfo();

//    return change;

//}


//void EquipmentWidget::updateInfo(){



//    this->lNongDuLabel->setText(lNongDuLabelName+QString::number(this->lNongDuLabelStatus)+lNongDuLabelValue);
//    lNongDuLabel->setStyleSheet("color:"+Config::colorLevel.split("|").at(0));

//    if(this->lOnOrOffLabelStatus==1){

//        this->lOnOrOffLabel->setText(lOnOrOffLabelName+lOnOrOffLabelValue.split("/").at(1));
//        lOnOrOffLabel->setStyleSheet("color:"+Config::colorLevel.split("|").at(1));

//    }else{
//        this->lOnOrOffLabel->setText(lOnOrOffLabelName+lOnOrOffLabelValue.split("/").at(0));
//        lOnOrOffLabel->setStyleSheet("color:"+Config::colorLevel.split("|").at(0));
//    }

//    if(this->lWorkOrBreakLabelStatus==1){
//        lWorkOrBreakLabel->setText(lWorkOrBreakLabelName+lWorkOrBreakLabelValue.split("/").at(1));
//        lWorkOrBreakLabel->setStyleSheet("color:"+Config::colorLevel.split("|").at(1));
//    }else{

//        lWorkOrBreakLabel->setText(lWorkOrBreakLabelName+lWorkOrBreakLabelValue.split("/").at(0));
//        lWorkOrBreakLabel->setStyleSheet("color:"+Config::colorLevel.split("|").at(0));
//    }

//    if(this->lWaringLabelStatus==1){

//        lWaringLabel->setStyleSheet("color:"+Config::colorLevel.split("|").at(2));
//        lWaringLabel->setText(lWaringLabelName+lWaringLabelValue.split("/").at(1));

//    }else if(this->lWaringLabelStatus==2){
//        lWaringLabel->setStyleSheet("color:"+Config::colorLevel.split("|").at(3));
//        lWaringLabel->setText(lWaringLabelName+lWaringLabelValue.split("/").at(2));

//    }else{
//        lWaringLabel->setStyleSheet("color:"+Config::colorLevel.split("|").at(0));
//        lWaringLabel->setText(lWaringLabelName+lWaringLabelValue.split("/").at(0));
//    }

//    int waringLvel=lWaringLabelStatus>0?lWaringLabelStatus+1:((lWorkOrBreakLabelStatus>0||lOnOrOffLabelStatus>0)?1:0);


//    switch(waringLvel){
//    case 1:
//        this->lLightLabel->setPixmap(QPixmap(QString::fromUtf8(":/yellow.png")));
//        break;
//    case 2:
//        this->lLightLabel->setPixmap(QPixmap(QString::fromUtf8(":/orange.png")));
//        break;
//    case 3:
//        this->lLightLabel->setPixmap(QPixmap(QString::fromUtf8(":/red.png")));
//        break;
//    default:
//        this->lLightLabel->setPixmap(QPixmap(QString::fromUtf8(":/green.png")));
//        break;
//    }


//}
