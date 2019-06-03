#include "cockpit.h"

#include "videoinputitem.h"

#include <QGraphicsScene>
#include <QGraphicsItem>

Cockpit::Cockpit(const QCameraInfo& cameraInfo, QObject* parent) : QObject(parent)
{
    m_scene = new QGraphicsScene(this);

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

    // Debug: display rects in OSD
    m_scene->addRect(cameraItem->boundingRect(), QPen(QColor("red")));
    m_scene->addRect(m_osdItemGroup->boundingRect(), QPen(QColor("blue")));
    qDebug() << Q_FUNC_INFO << "Camera: " << cameraItem->boundingRect();
    qDebug() << Q_FUNC_INFO << "OSD: " << m_osdItemGroup->boundingRect();
}

void Cockpit::processMqttMessage(const QString& topic, const QByteArray& message)
{
    // text
    if (topic == QString("text")) {
        m_text->setText(message);
    } else {
        qDebug() << Q_FUNC_INFO << "MQTT message dropped: " << message << "from topic: " << topic;
    }
}
