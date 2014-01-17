#ifndef LOGVIEWDIALOG_H
#define LOGVIEWDIALOG_H

#include <QDialog>

#include "sqlite.h"

namespace Ui {
class LogViewDialog;
}

class QStandardItemModel;

class LogViewDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit LogViewDialog(QWidget *parent = 0);
    ~LogViewDialog();
    
private slots:
    void on_pushButton_4_clicked();
    void doShowLog();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

private:
    Ui::LogViewDialog *ui;
    QStandardItemModel *tableModel;
    void initTableView();
    void initTreeView();
    void createConnection();
    QList<Log> *logList;


    void showLogs();

};

#endif // LOGVIEWDIALOG_H
