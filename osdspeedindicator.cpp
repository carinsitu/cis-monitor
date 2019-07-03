#include "osdspeedindicator.h"
#include <QLinearGradient>

OsdSpeedIndicator::OsdSpeedIndicator(QGraphicsItem* parent) : QGraphicsItemGroup(parent)
{
    this->setFlag(GraphicsItemFlag::ItemClipsChildrenToShape);
    QLinearGradient grad = QLinearGradient(QPointF(0, 0), QPointF(boundingRect().width(), 0));
    grad.setColorAt(0, QColor(47, 197, 50, 160));
    grad.setColorAt(0.5, QColor(255, 185, 16, 160));
    grad.setColorAt(1, QColor(230, 0, 0, 160));
    QBrush brush(grad);

    m_background = new QGraphicsRectItem(boundingRect());
    m_background->setBrush(brush);
    m_background->setPen(Qt::NoPen);
    this->addToGroup(m_background);
}

QRectF OsdSpeedIndicator::boundingRect() const
{
    return QRectF(0, 0, 200, 100);
}

QPainterPath OsdSpeedIndicator::shape() const
{
    qreal top_right_x = m_speed * boundingRect().width() / boundingRect().height();
    qreal top_right_y = boundingRect().height() - m_speed;
    qreal top_left_x = top_right_x - boundingRect().width();
    top_left_x = (top_left_x <= 0) ? 1 : top_left_x;
    qreal top_left_y =
        boundingRect().height() - (boundingRect().height() - top_right_y) / (boundingRect().width() - top_right_x) * (boundingRect().width() - top_left_x);
    top_left_y = (top_left_y <= -10000) ? -10000 : top_left_y;

    QPolygonF m_polygon = QPolygonF();
    // bottom left
    m_polygon.append(QPointF(0, boundingRect().height()));
    // bottom right
    m_polygon.append(QPointF(boundingRect().width(), boundingRect().height()));
    // top left
    m_polygon.append(QPointF(top_right_x, top_right_y));
    // top right
    m_polygon.append(QPointF(top_left_x, top_left_y));
    QGraphicsPolygonItem* poly = new QGraphicsPolygonItem(m_polygon);
    poly->setPen(Qt::NoPen);
    poly->setBrush(Qt::NoBrush);
    return poly->shape();
}

void OsdSpeedIndicator::setSpeed(qint16 speed)
{
    m_speed = speed < 100 ? speed : 100;
}
