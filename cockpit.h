#ifndef COCKPIT_H
#define COCKPIT_H

#include <QObject>

#include "osdspeedcounter.h"
#include "enginesound.h"

#include <QCameraInfo>
#include <QGraphicsItemGroup>
#include <QGraphicsSimpleTextItem>
#include <QComboBox>

class Cockpit : public QObject
{
    Q_OBJECT
public:
    explicit Cockpit(const QCameraInfo& cameraInfo, QObject* parent = nullptr);
    QGraphicsScene* scene() { return m_scene; }
    EngineSound* engineSound() { return m_engineSound; }
    void processMqttMessage(const QString& topic, const QByteArray& message);

private:
    QGraphicsScene* m_scene;
    QGraphicsItemGroup* m_osdItemGroup;
    QGraphicsSimpleTextItem* m_text;
    QGraphicsSimpleTextItem* m_rssi;
    OsdSpeedCounter* m_speedCounter;
    EngineSound* m_engineSound;
signals:

public slots:
};

#endif // COCKPIT_H
