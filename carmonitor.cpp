#include "carmonitor.h"
#include "ui_carmonitor.h"
#include "cockpit.h"
#include "cockpitmonitor.h"

#include <QtMqtt/QMqttClient>

#include <QGuiApplication>
#include <QScreen>
#include <QCameraInfo>
#include <QtWidgets/QMessageBox>
#include <QGridLayout>

CarMonitor::CarMonitor(QWidget* parent) : QMainWindow(parent), ui(new Ui::CarMonitor)
{
    ui->setupUi(this);

    // MQTT
    m_mqttClient = new QMqttClient(this);
    QString m_mqttTopic = "carinsitu/car";

    m_mqttClient->setHostname("localhost");
    m_mqttClient->setPort(1883);

    connect(m_mqttClient, &QMqttClient::stateChanged, this, &CarMonitor::onMqttStateChanged);
    connect(m_mqttClient, &QMqttClient::messageReceived, this, &CarMonitor::onMqttMessageReceived);

    m_mqttClient->connectToHost();

    // Screens
    foreach (QScreen* screen, QGuiApplication::screens()) {
        if (qGuiApp->primaryScreen() == screen) {
            qDebug() << "Screen: (primary):" << screen->name();
        } else {
            qDebug() << "Screen (secondary): " << screen->name();
        }
    }

    // FPV
    for (int i = 0; i < 4; i++) {
        QString deviceName("/dev/video");
        deviceName += QString::number(i);
        Cockpit* cockpit = new Cockpit(QCameraInfo(deviceName.toUtf8()), this);
        CockpitMonitor* monitor = new CockpitMonitor(cockpit, this);
        QString title = QString("Cockpit") + QString::number(i);
        monitor->setTitle(title);
        ui->centralLayout->addWidget(monitor, i % 2, i / 2);
        m_cockpits.append(cockpit);
    }
}

CarMonitor::~CarMonitor()
{
    delete ui;
}

void CarMonitor::onMqttStateChanged()
{
    switch (m_mqttClient->state()) {
    case QMqttClient::Connected: {
        // subscribe to topic
        auto subscription = m_mqttClient->subscribe(m_mqttTopic + "/#");
        if (!subscription) {
            QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not subscribe. Is there a valid connection?"));
            return;
        }
        break;
    }
    default: {
        qDebug() << "MQTT state: " << m_mqttClient->state();
    }
    }
}

void CarMonitor::onMqttMessageReceived(const QByteArray& message, const QMqttTopicName& topic)
{
    QStringList topicParts = topic.name().split('/');
    int carNum = topicParts.last().toInt();
    if (carNum > 0 && carNum < m_cockpits.size()) {
        //m_cockpits.at(carNum - 1)->setMessage(message);
    }
}
