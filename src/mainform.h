#ifndef MAINFORM_H
#define MAINFORM_H

#include <QSystemTrayIcon>
#include <QWidget>
#include <QList>

namespace Ui {
class MainForm;
}

class QMenu;
class QAction;
class QPoint;
class QCloseEvent;
class QMouseEvent;
class EquipmentWidget;
class LogViewDialog;
class QTimer;

class MainForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit MainForm(QWidget *parent = 0);
    ~MainForm();

protected:
     bool eventFilter(QObject *obj, QEvent *ev); //filter events, in this moment,we just attention this event of ui's label
     //void mousePressEvent(QMouseEvent *event);        //define a mouse peress event
     //void mouseMoveEvent(QMouseEvent *event);         // define a mouse move event
     void closeEvent(QCloseEvent *event);
     //bool winEvent(MSG *message, long *result);

private slots:
     void doSetting(); //click to setting the syatem
     void backShowStyle(QSystemTrayIcon::ActivationReason reason); //click trayIcon to show or hidden the mainform
     void logView();
     void on_pushButton_clicked();
     void quit();
     void playSound();

     void on_pushButton_2_clicked();

private:
    Ui::MainForm *ui;
    QList<EquipmentWidget*> equipmentsList;
    QPoint dragPosition;

    QMenu *contentMenu;
    QAction*exitAction;
    QAction*settingAction;

    void initEventerFilter(); // init label event listener

    void initLabels();

    //crete content menu
    void creatContentMenu();
    void createActions();

    //create trayIcon
    void createTrayIcon();
    QSystemTrayIcon*trayIcon;
    QMenu *trayIconMenu;
    QAction*maximizeAction;
    QAction*minimizeAction;
    QAction*norimizeAction;
    QAction*logViewAction;

    //crate lin status pic
    void createLinkStatusPic();

    void createEquipments();


    //label click events
    void showContentMenu(); //show contentmanu

    LogViewDialog *logview;
    void showLogView();

    void doViewLog(); // click to view the system logs
    void doStopAlarm(int id); // close the alarm according to the id
    void doRester();  //


   // QTimer *playTimer;
    void chageMenuLabelBack(bool top);
    QTimer *playTimer;
   // bool isPlay;

};

#endif // MAINFORM_H
