#include "osdspeedcounter.h"

#include <QFontDatabase>

OsdSpeedCounter::OsdSpeedCounter(QGraphicsItem* parent) : QGraphicsItemGroup(parent)
{
    QFontDatabase::addApplicationFont(":/fonts/digital-7-mono.ttf");
    QFont counterFont = QFont("Digital-7 Mono, Regular", 45, 1);
    m_text = new QGraphicsTextItem(this);
    this->addToGroup(m_text);
    m_text->setFont(counterFont);
    m_speedIndicatorClip = new OsdSpeedIndicatorClip(this);
    this->addToGroup(m_speedIndicatorClip);

    setSpeed(0);
}

QRectF OsdSpeedCounter::boundingRect() const
{
    return QRectF(0, 0, 200, 100);
}

void OsdSpeedCounter::setSpeed(qint16 speed)
{
    m_text->setPlainText(QString::number(speed) + "%");
    m_text->setPos(boundingRect().width() - m_text->boundingRect().width() - 5, boundingRect().height() - m_text->boundingRect().height());
    m_speedIndicatorClip->setSpeed(speed);
}
