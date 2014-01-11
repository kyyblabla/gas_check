#ifndef MAINFORM_H
#define MAINFORM_H

#include "modbusrequestthread.h"
#include "myserialport.h"

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
class GasViewForm;
class SettingDialog;



class MainForm : public QWidget
{
    Q_OBJECT
public:
    explicit MainForm(QWidget *parent = 0);
    ~MainForm();
    void doReceiveData(QString data);

    enum MasterModel{
        Master,
        Sub,
        SubToMaster,
        MasterToSub
    };

protected:
    bool eventFilter(QObject *obj, QEvent *ev); //filter events, in this moment,we just attention this event of ui's label
    //void mousePressEvent(QMouseEvent *event);        //define a mouse peress event
    //void mouseMoveEvent(QMouseEvent *event);         // define a mouse move event
    void closeEvent(QCloseEvent *event);
    //bool winEvent(MSG *message, long *result);

private slots:

    void changeStackIndex(int index);

    void doSetting(); //click to setting the syatem
    void backShowStyle(QSystemTrayIcon::ActivationReason reason); //click trayIcon to show or hidden the mainform

    void quit();
    void playSound();

    void doLogView();
    void transcationIsDone(Transcation *trans);
    void createTranstration();

    //void  gasViewSelectIndexChange(int);

    //void gasViewValueChange(int);

    void pollForDataOnBus();


    void modelChange(MainForm::MasterModel modelType);
    //void on_pushButton_clicked();

signals:
    void gasValueChange(int index);

private:
    Ui::MainForm *ui;
    QList<EquipmentWidget*> equipmentsList;
    QPoint dragPosition;

    //QMenu *contentMenu;
    QAction*exitAction;
    QAction*settingAction;

    SettingDialog*settingDialog;

    void initTimerAndThread();

    void initEventerFilter(); // init label event listener

    void initLabels();

    //crete content menu
    void creatContentMenu();
    void createActions();

    //create trayIcon
    void createTrayIcon();
    QSystemTrayIcon*trayIcon;
    QMenu *trayIconMenu;
    QAction*logViewAction;

    //crate lin status pic
    //void createLinkStatusPic();
    void createEquipments();


    //label click events
    // void showContentMenu(); //show contentmanu

    LogViewDialog *logview;
    void showLogView();

    void doViewLog(); // click to view the system logs
    void doStopAlarm(int id); // close the alarm according to the id
    void doRester();  //


    QTimer *playTimer;
    QTimer *transcationCreate;
    bool isPlay;

    QTimer*pollTimer;

    ModbusRequestThread*reqThread;
    // MySerialPort*mySerialPort;


    bool changeEquipmentStatus(int index, int labelIndex, int data);

    int transitionIndex;

    //void addLogInfo(QString info, int index, int level);

    //GasViewForm*gasViewForm;
    void addLogInfo(int equipmentIndex,int labelIndex,int statu);


    MasterModel masterModel;



};

#endif // MAINFORM_H
