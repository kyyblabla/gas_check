#-------------------------------------------------
#
# Project created by QtCreator 2013-11-28T17:43:18
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FGCheck
TEMPLATE = app


SOURCES += main.cpp\
        mainform.cpp \
    settingdialog.cpp \
    logviewdialog.cpp \
    sqlutil.cpp \
    config.cpp \
    qcustlabel.cpp \
    equipmentwidget.cpp

HEADERS  += mainform.h \
    settingdialog.h \
    logviewdialog.h \
    sqlutil.h \
    config.h \
    qcustlabel.h \
    equipmentwidget.h

FORMS    += mainform.ui \
    settingdialog.ui \
    logviewdialog.ui

RESOURCES += \
    rs/myrs.qrc

OTHER_FILES += \
    config.ini
