#include "carmonitor.h"
#include "ui_carmonitor.h"

#include <QCameraInfo>

#include "playerdisplay.h"

#include <QtMqtt/QMqttClient>
#include <QtWidgets/QMessageBox>

CarMonitor::CarMonitor(QWidget* parent) : QMainWindow(parent), ui(new Ui::CarMonitor)
{
    ui->setupUi(this);

    // MQTT
    m_client = new QMqttClient(this);
    m_client->setHostname(m_mqttHost);
    m_client->setPort(m_mqttPort);

    connect(m_client, &QMqttClient::stateChanged, this, &CarMonitor::updateLogStateChange);
    connect(m_client, &QMqttClient::messageReceived, this, &CarMonitor::onMqttMessageReceived);

    m_client->connectToHost();

    // FPV
    for (int i = 0; i < m_maxDisplays; i++) {
        QString deviceName("/dev/video");
        deviceName += QString::number(i);
        createCameraView(QCameraInfo(deviceName.toUtf8()));
    }
}

CarMonitor::~CarMonitor()
{
    delete ui;
}

void CarMonitor::createCameraView(const QCameraInfo& cameraInfo)
{
    m_displays.append(new PlayerDisplay(cameraInfo));
}

void CarMonitor::updateLogStateChange()
{
    switch (m_client->state()) {
    case QMqttClient::Connected: {
        // subscribe to topic
        auto subscription = m_client->subscribe(m_mqttTopic + "/#");
        if (!subscription) {
            QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not subscribe. Is there a valid connection?"));
            return;
        }
        break;
    }
    default: {
        qDebug() << "MQTT state: " << m_client->state();
    }
    }
}

void CarMonitor::onMqttMessageReceived(const QByteArray& message, const QMqttTopicName& topic)
{
    QStringList topicParts = topic.name().split('/');
    int carNum = topicParts.last().toInt();
    if (carNum > 0 && carNum < m_maxDisplays) {
        m_displays.at(carNum - 1)->setMessage(message);
    }
}
