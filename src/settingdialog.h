#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>

namespace Ui {
class SettingDialog;
}
class QStandardItemModel;
class QModelIndex;
class QStandardItem;

class
        SettingDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SettingDialog(QWidget *parent = 0);
    ~SettingDialog();
signals:
    void changeSerials(int);
private slots:
    
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void tableValueChange(const QModelIndex &topLeft, const QModelIndex &bottomRight);

    void on_pushButton_5_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::SettingDialog *ui;
    QStandardItemModel *tableModel;
    void initTable();
    void  createConnects();

    void  changeTableValue();
};

#endif // SETTINGDIALOG_H
