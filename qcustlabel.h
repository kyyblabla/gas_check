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
    
signals:
    
public slots:


protected:
    void paintEvent(QPaintEvent *event);

private:
     QString  desInfo;

    
};

#endif // QCUSTLABEL_H
