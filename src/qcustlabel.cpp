#include "qcustlabel.h"

#include <QPaintEvent>
#include <QLabel>
#include <QPainter>

QCustLabel::QCustLabel(QWidget *parent) :
    QLabel(parent),labelType(QCustLabel::No)
{
    this->setAlignment(Qt::AlignCenter);

}

void QCustLabel::setDesInfo(QString desInfo){

    this->desInfo=desInfo;

}

void QCustLabel::setLabelType(LabelType type){

    this->labelType=type;
}

void QCustLabel::paintEvent(QPaintEvent *event){

    QLabel::paintEvent(event) ;

    QPainter painter(this);
    painter.setPen(Qt::white);

    //QLabel::fontMetrics().width(QString s)
    //QLabel::fontMetrics().height()

    QString info=this->desInfo;

    int l=this->width()/2-(this->fontMetrics().width(info)/2);
    int t=this->height()/2+(this->fontMetrics().height()/2);

    painter.drawText(QPoint(l,t),info);


}

