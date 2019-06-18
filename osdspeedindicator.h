#ifndef OSDSPEEDINDICATOR_H
#define OSDSPEEDINDICATOR_H

#include <QGraphicsItemGroup>
#include <QPainter>

class OsdSpeedIndicator : public QGraphicsItemGroup
{
public:
    explicit OsdSpeedIndicator(QGraphicsItem* parent = nullptr);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void setSpeed(qint16 speed);

private:
    QGraphicsRectItem* m_background;
    qint16 m_speed = 0;
};

#endif // OSDSPEEDINDICATOR_H
