#include "carmonitor.h"
#include "ui_carmonitor.h"
#include "cockpit.h"
#include "cockpitmonitor.h"
#include "cockpitheadsetview.h"

#include <QtMqtt/QMqttClient>

#include <QGuiApplication>
#include <QScreen>
#include <QCameraInfo>
#include <QtWidgets/QMessageBox>
#include <QGridLayout>
#include <QCloseEvent>

#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusReply>

#include <QWindow>

CarMonitor::CarMonitor(QWidget* parent) : QMainWindow(parent), ui(new Ui::CarMonitor)
{
    ui->setupUi(this);

    inhibitScreenSaver();

    // MQTT
    m_mqttClient = new QMqttClient(this);
    m_mqttClient->setHostname("localhost");
    m_mqttClient->setPort(1883);

    connect(m_mqttClient, &QMqttClient::stateChanged, this, &CarMonitor::onMqttStateChanged);
    connect(m_mqttClient, &QMqttClient::messageReceived, this, &CarMonitor::onMqttMessageReceived);

    m_mqttClient->connectToHost();

    connect(qApp, &QGuiApplication::primaryScreenChanged, this, &CarMonitor::onPrimaryScreenChanged);

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
        auto subscription = m_mqttClient->subscribe(QString("carinsitu/cockpit/#"));
        if (!subscription) {
            QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not subscribe. Is there a valid connection?"));
            return;
        }
        break;
    }
    case QMqttClient::Disconnected: {
        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("MQTT client disconnected"));
        break;
    }
    case QMqttClient::Connecting: {
        break;
    }
    }
}

void CarMonitor::onMqttMessageReceived(const QByteArray& message, const QMqttTopicName& topic)
{
    QRegExp regexp("^carinsitu/cockpit/(\\d+)/(.*)$");
    if (regexp.indexIn(topic.name()) != -1) {
        int cockpitId = regexp.cap(1).toInt();
        QString cockpitTopic = regexp.cap(2);
        if (cockpitId >= 0 && cockpitId < m_cockpits.size()) {
            m_cockpits.at(cockpitId)->processMqttMessage(cockpitTopic, message);
        }
    }
}

void CarMonitor::onPrimaryScreenChanged(QScreen* screen)
{
    qDebug() << Q_FUNC_INFO << "Screen: " << screen->name();
}

void CarMonitor::on_pb_displayCockpitHeadsetViews_toggled(bool checked)
{
    if (checked) {
        openCockpitHeadsetViews();
    } else {
        closeCockpitHeadsetViews();
    }
}

void CarMonitor::openCockpitHeadsetViews()
{
    // Screens
    QList<QScreen*> screensAvailable;
    foreach (QScreen* screen, QGuiApplication::screens()) {
        if (window()->windowHandle()->screen() == screen) {
            qDebug() << "Screen: (primary):" << screen->name();
        } else {
            qDebug() << "Screen (secondary): " << screen->name();
            screensAvailable.append(screen);
        }
    }

    for (Cockpit* cockpit : m_cockpits) {
        if (screensAvailable.size()) {
            openCockitHeadsetView(cockpit, screensAvailable.takeFirst());
        }
    }
}

void CarMonitor::openCockitHeadsetView(Cockpit* cockpit, QScreen* screen)
{
    CockpitHeadsetView* headsetView = new CockpitHeadsetView(cockpit);
    headsetView->setScreen(screen);
    m_cockpitHeadsetViews.append(headsetView);
}

void CarMonitor::closeCockpitHeadsetViews()
{
    for (CockpitHeadsetView* cockpitHeadsetView : m_cockpitHeadsetViews) {
        cockpitHeadsetView->close();
        cockpitHeadsetView->deleteLater();
    }
    m_cockpitHeadsetViews.clear();
}

void CarMonitor::inhibitScreenSaver()
{
    QDBusConnection bus = QDBusConnection::sessionBus();
    if (bus.isConnected()) {
        QString service = "org.freedesktop.ScreenSaver";
        QString path = "/org/freedesktop/ScreenSaver";

        QDBusInterface screenSaverInterface(service, path, service, bus, this);
        if (!screenSaverInterface.isValid())
            qDebug() << "Unable to inhibit screensaver";

        QDBusReply<uint> reply = screenSaverInterface.call("Inhibit", "fr.opus-codium.cismonitor", "Driving a car");
        if (!reply.isValid()) {
            QDBusError error = reply.error();
            qDebug() << error.message() << error.name();
        }
    }
}

void CarMonitor::closeEvent(QCloseEvent* event)
{
    closeCockpitHeadsetViews();
    event->accept();
}
