/********************************************************************************
** Form generated from reading UI file 'gasviewform.ui'
**
** Created: Thu Jan 9 01:44:12 2014
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GASVIEWFORM_H
#define UI_GASVIEWFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "gasviewwidget.h"

QT_BEGIN_NAMESPACE

class Ui_GasViewForm
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_2;
    GasViewWidget *widget;

    void setupUi(QDialog *GasViewForm)
    {
        if (GasViewForm->objectName().isEmpty())
            GasViewForm->setObjectName(QString::fromUtf8("GasViewForm"));
        GasViewForm->resize(450, 374);
        GasViewForm->setStyleSheet(QString::fromUtf8("*{\n"
"	font:  \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"}"));
        verticalLayout = new QVBoxLayout(GasViewForm);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget_2 = new QWidget(GasViewForm);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setStyleSheet(QString::fromUtf8("*{\n"
" background-color:#393939;\n"
" color:#fff;\n"
" font-size:30px;\n"
"}\n"
"\n"
"#label_3:hover,#label_2:hover{\n"
"  color:#f80;\n"
"}\n"
" "));
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 2, 9, 2);
        label = new QLabel(widget_2);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        label_3 = new QLabel(widget_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_2);

        horizontalLayout->setStretch(0, 1);

        verticalLayout->addWidget(widget_2);

        widget = new GasViewWidget(GasViewForm);
        widget->setObjectName(QString::fromUtf8("widget"));

        verticalLayout->addWidget(widget);

        verticalLayout->setStretch(1, 1);

        retranslateUi(GasViewForm);

        QMetaObject::connectSlotsByName(GasViewForm);
    } // setupUi

    void retranslateUi(QDialog *GasViewForm)
    {
        GasViewForm->setWindowTitle(QApplication::translate("GasViewForm", "Gas View", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("GasViewForm", "No", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("GasViewForm", "<html><head/><body><p><span style=\" font-weight:600;\">&lt; </span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("GasViewForm", "<html><head/><body><p><span style=\" font-weight:600;\">&gt; </span></p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GasViewForm: public Ui_GasViewForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GASVIEWFORM_H
