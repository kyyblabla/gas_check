#ifndef DIALPAN_H
#define DIALPAN_H

#include <QLabel>
#include <QWidget>
#include <QPaintEvent>

class dialpan : public QLabel
{
    Q_OBJECT
public:
    explicit dialpan(QWidget *parent = 0);
    ~dialpan();
    void setRateValue(double ratevalue);
    double getRateValue();
    void setValueRange(int minValue,int maxValue);

signals:

private:
    /*ratevalue为表盘的rate值*/
    double ratevalue;
    int maxValue;
    int minValue;

protected:
    void paintEvent(QPaintEvent *);

public slots:
};

#endif // DIALPAN_H
