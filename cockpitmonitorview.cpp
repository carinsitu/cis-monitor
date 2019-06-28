#include "cockpitmonitorview.h"

#include <QVBoxLayout>
#include <QWindow>

#include "carmonitor.h"

CockpitMonitorView::CockpitMonitorView(Cockpit* cockpit, QWidget* parent) : QWidget(parent), m_cockpit(cockpit)
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
}

void CockpitMonitorView::resizeEvent(QResizeEvent* event)
{
    (void)event;
    m_view->fitInView(m_view->scene()->sceneRect());
}

void CockpitMonitorView::showEvent(QShowEvent* event)
{
    (void)event;
    m_view->fitInView(m_view->scene()->sceneRect());
}

void CockpitMonitorView::mouseDoubleClickEvent(QMouseEvent* event)
{
    (void)event;
    dynamic_cast<CarMonitor*>(parent()->parent()->parent())->openCockitHeadsetView(m_cockpit, window()->windowHandle()->screen());
}
