#ifndef LOGVIEWDIALOG_H
#define LOGVIEWDIALOG_H

#include <QDialog>

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

private:
    Ui::LogViewDialog *ui;

    QStandardItemModel *tableModel;
    void initTableView();

    QStandardItemModel *treeModel;
    void initTreeView();



};

#endif // LOGVIEWDIALOG_H
