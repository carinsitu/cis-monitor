#include "osdspeedcounter.h"

#include <QFontDatabase>

OsdSpeedCounter::OsdSpeedCounter(QGraphicsItem* parent) : QGraphicsItemGroup(parent)
{
    QFontDatabase::addApplicationFont(":/fonts/digital-7-mono.ttf");
    QFont counterFont = QFont("Digital-7 Mono, Regular", 45, 1);
    m_text = new QGraphicsSimpleTextItem(this);
    this->addToGroup(m_text);
    m_text->setBrush(QBrush(QColor(255, 255, 255, 200)));
    m_text->setPen(QColor(0, 0, 0, 50));
    m_text->setFont(counterFont);
    m_speedIndicatorClip = new OsdSpeedIndicatorClip(this);
    this->addToGroup(m_speedIndicatorClip);

    QPainterPath path = QPainterPath(QPointF(0, boundingRect().height()));
    path.lineTo(25, boundingRect().height());
    path.quadTo(QPointF(60, 30), QPointF(190, 40));
    path.lineTo(boundingRect().width(), 0);
    path.lineTo(boundingRect().width() + 4, 0);
    path.lineTo(194, 44);
    path.quadTo(QPointF(62, 34), QPointF(29, boundingRect().height() + 4));
    path.lineTo(0, boundingRect().height() + 4);
    path.lineTo(0, boundingRect().height());
    m_speedIndicatorUnderline = new QGraphicsPathItem(path);
    m_speedIndicatorUnderline->setBrush(QBrush(QColor(255, 255, 255, 200)));
    m_speedIndicatorUnderline->setPen(QColor(0, 0, 0, 50));
    this->addToGroup(m_speedIndicatorUnderline);

    setSpeed(0);
}

QRectF OsdSpeedCounter::boundingRect() const
{
    return QRectF(0, 0, 200, 100);
}

void OsdSpeedCounter::setSpeed(qint16 speed)
{
    m_text->setText(QString::number(speed) + "%");
    m_text->setPos(boundingRect().width() - m_text->boundingRect().width() - 5, boundingRect().height() - m_text->boundingRect().height());
    m_speedIndicatorClip->setSpeed(speed);
}
