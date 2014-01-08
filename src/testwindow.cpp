#include "testwindow.h"
#include "ui_testwindow.h"

#include <QPalette>
#include <QBrush>
#include <QStackedLayout>

TestWindow::TestWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestWindow)
{
    ui->setupUi(this);

    // ui->stackedWidget


//    QPalette pal = palette();
//    pal.setColor(QPalette::Background, QColor(0x00,0xff,0x00,0x00));

//    setPalette(pal);


//    ui->page_2->setPalette(pal);

//    ui->page->setPalette(pal);

    QStackedLayout*laylout=(QStackedLayout*)ui->stackedWidget->layout();

    laylout->setStackingMode(QStackedLayout::StackAll);


    ui->stackedWidget->setCurrentIndex(1);

    ui->page->setVisible(false);



}

TestWindow::~TestWindow()
{
    delete ui;
}
