#ifndef CARMONITOR_H
#define CARMONITOR_H

#include <QMainWindow>
#include <QCamera>
#include <QtMqtt/QMqttClient>
#include "playerdisplay.h"

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
    void createCameraView(const QCameraInfo& cameraInfo);
    void updateLogStateChange();
    void onMqttMessageReceived(const QByteArray& message, const QMqttTopicName& topic);

private:
    Ui::CarMonitor* ui;
    QMqttClient* m_client;
    QString m_mqttHost = "localhost";
    quint16 m_mqttPort = 1883;
    QString m_mqttTopic = "carinsitu/car";
    QList<PlayerDisplay*> m_displays;
    int m_maxDisplays = 3;
};

#endif // CARMONITOR_H
