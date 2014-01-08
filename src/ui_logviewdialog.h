/********************************************************************************
** Form generated from reading UI file 'logviewdialog.ui'
**
** Created: Thu Jan 9 01:44:11 2014
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGVIEWDIALOG_H
#define UI_LOGVIEWDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSplitter>
#include <QtGui/QTableView>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LogViewDialog
{
public:
    QHBoxLayout *horizontalLayout_3;
    QSplitter *splitter;
    QTreeView *treeView;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBox;
    QComboBox *comboBox;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QTableView *tableView;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *LogViewDialog)
    {
        if (LogViewDialog->objectName().isEmpty())
            LogViewDialog->setObjectName(QString::fromUtf8("LogViewDialog"));
        LogViewDialog->resize(640, 480);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icofire.ico"), QSize(), QIcon::Normal, QIcon::Off);
        LogViewDialog->setWindowIcon(icon);
        horizontalLayout_3 = new QHBoxLayout(LogViewDialog);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        splitter = new QSplitter(LogViewDialog);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setCursor(QCursor(Qt::ArrowCursor));
        splitter->setFrameShape(QFrame::NoFrame);
        splitter->setFrameShadow(QFrame::Plain);
        splitter->setLineWidth(1);
        splitter->setOrientation(Qt::Horizontal);
        splitter->setOpaqueResize(true);
        splitter->setHandleWidth(10);
        splitter->setChildrenCollapsible(true);
        treeView = new QTreeView(splitter);
        treeView->setObjectName(QString::fromUtf8("treeView"));
        treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        splitter->addWidget(treeView);
        treeView->header()->setVisible(false);
        widget_4 = new QWidget(splitter);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setStyleSheet(QString::fromUtf8("QWidget#widget_4{\n"
"  \n"
"}"));
        verticalLayout = new QVBoxLayout(widget_4);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new QWidget(widget_4);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setStyleSheet(QString::fromUtf8("QWidget#widget{\n"
"  \n"
"}"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 12);
        checkBox = new QCheckBox(widget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        horizontalLayout->addWidget(checkBox);

        comboBox = new QComboBox(widget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout->addWidget(comboBox);

        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addWidget(widget);

        widget_2 = new QWidget(widget_4);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        tableView = new QTableView(widget_2);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setDragEnabled(true);
        tableView->setShowGrid(true);
        tableView->setGridStyle(Qt::SolidLine);
        tableView->setSortingEnabled(true);
        tableView->horizontalHeader()->setCascadingSectionResizes(false);

        horizontalLayout_2->addWidget(tableView);


        verticalLayout->addWidget(widget_2);

        widget_3 = new QWidget(widget_4);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        horizontalLayout_4 = new QHBoxLayout(widget_3);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 9, 0, 0);
        pushButton_3 = new QPushButton(widget_3);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        horizontalLayout_4->addWidget(pushButton_3);

        pushButton_2 = new QPushButton(widget_3);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout_4->addWidget(pushButton_2);

        horizontalSpacer = new QSpacerItem(174, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);


        verticalLayout->addWidget(widget_3);

        splitter->addWidget(widget_4);

        horizontalLayout_3->addWidget(splitter);


        retranslateUi(LogViewDialog);

        QMetaObject::connectSlotsByName(LogViewDialog);
    } // setupUi

    void retranslateUi(QDialog *LogViewDialog)
    {
        LogViewDialog->setWindowTitle(QApplication::translate("LogViewDialog", "Log view", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("LogViewDialog", "all", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("LogViewDialog", "All", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("LogViewDialog", "Red", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("LogViewDialog", "Yellow", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("LogViewDialog", "Orange", 0, QApplication::UnicodeUTF8)
        );
        pushButton->setText(QApplication::translate("LogViewDialog", "Serach", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("LogViewDialog", "Dump", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("LogViewDialog", "Del", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class LogViewDialog: public Ui_LogViewDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGVIEWDIALOG_H
