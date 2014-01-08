/********************************************************************************
** Form generated from reading UI file 'myserialsettingswidget.ui'
**
** Created: Thu Jan 9 01:44:12 2014
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYSERIALSETTINGSWIDGET_H
#define UI_MYSERIALSETTINGSWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MySerialSettingsWidget
{
public:
    QGridLayout *gridLayout;
    QLabel *label_4;
    QLabel *label_2;
    QComboBox *baud;
    QLabel *label_5;
    QComboBox *stopBits;
    QLabel *label_3;
    QComboBox *dataBits;
    QLabel *label_6;
    QComboBox *parity;
    QComboBox *serialPort;

    void setupUi(QWidget *MySerialSettingsWidget)
    {
        if (MySerialSettingsWidget->objectName().isEmpty())
            MySerialSettingsWidget->setObjectName(QString::fromUtf8("MySerialSettingsWidget"));
        MySerialSettingsWidget->resize(453, 102);
        gridLayout = new QGridLayout(MySerialSettingsWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_4 = new QLabel(MySerialSettingsWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 0, 0, 1, 1);

        label_2 = new QLabel(MySerialSettingsWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        baud = new QComboBox(MySerialSettingsWidget);
        baud->setObjectName(QString::fromUtf8("baud"));

        gridLayout->addWidget(baud, 1, 1, 1, 1);

        label_5 = new QLabel(MySerialSettingsWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 1, 2, 1, 1);

        stopBits = new QComboBox(MySerialSettingsWidget);
        stopBits->setObjectName(QString::fromUtf8("stopBits"));

        gridLayout->addWidget(stopBits, 1, 3, 1, 1);

        label_3 = new QLabel(MySerialSettingsWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        dataBits = new QComboBox(MySerialSettingsWidget);
        dataBits->setObjectName(QString::fromUtf8("dataBits"));

        gridLayout->addWidget(dataBits, 2, 1, 1, 1);

        label_6 = new QLabel(MySerialSettingsWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 2, 2, 1, 1);

        parity = new QComboBox(MySerialSettingsWidget);
        parity->setObjectName(QString::fromUtf8("parity"));

        gridLayout->addWidget(parity, 2, 3, 1, 1);

        serialPort = new QComboBox(MySerialSettingsWidget);
        serialPort->setObjectName(QString::fromUtf8("serialPort"));

        gridLayout->addWidget(serialPort, 0, 1, 1, 3);


        retranslateUi(MySerialSettingsWidget);

        baud->setCurrentIndex(2);
        dataBits->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MySerialSettingsWidget);
    } // setupUi

    void retranslateUi(QWidget *MySerialSettingsWidget)
    {
        MySerialSettingsWidget->setWindowTitle(QApplication::translate("MySerialSettingsWidget", "Form", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MySerialSettingsWidget", "Serial port", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MySerialSettingsWidget", "Baud", 0, QApplication::UnicodeUTF8));
        baud->clear();
        baud->insertItems(0, QStringList()
         << QApplication::translate("MySerialSettingsWidget", "1200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MySerialSettingsWidget", "4800", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MySerialSettingsWidget", "9600", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MySerialSettingsWidget", "19200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MySerialSettingsWidget", "38400", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MySerialSettingsWidget", "57600", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MySerialSettingsWidget", "115200", 0, QApplication::UnicodeUTF8)
        );
        label_5->setText(QApplication::translate("MySerialSettingsWidget", "Stop bits", 0, QApplication::UnicodeUTF8));
        stopBits->clear();
        stopBits->insertItems(0, QStringList()
         << QApplication::translate("MySerialSettingsWidget", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MySerialSettingsWidget", "1.5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MySerialSettingsWidget", "2", 0, QApplication::UnicodeUTF8)
        );
        label_3->setText(QApplication::translate("MySerialSettingsWidget", "Data bits", 0, QApplication::UnicodeUTF8));
        dataBits->clear();
        dataBits->insertItems(0, QStringList()
         << QApplication::translate("MySerialSettingsWidget", "7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MySerialSettingsWidget", "8", 0, QApplication::UnicodeUTF8)
        );
        label_6->setText(QApplication::translate("MySerialSettingsWidget", "Parity", 0, QApplication::UnicodeUTF8));
        parity->clear();
        parity->insertItems(0, QStringList()
         << QApplication::translate("MySerialSettingsWidget", "none", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MySerialSettingsWidget", "odd", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MySerialSettingsWidget", "even", 0, QApplication::UnicodeUTF8)
        );
    } // retranslateUi

};

namespace Ui {
    class MySerialSettingsWidget: public Ui_MySerialSettingsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYSERIALSETTINGSWIDGET_H
