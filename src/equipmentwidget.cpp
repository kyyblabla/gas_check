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

    if(list.length()<4){
        list=tr("nd:|dp#onOrOff:|on/off#workOrBreak:|work/break#alarm:|no/low/high").split("#");
    }

    lNongDuLabelName=list.at(0).split("|").at(0);
    lNongDuLabelValue=list.at(0).split("|").at(1);


    lOnOrOffLabelName=list.at(1).split("|").at(0);
    lOnOrOffLabelValue=list.at(1).split("|").at(1);


    lWorkOrBreakLabelName=list.at(2).split("|").at(0);
    lWorkOrBreakLabelValue=list.at(2).split("|").at(1);


    lWaringLabelName=list.at(3).split("|").at(0);
    lWaringLabelValue=list.at(3).split("|").at(1);

}

void EquipmentWidget::setLabels(){


    this->lLightLabel=new QLabel;

    lLightLabel->setAlignment(Qt::AlignCenter);
    lLightLabel->setPixmap(QPixmap(QString::fromUtf8(":/green.png")));

    this->lNongDuLabel=new QLabel;
    lNongDuLabel->setStyleSheet("color:green");
    lNongDuLabel->setText(lNongDuLabelName+"0"+lNongDuLabelValue);

    this->lOnOrOffLabel=new QLabel;
    lOnOrOffLabel->setStyleSheet("color:green");
    lOnOrOffLabel->setText(lOnOrOffLabelName+lOnOrOffLabelValue.split("/").at(0));

    this->lWorkOrBreakLabel=new QLabel;
    lWorkOrBreakLabel->setStyleSheet("color:green");
    lWorkOrBreakLabel->setText(lWorkOrBreakLabelName+lWorkOrBreakLabelValue.split("/").at(0));

    this->lWaringLabel=new QLabel;
    lWaringLabel->setStyleSheet("color:green");
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
        case 0:
            this->lLightLabel->setPixmap(QPixmap(QString::fromUtf8(":/green.png")));
            break;
        case 1:
            this->lLightLabel->setPixmap(QPixmap(QString::fromUtf8(":/yellow.png")));
            break;
        case 2:
            this->lLightLabel->setPixmap(QPixmap(QString::fromUtf8(":/red.png")));
            break;
        default:
            break;
        }
        break;
    case  1:
        this->lNongDuLabel->setText(lNongDuLabelName+info+lNongDuLabelValue);
        lNongDuLabel->setStyleSheet("color:green");
        break;
    case  2:
        if(status==1){
            this->lOnOrOffLabel->setText(lOnOrOffLabelName+lOnOrOffLabelValue.split("/").at(1));
            lOnOrOffLabel->setStyleSheet("color:#f40");
        }else{
            this->lOnOrOffLabel->setText(lOnOrOffLabelName+lOnOrOffLabelValue.split("/").at(0));
            lOnOrOffLabel->setStyleSheet("color:green");
        }
        break;
    case  3:
        if(status==1){
            lWorkOrBreakLabel->setText(lWorkOrBreakLabelName+lWorkOrBreakLabelValue.split("/").at(1));
            lWorkOrBreakLabel->setStyleSheet("color:#f80");
        }else{

            lWorkOrBreakLabel->setText(lWorkOrBreakLabelName+lWorkOrBreakLabelValue.split("/").at(0));
            lWorkOrBreakLabel->setStyleSheet("color:green");
        }
        break;
    case  4:
        if(status==1){
            lWaringLabel->setText(lWaringLabelName+lWaringLabelValue.split("/").at(1));
            lWaringLabel->setStyleSheet("color:yellow");


        }else if(status==2){
            lWaringLabel->setStyleSheet("color:red");
            lWaringLabel->setText(lWaringLabelName+lWaringLabelValue.split("/").at(2));

        }else{
            lWaringLabel->setStyleSheet("color:green");
            lWaringLabel->setText(lWaringLabelName+lWaringLabelValue.split("/").at(0));
        }
        break;
    default:
        break;
    }

}
