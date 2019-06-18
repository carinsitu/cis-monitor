#ifndef OSDSPEEDINDICATORCLIP_H
#define OSDSPEEDINDICATORCLIP_H

#include "osdspeedindicator.h"

#include <QGraphicsItemGroup>
#include <QPainter>

class OsdSpeedIndicatorClip : public QGraphicsItemGroup
{
public:
    explicit OsdSpeedIndicatorClip(QGraphicsItem* parent = nullptr);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void setSpeed(qint16 speed);

private:
    OsdSpeedIndicator* m_speedIndicator = new OsdSpeedIndicator(this);
};

#endif // OSDSPEEDINDICATORCLIP_H
