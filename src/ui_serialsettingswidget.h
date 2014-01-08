/********************************************************************************
** Form generated from reading UI file 'serialsettingswidget.ui'
**
** Created: Thu Jan 9 01:44:11 2014
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERIALSETTINGSWIDGET_H
#define UI_SERIALSETTINGSWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SerialSettingsWidget
{
public:
    QGridLayout *gridLayout;
    QComboBox *parity;
    QLabel *label_5;
    QComboBox *stopBits;
    QLabel *label_4;
    QComboBox *baud;
    QComboBox *dataBits;
    QCheckBox *checkBox;
    QComboBox *serialPort;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label;

    void setupUi(QWidget *SerialSettingsWidget)
    {
        if (SerialSettingsWidget->objectName().isEmpty())
            SerialSettingsWidget->setObjectName(QString::fromUtf8("SerialSettingsWidget"));
        SerialSettingsWidget->resize(447, 124);
        SerialSettingsWidget->setMinimumSize(QSize(0, 124));
        gridLayout = new QGridLayout(SerialSettingsWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        parity = new QComboBox(SerialSettingsWidget);
        parity->setObjectName(QString::fromUtf8("parity"));

        gridLayout->addWidget(parity, 3, 3, 1, 1);

        label_5 = new QLabel(SerialSettingsWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 3, 2, 1, 1);

        stopBits = new QComboBox(SerialSettingsWidget);
        stopBits->setObjectName(QString::fromUtf8("stopBits"));

        gridLayout->addWidget(stopBits, 2, 3, 1, 1);

        label_4 = new QLabel(SerialSettingsWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 2, 2, 1, 1);

        baud = new QComboBox(SerialSettingsWidget);
        baud->setObjectName(QString::fromUtf8("baud"));

        gridLayout->addWidget(baud, 2, 1, 1, 1);

        dataBits = new QComboBox(SerialSettingsWidget);
        dataBits->setObjectName(QString::fromUtf8("dataBits"));

        gridLayout->addWidget(dataBits, 3, 1, 1, 1);

        checkBox = new QCheckBox(SerialSettingsWidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        gridLayout->addWidget(checkBox, 0, 0, 1, 1);

        serialPort = new QComboBox(SerialSettingsWidget);
        serialPort->setObjectName(QString::fromUtf8("serialPort"));

        gridLayout->addWidget(serialPort, 1, 1, 1, 3);

        label_2 = new QLabel(SerialSettingsWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        label_3 = new QLabel(SerialSettingsWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        label = new QLabel(SerialSettingsWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);


        retranslateUi(SerialSettingsWidget);

        baud->setCurrentIndex(2);
        dataBits->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(SerialSettingsWidget);
    } // setupUi

    void retranslateUi(QWidget *SerialSettingsWidget)
    {
        SerialSettingsWidget->setWindowTitle(QApplication::translate("SerialSettingsWidget", "Form", 0, QApplication::UnicodeUTF8));
        parity->clear();
        parity->insertItems(0, QStringList()
         << QApplication::translate("SerialSettingsWidget", "none", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SerialSettingsWidget", "odd", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SerialSettingsWidget", "even", 0, QApplication::UnicodeUTF8)
        );
        label_5->setText(QApplication::translate("SerialSettingsWidget", "Parity", 0, QApplication::UnicodeUTF8));
        stopBits->clear();
        stopBits->insertItems(0, QStringList()
         << QApplication::translate("SerialSettingsWidget", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SerialSettingsWidget", "1.5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SerialSettingsWidget", "2", 0, QApplication::UnicodeUTF8)
        );
        label_4->setText(QApplication::translate("SerialSettingsWidget", "Stop bits", 0, QApplication::UnicodeUTF8));
        baud->clear();
        baud->insertItems(0, QStringList()
         << QApplication::translate("SerialSettingsWidget", "1200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SerialSettingsWidget", "4800", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SerialSettingsWidget", "9600", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SerialSettingsWidget", "19200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SerialSettingsWidget", "38400", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SerialSettingsWidget", "57600", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SerialSettingsWidget", "115200", 0, QApplication::UnicodeUTF8)
        );
        dataBits->clear();
        dataBits->insertItems(0, QStringList()
         << QApplication::translate("SerialSettingsWidget", "7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SerialSettingsWidget", "8", 0, QApplication::UnicodeUTF8)
        );
        checkBox->setText(QApplication::translate("SerialSettingsWidget", "Active", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SerialSettingsWidget", "Baud", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("SerialSettingsWidget", "Data bits", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SerialSettingsWidget", "Serial port", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SerialSettingsWidget: public Ui_SerialSettingsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERIALSETTINGSWIDGET_H
