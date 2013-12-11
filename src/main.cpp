﻿#include "mainform.h"
#include "sqlutil.h"
#include "config.h"

#include <QApplication>
#include <QTextCodec>
#include <QDebug>

int main(int argc, char *argv[])
{

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(codec);

    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);

    QApplication a(argc, argv);
    Config::initConfig();
    MainForm w;
    w.show();
    return a.exec();

}
