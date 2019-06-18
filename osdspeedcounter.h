#ifndef OSDSPEEDCOUNTER_H
#define OSDSPEEDCOUNTER_H

#include "osdspeedindicatorclip.h"

#include <QGraphicsItemGroup>

class OsdSpeedCounter : public QGraphicsItemGroup
{
public:
    explicit OsdSpeedCounter(QGraphicsItem* parent = nullptr);

    void setSpeed(qint16 speed);
    QRectF boundingRect() const;

private:
    QGraphicsSimpleTextItem* m_text;
    OsdSpeedIndicatorClip* m_speedIndicatorClip;
    QGraphicsPathItem* m_speedIndicatorUnderline;
};

#endif // OSDSPEEDCOUNTER_H
