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
    bool updateLabelVlaue(int labelIndex, int status);
    int getGasNd(){return lNongDuLabelStatus;}

signals:
    
public slots:

private:
    QLabel *lLightLabel;

    QLabel *lNongDuLabel;
    QString lNongDuLabelName;
    QString lNongDuLabelValue;
    int lNongDuLabelStatus;

    QLabel *lOnOrOffLabel;
    QString lOnOrOffLabelName;
    QString lOnOrOffLabelValue;
    int lOnOrOffLabelStatus;

    QLabel *lWorkOrBreakLabel;
    QString lWorkOrBreakLabelName;
    QString lWorkOrBreakLabelValue;
    int lWorkOrBreakLabelStatus;

    QLabel *lWaringLabel;
    QString lWaringLabelName;
    QString lWaringLabelValue;
    int lWaringLabelStatus;

    void updateInfo();
    
};

#endif // EQUIPMENTWIDGET_H
