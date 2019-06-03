#ifndef OSDSPEEDCOUNTER_H
#define OSDSPEEDCOUNTER_H

#include <QGraphicsItemGroup>
#include <QPainter>

class OsdSpeedCounter : public QGraphicsItemGroup
{
public:
    explicit OsdSpeedCounter(QGraphicsItem* parent = nullptr);

    void setSpeed(qint16 speed);

    QRectF boundingRect() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

private:
    QGraphicsTextItem* m_text;
    QRectF m_mask;
};

#endif // OSDSPEEDCOUNTER_H
