#include "cockpitheadsetview.h"

#include <QVBoxLayout>
#include <QWindow>

CockpitHeadsetView::CockpitHeadsetView(Cockpit* cockpit, QWidget* parent) : QDialog(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->setContentsMargins(0, 0, 0, 0);

    m_view = new QGraphicsView(this);
    m_view->setResizeAnchor(QGraphicsView::AnchorViewCenter);
    this->setStyleSheet("background-color:black;");
    this->layout()->addWidget(m_view);
    m_view->setScene(cockpit->scene());
    m_view->show();

    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
}

void CockpitHeadsetView::resizeEvent(QResizeEvent* event)
{
    (void)event;
    m_view->fitInView(m_view->scene()->sceneRect());
}

void CockpitHeadsetView::showEvent(QShowEvent* event)
{
    (void)event;
    m_view->fitInView(m_view->scene()->sceneRect());
}

void CockpitHeadsetView::setScreen(QScreen* screen)
{
    qDebug() << Q_FUNC_INFO << "Move to screen: " << screen->name();
    move(screen->geometry().x(), screen->geometry().y());
    // setGeometry(screen->geometry());
    showFullScreen();
}
