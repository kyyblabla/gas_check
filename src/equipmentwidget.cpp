#include "equipmentwidget.h"
#include "config.h"

#include <QStringList>
#include <QVBoxLayout>
#include <QDebug>


EquipmentWidget::EquipmentWidget(QWidget *parent) :
    QWidget(parent)
{
    initWidget();
    setLabels();
}


void EquipmentWidget::initWidget(){

    QVBoxLayout *layout=new QVBoxLayout;
    this->setLayout(layout);
    layout->setMargin(0);

    QStringList list= Config::EQUIPMENT_LABEL.split("#");
    lNongDuLabelName=list.at(0).split("|").at(0);
    lNongDuLabelValue=list.at(0).split("|").at(1);
    this->lNongDuLabelStatus=0;


    lOnOrOffLabelName=list.at(1).split("|").at(0);
    lOnOrOffLabelValue=list.at(1).split("|").at(1);
    this->lOnOrOffLabelStatus=0;


    lWorkOrBreakLabelName=list.at(2).split("|").at(0);
    lWorkOrBreakLabelValue=list.at(2).split("|").at(1);
    this->lWorkOrBreakLabelStatus=0;


    lWaringLabelName=list.at(3).split("|").at(0);
    lWaringLabelValue=list.at(3).split("|").at(1);
    this->lWaringLabelStatus=0;



}

void EquipmentWidget::setLabels(){

    this->lLightLabel=new QLabel;

    lLightLabel->setAlignment(Qt::AlignCenter);
    lLightLabel->setPixmap(QPixmap(QString::fromUtf8(":/green.png")));

    this->lNongDuLabel=new QLabel;
    lNongDuLabel->setStyleSheet("color:"+Config::colorLevel.split("|").at(0));
    lNongDuLabel->setText(lNongDuLabelName+"0"+lNongDuLabelValue);

    this->lOnOrOffLabel=new QLabel;
    lOnOrOffLabel->setStyleSheet("color:"+Config::colorLevel.split("|").at(0));
    lOnOrOffLabel->setText(lOnOrOffLabelName+lOnOrOffLabelValue.split("/").at(0));

    this->lWorkOrBreakLabel=new QLabel;
    lWorkOrBreakLabel->setStyleSheet("color:"+Config::colorLevel.split("|").at(0));
    lWorkOrBreakLabel->setText(lWorkOrBreakLabelName+lWorkOrBreakLabelValue.split("/").at(0));

    this->lWaringLabel=new QLabel;
    lWaringLabel->setStyleSheet("color:"+Config::colorLevel.split("|").at(0));
    lWaringLabel->setText(lWaringLabelName+lWaringLabelValue.split("/").at(0));

    this->layout()->addWidget(lLightLabel);
    this->layout()->addWidget(lNongDuLabel);
    this->layout()->addWidget(lOnOrOffLabel);
    this->layout()->addWidget(lWorkOrBreakLabel);
    this->layout()->addWidget(lWaringLabel);

}


void EquipmentWidget::updateLabelInfo(int labelName, int status, QString info){

    switch (labelName) {
    case 0:
        switch(status){
        case 1:
            this->lLightLabel->setPixmap(QPixmap(QString::fromUtf8(":/yellow.png")));
            break;
        case 2:
            this->lLightLabel->setPixmap(QPixmap(QString::fromUtf8(":/orange.png")));
            break;
        case 3:
            this->lLightLabel->setPixmap(QPixmap(QString::fromUtf8(":/red.png")));
            break;
        default:
            this->lLightLabel->setPixmap(QPixmap(QString::fromUtf8(":/green.png")));
            break;
        }
        break;
    case  1:
        this->lNongDuLabel->setText(lNongDuLabelName+info+lNongDuLabelValue);
        lNongDuLabel->setStyleSheet("color:"+Config::colorLevel.split("|").at(0));
        break;
    case  2:

        if(status==1){

            this->lOnOrOffLabel->setText(lOnOrOffLabelName+lOnOrOffLabelValue.split("/").at(1));
            lOnOrOffLabel->setStyleSheet("color:"+Config::colorLevel.split("|").at(1));

        }else{

            this->lOnOrOffLabel->setText(lOnOrOffLabelName+lOnOrOffLabelValue.split("/").at(0));
            lOnOrOffLabel->setStyleSheet("color:"+Config::colorLevel.split("|").at(0));
        }

        break;
    case  3:
        if(status==1){
            lWorkOrBreakLabel->setText(lWorkOrBreakLabelName+lWorkOrBreakLabelValue.split("/").at(1));
            lWorkOrBreakLabel->setStyleSheet("color:"+Config::colorLevel.split("|").at(1));
        }else{

            lWorkOrBreakLabel->setText(lWorkOrBreakLabelName+lWorkOrBreakLabelValue.split("/").at(0));
            lWorkOrBreakLabel->setStyleSheet("color:"+Config::colorLevel.split("|").at(0));
        }
        break;
    case  4:
        if(status==1){

            lWaringLabel->setStyleSheet("color:"+Config::colorLevel.split("|").at(2));
            lWaringLabel->setText(lWaringLabelName+lWaringLabelValue.split("/").at(1));

        }else if(status==2){
            lWaringLabel->setStyleSheet("color:"+Config::colorLevel.split("|").at(3));
            lWaringLabel->setText(lWaringLabelName+lWaringLabelValue.split("/").at(2));

        }else{
            lWaringLabel->setStyleSheet("color:"+Config::colorLevel.split("|").at(0));
            lWaringLabel->setText(lWaringLabelName+lWaringLabelValue.split("/").at(0));
        }
        break;
    default:
        break;
    }

}


