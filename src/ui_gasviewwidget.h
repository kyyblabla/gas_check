/********************************************************************************
** Form generated from reading UI file 'gasviewwidget.ui'
**
** Created: Thu Jan 9 01:44:12 2014
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GASVIEWWIDGET_H
#define UI_GASVIEWWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GasViewWidget
{
public:

    void setupUi(QWidget *GasViewWidget)
    {
        if (GasViewWidget->objectName().isEmpty())
            GasViewWidget->setObjectName(QString::fromUtf8("GasViewWidget"));
        GasViewWidget->resize(463, 259);
        GasViewWidget->setStyleSheet(QString::fromUtf8(""));

        retranslateUi(GasViewWidget);

        QMetaObject::connectSlotsByName(GasViewWidget);
    } // setupUi

    void retranslateUi(QWidget *GasViewWidget)
    {
        GasViewWidget->setWindowTitle(QApplication::translate("GasViewWidget", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GasViewWidget: public Ui_GasViewWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GASVIEWWIDGET_H
