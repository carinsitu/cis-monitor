#ifndef CARMONITOR_H
#define CARMONITOR_H

#include <QMainWindow>
#include <QCamera>

#include <QtMqtt/QMqttClient>

#include "cockpit.h"
#include "cockpitheadsetview.h"

namespace Ui {
class CarMonitor;
}

class CarMonitor : public QMainWindow
{
    Q_OBJECT

public:
    explicit CarMonitor(QWidget* parent = nullptr);
    ~CarMonitor();

private slots:
    void onMqttStateChanged();
    void onMqttMessageReceived(const QByteArray& message, const QMqttTopicName& topic);
    void onPrimaryScreenChanged(QScreen* screen);

    void on_pb_displayCockpitHeadsetViews_toggled(bool checked);

private:
    Ui::CarMonitor* ui;
    QMqttClient* m_mqttClient;
    QList<Cockpit*> m_cockpits;
    QList<CockpitHeadsetView*> m_cockpitHeadsetViews;

    void cockpitsSetup();

    void inhibitScreenSaver();

    void openCockpitHeadsetViews();
    void closeCockpitHeadsetViews();

    void closeEvent(QCloseEvent*);
};

#endif // CARMONITOR_H
