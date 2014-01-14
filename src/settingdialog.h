#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <mainform.h>
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
    void changeIsSlave(MainForm::MasterModel model);

protected:
    void showEvent(QShowEvent *event);

private slots:
    void listItemSelectChange();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void tableValueChange(const QModelIndex &topLeft, const QModelIndex &bottomRight);

    void on_pushButton_5_clicked();

    void on_checkBox_clicked(bool checked);

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void serilaSelectIndexChange(int);

    void on_pushButton_6_clicked();

    void setSureButtonEnable(int value);


private:
    Ui::SettingDialog *ui;
   // QStandardItemModel *listModel;
    void initTable();
    void  createConnects();
    void removeConnection();

    void setBlockEnable(bool enable);
};

#endif // SETTINGDIALOG_H
