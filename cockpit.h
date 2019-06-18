#ifndef COCKPIT_H
#define COCKPIT_H

#include <QObject>

#include "osdspeedcounter.h"

#include <QCameraInfo>
#include <QGraphicsItemGroup>
#include <QGraphicsSimpleTextItem>

class Cockpit : public QObject
{
    Q_OBJECT
public:
    explicit Cockpit(const QCameraInfo& cameraInfo, QObject* parent = nullptr);
    QGraphicsScene* scene() { return m_scene; }
    void processMqttMessage(const QString& topic, const QByteArray& message);

private:
    QGraphicsScene* m_scene;
    QGraphicsItemGroup* m_osdItemGroup;
    QGraphicsSimpleTextItem* m_text;
    QGraphicsSimpleTextItem* m_rssi;
    OsdSpeedCounter* m_speedCounter;

signals:

public slots:
};

#endif // COCKPIT_H
