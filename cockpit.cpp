#include "cockpit.h"

#include "videoinputitem.h"

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QFontDatabase>

Cockpit::Cockpit(const QCameraInfo& cameraInfo, QObject* parent) : QObject(parent)
{
    m_scene = new QGraphicsScene(this);
    QFontDatabase::addApplicationFont(":/fonts/digital-7-mono.ttf");
    QFont rssiFont = QFont("Digital-7 Mono, Regular", 15, 1);

    QGraphicsItem* cameraItem = new VideoInputItem(cameraInfo);
    m_scene->addItem(cameraItem);

    m_osdItemGroup = new QGraphicsItemGroup;
    m_scene->addItem(m_osdItemGroup);

    // Display device name in OSD
    m_text = new QGraphicsSimpleTextItem(cameraInfo.deviceName(), m_osdItemGroup);
    m_text->setPen(QColor("red"));
    m_osdItemGroup->addToGroup(m_text);

    // Display speed
    m_speedCounter = new OsdSpeedCounter(m_osdItemGroup);
    QPointF speedCounterPos = cameraItem->boundingRect().bottomRight();
    speedCounterPos -= m_speedCounter->boundingRect().bottomRight();
    speedCounterPos -= QPointF(10, 10);
    m_speedCounter->setPos(speedCounterPos);
    m_osdItemGroup->addToGroup(m_speedCounter);

    // Display rssi
    m_rssi = new QGraphicsSimpleTextItem(cameraInfo.deviceName(), m_osdItemGroup);
    m_rssi->setBrush(QBrush(QColor(255, 255, 255, 200)));
    m_rssi->setFont(rssiFont);
    m_rssi->setText("RSSI: ---");
    m_rssi->setPos(cameraItem->boundingRect().topRight().x() - m_rssi->boundingRect().width() - 5, cameraItem->boundingRect().topRight().y() + 5);
    m_osdItemGroup->addToGroup(m_rssi);

    // Debug: display rects in OSD
    m_scene->addRect(cameraItem->boundingRect(), QPen(QColor("red")));
    m_scene->addRect(m_osdItemGroup->boundingRect(), QPen(QColor("blue")));
    qDebug() << Q_FUNC_INFO << "Camera: " << cameraItem->boundingRect();
    qDebug() << Q_FUNC_INFO << "OSD: " << m_osdItemGroup->boundingRect();

    // Audio
    m_engineSound = new EngineSound();
}

void Cockpit::processMqttMessage(const QString& topic, const QByteArray& message)
{
    // text
    if (topic == QString("text")) {
        m_text->setText(message);
    } else if (topic == QString("car/throttle")) {
        int speed = message.toInt();
        if (speed < 0)
            speed = -speed;
        qreal speedReal = static_cast<qreal>(speed) / 32767.0;
        qint16 speedPercent = static_cast<qint16>(speedReal * 100.0);
        m_speedCounter->setSpeed(speedPercent);
        m_engineSound->setEngineSpeed(speedPercent);
    } else if (topic == QString("car/rssi")) {
        int rssi = message.toInt();
        m_rssi->setText("RSSI: " + QString::number(rssi).rightJustified(3));
    } else {
        qDebug() << Q_FUNC_INFO << "MQTT message dropped: " << message << "from topic: " << topic;
    }
}