bool EquipmentWidget::updateLabelVlaue(int labelIndex, int status){

    bool change=false;
    switch (labelIndex) {
    case  1:
        this->lNongDuLabelStatus=status;
        break;
    case  2:
        if(this->lOnOrOffLabelStatus!=status){
            change=true;
            this->lOnOrOffLabelStatus=status;
        }

        break;
    case  3:
        if( this->lWorkOrBreakLabelStatus!=status){
            change=true;
            this->lWorkOrBreakLabelStatus=status;
        }

        break;
    case  4:

        qDebug()<<"lWaringLabelStatus:"<<lWaringLabelStatus<<endl;
        qDebug()<<"status:"<<status<<endl;
        if(this->lWaringLabelStatus!=status){
            change=true;
            this->lWaringLabelStatus=status;
        }
        break;
    default:
        break;
    }

    updateInfo();

    return change;

}


void EquipmentWidget::updateInfo(){



    this->lNongDuLabel->setText(lNongDuLabelName+QString::number(this->lNongDuLabelStatus)+lNongDuLabelValue);
    lNongDuLabel->setStyleSheet("color:"+Config::colorLevel.split("|").at(0));

    if(this->lOnOrOffLabelStatus==1){

        this->lOnOrOffLabel->setText(lOnOrOffLabelName+lOnOrOffLabelValue.split("/").at(1));
        lOnOrOffLabel->setStyleSheet("color:"+Config::colorLevel.split("|").at(1));

    }else{
        this->lOnOrOffLabel->setText(lOnOrOffLabelName+lOnOrOffLabelValue.split("/").at(0));
        lOnOrOffLabel->setStyleSheet("color:"+Config::colorLevel.split("|").at(0));
    }

    if(this->lWorkOrBreakLabelStatus==1){
        lWorkOrBreakLabel->setText(lWorkOrBreakLabelName+lWorkOrBreakLabelValue.split("/").at(1));
        lWorkOrBreakLabel->setStyleSheet("color:"+Config::colorLevel.split("|").at(1));
    }else{

        lWorkOrBreakLabel->setText(lWorkOrBreakLabelName+lWorkOrBreakLabelValue.split("/").at(0));
        lWorkOrBreakLabel->setStyleSheet("color:"+Config::colorLevel.split("|").at(0));
    }

    if(this->lWaringLabelStatus==1){

        lWaringLabel->setStyleSheet("color:"+Config::colorLevel.split("|").at(2));
        lWaringLabel->setText(lWaringLabelName+lWaringLabelValue.split("/").at(1));

    }else if(this->lWaringLabelStatus==2){
        lWaringLabel->setStyleSheet("color:"+Config::colorLevel.split("|").at(3));
        lWaringLabel->setText(lWaringLabelName+lWaringLabelValue.split("/").at(2));

    }else{
        lWaringLabel->setStyleSheet("color:"+Config::colorLevel.split("|").at(0));
        lWaringLabel->setText(lWaringLabelName+lWaringLabelValue.split("/").at(0));
    }

    int waringLvel=lWaringLabelStatus>0?lWaringLabelStatus+1:((lWorkOrBreakLabelStatus>0||lOnOrOffLabelStatus>0)?1:0);


    switch(waringLvel){
    case 1:
        this->lLightLabel->setPixmap(QPixmap(QString::fromUtf8(":/yellow.png")));
        break;
    case 2:
        this->lLightLabel->setPixmap(QPixmap(QString::fromUtf8(":/orange.png")));
        break;
    case 3:
        this->lLightLabel->setPixmap(QPixmap(QString::fromUtf8(":/red.png")));
        break;
    default:
        this->lLightLabel->setPixmap(QPixmap(QString::fromUtf8(":/green.png")));
        break;
    }


}
