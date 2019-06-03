#include "osdspeedcounter.h"

#include <QTextBlockFormat>
#include <QTextCursor>
#include <QFontDatabase>
#include <QLinearGradient>

OsdSpeedCounter::OsdSpeedCounter(QGraphicsItem* parent) : QGraphicsItemGroup(parent)
{
    QFontDatabase::addApplicationFont(":/fonts/digital-7-mono.ttf");
    QFont counterFont = QFont("Digital-7 Mono, Regular", 50, 1);
    m_text = new QGraphicsTextItem(this);
    this->addToGroup(m_text);
    m_text->setFont(counterFont);

    setSpeed(0);
}

QRectF OsdSpeedCounter::boundingRect() const
{
    return QRectF(0, 0, 200, 100);
}

void OsdSpeedCounter::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    (void)option;
    (void)widget;

    // Add antialiasing to painter
    painter->setRenderHint(QPainter::Antialiasing);

    // Create fill gradient
    QLinearGradient grad = QLinearGradient(QPointF(0, 0), QPointF(boundingRect().width(), 0));
    grad.setColorAt(0, Qt::green);
    grad.setColorAt(0.5, Qt::yellow);
    grad.setColorAt(1, Qt::red);

    QBrush brush(grad);

    QRectF gradientRect = boundingRect();

    // Create drawing path
    QPainterPath path = QPainterPath(QPointF(0, 100));
    path.lineTo(25, 100);
    path.quadTo(QPointF(60, 30), QPointF(190, 40));
    path.lineTo(boundingRect().width(), 0);
    path.quadTo(QPointF(50, 0), QPointF(0, boundingRect().height()));
    // Apply clip path to painter
    painter->setClipPath(path);
    // Fill the gradient rect
    painter->fillRect(gradientRect, grad);
    // fill the dark masking rect
    painter->fillRect(m_mask, QBrush(QColor(0, 0, 0, 120)));
    // Add stroke
    painter->drawPath(path);
}

void OsdSpeedCounter::setSpeed(qint16 speed)
{
    m_text->setPlainText(QString::number(speed) + "%");
    m_text->setPos(boundingRect().width() - m_text->boundingRect().width() - 5, boundingRect().height() / 2 - 5);
    m_mask = QRectF(QPointF(speed * (boundingRect().width() / 100), boundingRect().height()), QPointF(boundingRect().width(), 0));
}
