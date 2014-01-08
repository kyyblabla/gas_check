/********************************************************************************
** Form generated from reading UI file 'mainform.ui'
**
** Created: Thu Jan 9 01:43:52 2014
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINFORM_H
#define UI_MAINFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStackedWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainForm
{
public:
    QHBoxLayout *horizontalLayout_8;
    QWidget *widget_12;
    QVBoxLayout *verticalLayout_6;
    QWidget *widget_7;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QStackedWidget *stackedWidget;
    QWidget *main_view;
    QHBoxLayout *horizontalLayout_9;
    QWidget *widget_con;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_5;
    QWidget *widget_8;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_12;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout;
    QWidget *widget_9;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_13;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *verticalSpacer_2;
    QWidget *float_menu;
    QVBoxLayout *verticalLayout_8;
    QSpacerItem *verticalSpacer;
    QWidget *widget_4;
    QGridLayout *gridLayout_2;
    QLabel *label_9;
    QLabel *label_19;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_10;
    QLabel *label_20;
    QLabel *label_18;
    QWidget *page;
    QVBoxLayout *verticalLayout;
    QWidget *widget_11;
    QHBoxLayout *horizontalLayout_3;
    QTextEdit *textEdit;
    QWidget *widget_2;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_7;
    QWidget *widget_10;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton_4;
    QLabel *label_21;
    QLabel *label_14;
    QLabel *label_15;

    void setupUi(QWidget *MainForm)
    {
        if (MainForm->objectName().isEmpty())
            MainForm->setObjectName(QString::fromUtf8("MainForm"));
        MainForm->resize(640, 480);
        MainForm->setMinimumSize(QSize(640, 480));
        MainForm->setStyleSheet(QString::fromUtf8("QWidget#MainForm{\n"
"	 \n"
"	background-color: rgb(0,0,0) ;\n"
"}\n"
"\n"
"*{\n"
"	font: 9pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"}\n"
""));
        horizontalLayout_8 = new QHBoxLayout(MainForm);
        horizontalLayout_8->setSpacing(0);
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        widget_12 = new QWidget(MainForm);
        widget_12->setObjectName(QString::fromUtf8("widget_12"));
        widget_12->setStyleSheet(QString::fromUtf8("QWidget#widget_12{\n"
"     \n"
"\n"
"}"));
        verticalLayout_6 = new QVBoxLayout(widget_12);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        widget_7 = new QWidget(widget_12);
        widget_7->setObjectName(QString::fromUtf8("widget_7"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_7->sizePolicy().hasHeightForWidth());
        widget_7->setSizePolicy(sizePolicy);
        widget_7->setMinimumSize(QSize(0, 50));
        widget_7->setStyleSheet(QString::fromUtf8("QWidget#widget_7{\n"
"  background-color:#0C80E8;\n"
"  border-bottom:1px solid #ccc;\n"
"  \n"
"}\n"
"\n"
"QWidget#widget_7 *{\n"
"  color:#fff;\n"
"  \n"
"}\n"
"\n"
"QWidget#widget_7 QLabel#label_2:hover{\n"
"	\n"
"	background-color: qlineargradient(spread:pad, x1:0.5, y1:0, x2:0.54, y2:1, stop:0 rgba(255, 0, 0, 148), stop:0.534091 rgba(248, 248, 248, 0));\n"
"}\n"
"\n"
"QWidget#widget_7 QLabel#label_3:hover,\n"
"QWidget#widget_7 QLabel#label_11:hover{\n"
"   \n"
"	 \n"
"	background-color: qlineargradient(spread:pad, x1:0.511, y1:0, x2:0.495, y2:1, stop:0 rgba(0, 0, 0, 146), stop:0.596591 rgba(246, 246, 246, 0));\n"
"	 \n"
"}"));
        horizontalLayout_4 = new QHBoxLayout(widget_7);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(9, 9, 9, 9);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label = new QLabel(widget_7);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(15);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("QLabel#label{\n"
"  font:15pt;\n"
"}"));
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(label);

        horizontalLayout_4->setStretch(0, 1);

        verticalLayout_6->addWidget(widget_7);

        stackedWidget = new QStackedWidget(widget_12);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy1);
        main_view = new QWidget();
        main_view->setObjectName(QString::fromUtf8("main_view"));
        horizontalLayout_9 = new QHBoxLayout(main_view);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        widget_con = new QWidget(main_view);
        widget_con->setObjectName(QString::fromUtf8("widget_con"));
        verticalLayout_2 = new QVBoxLayout(widget_con);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        widget = new QWidget(widget_con);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setStyleSheet(QString::fromUtf8("QWidget#widget QLabel{\n"
"    color:#FFF;\n"
"}\n"
"\n"
"QWidget#widget_9{\n"
"	color:#fff;\n"
"    background-color:none;\n"
"}\n"
"\n"
"QWidget#widget_9 > QLabel{\n"
"	color:#fff;\n"
"     \n"
"}\n"
"\n"
"\n"
"QWidget#widget_5{\n"
"  \n"
"}\n"
"\n"
" \n"
"\n"
""));
        horizontalLayout_5 = new QHBoxLayout(widget);
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        widget_8 = new QWidget(widget);
        widget_8->setObjectName(QString::fromUtf8("widget_8"));
        widget_8->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_4 = new QVBoxLayout(widget_8);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_12 = new QLabel(widget_8);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_4->addWidget(label_12);

        widget_5 = new QWidget(widget_8);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        horizontalLayout = new QHBoxLayout(widget_5);
        horizontalLayout->setSpacing(3);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));

        verticalLayout_4->addWidget(widget_5);

        verticalLayout_4->setStretch(0, 1);
        verticalLayout_4->setStretch(1, 9);

        horizontalLayout_5->addWidget(widget_8);

        widget_9 = new QWidget(widget);
        widget_9->setObjectName(QString::fromUtf8("widget_9"));
        verticalLayout_5 = new QVBoxLayout(widget_9);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label_13 = new QLabel(widget_9);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        verticalLayout_5->addWidget(label_13);

        widget_6 = new QWidget(widget_9);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        widget_6->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_2 = new QHBoxLayout(widget_6);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));

        verticalLayout_5->addWidget(widget_6);

        verticalLayout_5->setStretch(0, 1);
        verticalLayout_5->setStretch(1, 9);

        horizontalLayout_5->addWidget(widget_9);

        horizontalLayout_5->setStretch(0, 3);
        horizontalLayout_5->setStretch(1, 1);

        verticalLayout_2->addWidget(widget);

        verticalSpacer_2 = new QSpacerItem(20, 191, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        horizontalLayout_9->addWidget(widget_con);

        stackedWidget->addWidget(main_view);
        float_menu = new QWidget();
        float_menu->setObjectName(QString::fromUtf8("float_menu"));
        float_menu->setStyleSheet(QString::fromUtf8("QWidget#widget_4{\n"
"	\n"
"	background-color: #F1F3F3;\n"
"\n"
"}"));
        verticalLayout_8 = new QVBoxLayout(float_menu);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalSpacer = new QSpacerItem(20, 252, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_8->addItem(verticalSpacer);

        widget_4 = new QWidget(float_menu);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	color:#fff;\n"
"	background-color:#0C80E8;\n"
"	font-size:13pt;\n"
"	border-radius:3px;\n"
"}"));
        gridLayout_2 = new QGridLayout(widget_4);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setHorizontalSpacing(6);
        label_9 = new QLabel(widget_4);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setEnabled(false);
        label_9->setStyleSheet(QString::fromUtf8(""));
        label_9->setTextFormat(Qt::AutoText);
        label_9->setAlignment(Qt::AlignCenter);
        label_9->setMargin(5);

        gridLayout_2->addWidget(label_9, 0, 0, 1, 1);

        label_19 = new QLabel(widget_4);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setEnabled(true);
        label_19->setStyleSheet(QString::fromUtf8(""));
        label_19->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_19, 0, 1, 1, 1);

        label_16 = new QLabel(widget_4);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setEnabled(false);
        label_16->setStyleSheet(QString::fromUtf8(""));
        label_16->setTextFormat(Qt::AutoText);
        label_16->setAlignment(Qt::AlignCenter);
        label_16->setMargin(5);

        gridLayout_2->addWidget(label_16, 0, 2, 1, 1);

        label_17 = new QLabel(widget_4);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setEnabled(false);
        label_17->setMinimumSize(QSize(0, 0));
        label_17->setStyleSheet(QString::fromUtf8(""));
        label_17->setTextFormat(Qt::AutoText);
        label_17->setAlignment(Qt::AlignCenter);
        label_17->setMargin(5);

        gridLayout_2->addWidget(label_17, 0, 3, 1, 1);

        label_10 = new QLabel(widget_4);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setEnabled(true);
        label_10->setMinimumSize(QSize(0, 0));
        label_10->setStyleSheet(QString::fromUtf8(""));
        label_10->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_10, 1, 0, 1, 1);

        label_20 = new QLabel(widget_4);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setEnabled(false);
        label_20->setStyleSheet(QString::fromUtf8(""));
        label_20->setTextFormat(Qt::AutoText);
        label_20->setAlignment(Qt::AlignCenter);
        label_20->setMargin(5);

        gridLayout_2->addWidget(label_20, 1, 1, 1, 1);

        label_18 = new QLabel(widget_4);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setEnabled(false);
        label_18->setMinimumSize(QSize(0, 0));
        label_18->setStyleSheet(QString::fromUtf8(""));
        label_18->setTextFormat(Qt::AutoText);
        label_18->setAlignment(Qt::AlignCenter);
        label_18->setMargin(5);

        gridLayout_2->addWidget(label_18, 1, 2, 1, 1);


        verticalLayout_8->addWidget(widget_4);

        verticalLayout_8->setStretch(0, 2);
        verticalLayout_8->setStretch(1, 1);
        stackedWidget->addWidget(float_menu);
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        verticalLayout = new QVBoxLayout(page);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget_11 = new QWidget(page);
        widget_11->setObjectName(QString::fromUtf8("widget_11"));
        horizontalLayout_3 = new QHBoxLayout(widget_11);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        textEdit = new QTextEdit(widget_11);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        sizePolicy.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy);
        textEdit->setMinimumSize(QSize(0, 0));
        textEdit->setStyleSheet(QString::fromUtf8("QTextEdit#textEdit{\n"
"	background-color: qlineargradient(spread:pad, x1:0.489, y1:0, x2:0.488, y2:1, stop:0 rgba(242, 242, 242, 255), stop:1 rgba(255, 255, 255, 255));\n"
"	padding:0px;\n"
"}"));

        horizontalLayout_3->addWidget(textEdit);

        widget_2 = new QWidget(widget_11);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setStyleSheet(QString::fromUtf8("QWidget#widget_2 .QLabel:hover{\n"
"   border-color:#ccc; \n"
"   border-width:1px;\n"
"   border-style:solid;\n"
"}"));

        horizontalLayout_3->addWidget(widget_2);


        verticalLayout->addWidget(widget_11);

        widget_3 = new QWidget(page);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        sizePolicy.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy);
        widget_3->setMinimumSize(QSize(0, 140));
        verticalLayout_7 = new QVBoxLayout(widget_3);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        widget_10 = new QWidget(widget_3);
        widget_10->setObjectName(QString::fromUtf8("widget_10"));
        widget_10->setStyleSheet(QString::fromUtf8("QWidget#widget_10{\n"
"	background-color:   \n"
"}\n"
"QWidget#widget_10 .QLabel{\n"
"  color:#fff;\n"
"   background-color:#59AAE8;\n"
"   padding:5px;\n"
"   border-radius:3px;\n"
"   border-color:#499BDC;\n"
"   border-width: 1px;\n"
"   border-style: solid;\n"
"}\n"
"\n"
"\n"
"QWidget#widget_10 .QLabel:hover{\n"
"   background-color:rgb(89, 170, 200);\n"
"}\n"
""));
        horizontalLayout_6 = new QHBoxLayout(widget_10);
        horizontalLayout_6->setSpacing(10);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(-1, 12, -1, 12);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);

        pushButton_3 = new QPushButton(widget_10);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        horizontalLayout_6->addWidget(pushButton_3);

        pushButton_2 = new QPushButton(widget_10);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout_6->addWidget(pushButton_2);

        pushButton_4 = new QPushButton(widget_10);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        horizontalLayout_6->addWidget(pushButton_4);

        label_21 = new QLabel(widget_10);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_6->addWidget(label_21);

        label_14 = new QLabel(widget_10);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_6->addWidget(label_14);

        label_15 = new QLabel(widget_10);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_6->addWidget(label_15);


        verticalLayout_7->addWidget(widget_10);


        verticalLayout->addWidget(widget_3);

        stackedWidget->addWidget(page);

        verticalLayout_6->addWidget(stackedWidget);


        horizontalLayout_8->addWidget(widget_12);


        retranslateUi(MainForm);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainForm);
    } // setupUi

    void retranslateUi(QWidget *MainForm)
    {
        MainForm->setWindowTitle(QApplication::translate("MainForm", "Gas Miontor", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainForm", "Gas Minotor", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("MainForm", "JiKu", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("MainForm", "JiaYouBeng", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainForm", "Close Alarm", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("MainForm", "Option", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("MainForm", "System Setting", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("MainForm", "Log", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainForm", "Rest", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("MainForm", "Back", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("MainForm", "Exit", 0, QApplication::UnicodeUTF8));
        textEdit->setHtml(QApplication::translate("MainForm", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'\345\276\256\350\275\257\351\233\205\351\273\221'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("MainForm", "run", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("MainForm", "paly", 0, QApplication::UnicodeUTF8));
        pushButton_4->setText(QApplication::translate("MainForm", "ShowPan", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("MainForm", "Gas view", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("MainForm", "Clear", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("MainForm", "Log", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainForm: public Ui_MainForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFORM_H
