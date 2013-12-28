#ifndef QCUSTLABEL_H
#define QCUSTLABEL_H


#include <QLabel>


class QPaintEvent;
class QTimer;

class QCustLabel : public QLabel
{
    Q_OBJECT
public:
    explicit QCustLabel(QWidget *parent = 0);
    void setDesInfo(QString desInfo);
    ~QCustLabel();

    enum LabelType{
        MainDevice,
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
     QTimer*timer;
     int timeCount;
};

#endif // QCUSTLABEL_H
