#include "cockpit.h"

#include <QGraphicsScene>
#include <QGraphicsItem>

#include "videoinputitem.h"

Cockpit::Cockpit(const QCameraInfo& cameraInfo, QObject* parent) : QObject(parent)
{
    m_scene = new QGraphicsScene(this);

    QGraphicsItem* cameraItem = new VideoInputItem(cameraInfo);
    m_scene->addItem(cameraItem);

    m_osd = new QGraphicsItemGroup(cameraItem);

    // Display device name in OSD
    m_text = new QGraphicsSimpleTextItem(cameraInfo.deviceName(), m_osd);

    // Display a red rect in OSD (through whole scene)
    m_scene->addRect(0, 0, 320, 240, QPen(QColor("red")));
}
