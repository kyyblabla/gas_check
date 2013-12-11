#ifndef EQUIPMENTWIDGET_H
#define EQUIPMENTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QString>


class EquipmentWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EquipmentWidget(QWidget *parent = 0);

    void initWidget();
    void setLabels();
    void updateLabelInfo(int labelName, int status, QString info);

signals:
    
public slots:

private:
    QLabel *lLightLabel;

    QLabel *lNongDuLabel;
    QString lNongDuLabelName;
    QString lNongDuLabelValue;

    QLabel *lOnOrOffLabel;
    QString lOnOrOffLabelName;
    QString lOnOrOffLabelValue;

    QLabel *lWorkOrBreakLabel;
    QString lWorkOrBreakLabelName;
    QString lWorkOrBreakLabelValue;

    QLabel *lWaringLabel;
    QString lWaringLabelName;
    QString lWaringLabelValue;
    
};

#endif // EQUIPMENTWIDGET_H
