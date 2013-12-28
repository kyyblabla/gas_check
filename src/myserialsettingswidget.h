#ifndef MYSERIALSETTINGSWIDGET_H
#define MYSERIALSETTINGSWIDGET_H

#include <QWidget>

namespace Ui {
class MySerialSettingsWidget;
}

class MySerialSettingsWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit MySerialSettingsWidget(QWidget *parent = 0);
    ~MySerialSettingsWidget();
private slots:
    void changeSerialPort(int index);

private:
    void creatConnects();
    Ui::MySerialSettingsWidget *ui;
};

#endif // MYSERIALSETTINGSWIDGET_H
