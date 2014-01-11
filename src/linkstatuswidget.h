#ifndef LINKSTATUSWIDGET_H
#define LINKSTATUSWIDGET_H

#include <QWidget>




namespace Ui {
class LinkStatusWidget;
}

class QTimer;

class LinkStatusWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LinkStatusWidget(QWidget *parent = 0);
    ~LinkStatusWidget();
    void isConnection(bool isConn);

protected:
    void  paintEvent(QPaintEvent *event);
    void  showEvent(QShowEvent* event);


private slots:
    void updateData();

private:
    Ui::LinkStatusWidget *ui;
    int timerIDMain;
    bool isConn;

    QTimer*paintTimer;

    int countMain;
    int countSub;

    void init();
    void initLines();

    int  getLineLength(int index, int xtpe);

    int left_left;
    int left_top;
    int left_space;
    int left_width;
    int left_height;


    int right_right;
    int right_top;
    int right_space;
    int right_width;
    int right_height;

    int line_width_main;
    int line_width_sub;

    bool isBroken_1;  //honeywell is broken
    bool isBroken_2;  //selaveII is  broken

    QVector<QLine> lines;



};

#endif // LINKSTATUSWIDGET_H
