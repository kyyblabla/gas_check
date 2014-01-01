QT       += core gui xml
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FGCheck
TEMPLATE = app

MOC_DIR     = generated
OBJECTS_DIR = generated
UI_DIR      = generated
RCC_DIR     = generated

TRANSLATIONS += gas_zh.ts

SOURCES +=  src/main.cpp\
            src/mainform.cpp \
            src/settingdialog.cpp \
            src/logviewdialog.cpp \
            src/sqlutil.cpp \
            src/config.cpp \
            src/qcustlabel.cpp \
            src/equipmentwidget.cpp \
            src/serialsettingswidget.cpp \
            3rdparty/qextserialport/qextserialport.cpp	\
            3rdparty/libmodbus/src/modbus.c \
            3rdparty/libmodbus/src/modbus-data.c \
            3rdparty/libmodbus/src/modbus-rtu.c \
            3rdparty/libmodbus/src/modbus-tcp.c \
            src/modbusrequestthread.cpp \
            src/configxml.cpp \
            src/gasviewform.cpp \
            src/gasviewwidget.cpp \
            src/myserialport.cpp \
            src/myserialsettingswidget.cpp \
            src/speedo_meter.cpp



HEADERS  += src/mainform.h \
            src/settingdialog.h \
            src/logviewdialog.h \
            src/sqlutil.h \
            src/config.h \
            src/qcustlabel.h \
            src/equipmentwidget.h \
            src/serialsettingswidget.h \
            src/imodbus.h \
            src/modbusrequestthread.h \
            3rdparty/qextserialport/qextserialport.h \
            3rdparty/qextserialport/qextserialenumerator.h \
            3rdparty/libmodbus/src/modbus.h \
            src/configxml.h \
            src/gasviewform.h \
            src/gasviewwidget.h \
            src/myserialport.h \
            src/myserialsettingswidget.h \
            src/speedo_meter.h



INCLUDEPATH += 3rdparty/libmodbus \
               3rdparty/libmodbus/src \
               3rdparty/qextserialport \
               src

INCLUDEPATH += E:\QT4\qwt-6.1.0\src

DEPENDPATH  += E:\QT4\qwt-6.1.0\lib


unix {
    SOURCES += 3rdparty/qextserialport/posix_qextserialport.cpp	\
           3rdparty/qextserialport/qextserialenumerator_unix.cpp
    DEFINES += _TTY_POSIX_
}

win32 {
    SOURCES += 3rdparty/qextserialport/win_qextserialport.cpp \
           3rdparty/qextserialport/qextserialenumerator_win.cpp
    DEFINES += _TTY_WIN_  WINVER=0x0501
    LIBS += -lsetupapi -lwsock32 -lWS2_32

}

LIBS += -LE:\QT4\qwt-6.1.0\lib -lqwtd



FORMS    += form/mainform.ui \
            form/settingdialog.ui \
            form/logviewdialog.ui \
            form/serialsettingswidget.ui \
            form/gasviewform.ui \
            form/gasviewwidget.ui \
            src/myserialsettingswidget.ui


RESOURCES += \
    rs/myrs.qrc

OTHER_FILES += \
    addrConfig.xml \
    config.ini
