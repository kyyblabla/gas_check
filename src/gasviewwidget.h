#ifndef GASVIEWWIDGET_H
#define GASVIEWWIDGET_H

#include <QWidget>

class QPaintEvent;
class QPainter;

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
    void paintEvent(QPaintEvent *event);
    
private:
    Ui::GasViewWidget *ui;

    int x;
    int y;
    int picWidth;
    int pixHeight;
    int startAngle;
    int endAngle;

    void initPainter();

};

#endif // GASVIEWWIDGET_H
