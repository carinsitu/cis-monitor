#include "osdspeedindicatorclip.h"

OsdSpeedIndicatorClip::OsdSpeedIndicatorClip(QGraphicsItem* parent) : QGraphicsItemGroup(parent)
{
    this->setFlag(GraphicsItemFlag::ItemClipsChildrenToShape);
    this->addToGroup(m_speedIndicator);
}

QRectF OsdSpeedIndicatorClip::boundingRect() const
{
    return QRectF(0, 0, 200, 100);
}

QPainterPath OsdSpeedIndicatorClip::shape() const
{
    QPainterPath path = QPainterPath(QPointF(0, boundingRect().height()));
    path.lineTo(25, boundingRect().height());
    path.quadTo(QPointF(60, 30), QPointF(190, 40));
    path.lineTo(boundingRect().width(), 0);
    path.quadTo(QPointF(50, 0), QPointF(0, boundingRect().height()));
    return path;
}

void OsdSpeedIndicatorClip::setSpeed(qint16 speed)
{
    m_speedIndicator->setSpeed(speed);
}
