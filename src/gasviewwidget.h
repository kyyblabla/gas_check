#ifndef GASVIEWWIDGET_H
#define GASVIEWWIDGET_H

#include <QWidget>

class QwtDial;
class QPalette;
class SpeedoMeter;
class AttitudeIndicator;

namespace Ui {
class GasViewWidget;
}

class GasViewWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit GasViewWidget(QWidget *parent = 0);
    ~GasViewWidget();

protected:
    

public slots:
    void setGanNd(double nd);

private:
    Ui::GasViewWidget *ui;

    QPalette colorTheme( const QColor & ) const;
    QwtDial *createDial();
    SpeedoMeter *d_speedo;
    AttitudeIndicator *d_ai;

};

#endif // GASVIEWWIDGET_H
