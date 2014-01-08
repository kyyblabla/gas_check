/********************************************************************************
** Form generated from reading UI file 'settingdialog.ui'
**
** Created: Thu Jan 9 01:44:11 2014
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGDIALOG_H
#define UI_SETTINGDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "myserialsettingswidget.h"
#include "serialsettingswidget.h"

QT_BEGIN_NAMESPACE

class Ui_SettingDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QTableView *tableView;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QCheckBox *checkBox;
    QLabel *label;
    QSpinBox *spinBox;
    QSpacerItem *verticalSpacer_2;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_5;
    QPushButton *pushButton_3;
    QSpacerItem *verticalSpacer;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout_3;
    QWidget *widget;
    QVBoxLayout *verticalLayout_8;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_9;
    SerialSettingsWidget *widget_6;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_10;
    MySerialSettingsWidget *widget_2;
    QWidget *widget_5;
    QVBoxLayout *verticalLayout_7;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QDialog *SettingDialog)
    {
        if (SettingDialog->objectName().isEmpty())
            SettingDialog->setObjectName(QString::fromUtf8("SettingDialog"));
        SettingDialog->resize(632, 455);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icofire.ico"), QSize(), QIcon::Normal, QIcon::Off);
        SettingDialog->setWindowIcon(icon);
        horizontalLayout = new QHBoxLayout(SettingDialog);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tabWidget = new QTabWidget(SettingDialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        horizontalLayout_2 = new QHBoxLayout(tab);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        widget_4 = new QWidget(tab);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        verticalLayout_4 = new QVBoxLayout(widget_4);
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        groupBox = new QGroupBox(widget_4);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tableView = new QTableView(groupBox);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        verticalLayout_2->addWidget(tableView);


        verticalLayout_4->addWidget(groupBox);

        groupBox_2 = new QGroupBox(widget_4);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        checkBox = new QCheckBox(groupBox_2);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        gridLayout->addWidget(checkBox, 0, 0, 1, 1);

        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        spinBox = new QSpinBox(groupBox_2);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setMaximum(255);

        gridLayout->addWidget(spinBox, 1, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 2, 2, 1, 1);


        verticalLayout_4->addWidget(groupBox_2);


        horizontalLayout_2->addWidget(widget_4);

        widget_3 = new QWidget(tab);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        verticalLayout = new QVBoxLayout(widget_3);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pushButton = new QPushButton(widget_3);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setEnabled(false);

        verticalLayout->addWidget(pushButton);

        pushButton_5 = new QPushButton(widget_3);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setEnabled(false);

        verticalLayout->addWidget(pushButton_5);

        pushButton_3 = new QPushButton(widget_3);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        verticalLayout->addWidget(pushButton_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_2->addWidget(widget_3);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        horizontalLayout_3 = new QHBoxLayout(tab_2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        widget = new QWidget(tab_2);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayout_8 = new QVBoxLayout(widget);
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        groupBox_4 = new QGroupBox(widget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        verticalLayout_9 = new QVBoxLayout(groupBox_4);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        widget_6 = new SerialSettingsWidget(groupBox_4);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));

        verticalLayout_9->addWidget(widget_6);


        verticalLayout_8->addWidget(groupBox_4);

        groupBox_5 = new QGroupBox(widget);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        verticalLayout_10 = new QVBoxLayout(groupBox_5);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        widget_2 = new MySerialSettingsWidget(groupBox_5);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));

        verticalLayout_10->addWidget(widget_2);


        verticalLayout_8->addWidget(groupBox_5);


        horizontalLayout_3->addWidget(widget);

        widget_5 = new QWidget(tab_2);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        verticalLayout_7 = new QVBoxLayout(widget_5);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        pushButton_7 = new QPushButton(widget_5);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setEnabled(false);

        verticalLayout_7->addWidget(pushButton_7);

        pushButton_8 = new QPushButton(widget_5);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setEnabled(false);

        verticalLayout_7->addWidget(pushButton_8);

        pushButton_9 = new QPushButton(widget_5);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));

        verticalLayout_7->addWidget(pushButton_9);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_3);


        horizontalLayout_3->addWidget(widget_5);

        horizontalLayout_3->setStretch(0, 1);
        tabWidget->addTab(tab_2, QString());

        horizontalLayout->addWidget(tabWidget);


        retranslateUi(SettingDialog);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(SettingDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingDialog)
    {
        SettingDialog->setWindowTitle(QApplication::translate("SettingDialog", "System Setting ", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("SettingDialog", "devices list", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("SettingDialog", "Host/Slave Settig", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("SettingDialog", "Is Slave", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SettingDialog", "address", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("SettingDialog", "Sure", 0, QApplication::UnicodeUTF8));
        pushButton_5->setText(QApplication::translate("SettingDialog", "Apply", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("SettingDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("SettingDialog", "Base Setting", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("SettingDialog", "SerialPort Setting", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("SettingDialog", "Slave Equipment Setting", 0, QApplication::UnicodeUTF8));
        pushButton_7->setText(QApplication::translate("SettingDialog", "Sure", 0, QApplication::UnicodeUTF8));
        pushButton_8->setText(QApplication::translate("SettingDialog", "Apply", 0, QApplication::UnicodeUTF8));
        pushButton_9->setText(QApplication::translate("SettingDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("SettingDialog", "Miontor Setting", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SettingDialog: public Ui_SettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGDIALOG_H
