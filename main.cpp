#include "mainform.h"
#include "sqlutil.h"
#include "config.h"

#include <QApplication>
#include <QTextCodec>
#include <QDebug>

int main(int argc, char *argv[])
{

   QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));

   QApplication a(argc, argv);
    Config::initConfig();
    MainForm w;
    w.show();
    return a.exec();

}
