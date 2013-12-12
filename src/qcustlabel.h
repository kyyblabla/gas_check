#ifndef QCUSTLABEL_H
#define QCUSTLABEL_H

#include <QLabel>
class QPaintEvent;

class QCustLabel : public QLabel
{
    Q_OBJECT
public:
    explicit QCustLabel(QWidget *parent = 0);
    void setDesInfo(QString desInfo);

    enum LabelType{
        MianDevice,
        SubI,
        SubII,
        No
    };

    void setLabelType(LabelType type);
    
signals:
    
public slots:


protected:
    void paintEvent(QPaintEvent *event);

private:
     QString  desInfo;
     LabelType labelType;
};

#endif // QCUSTLABEL_H
