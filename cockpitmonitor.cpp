#include "cockpitmonitor.h"

#include <QGraphicsScene>
#include <QVBoxLayout>

#include "cockpitmonitorview.h"
#include "videoinputitem.h"

CockpitMonitor::CockpitMonitor(Cockpit* cockpit, QWidget* parent) : QGroupBox(parent)
{
    CockpitMonitorView* monitorView = new CockpitMonitorView(cockpit, this);

    QLayout* layout = new QVBoxLayout;
    layout->addWidget(monitorView);
    this->setLayout(layout);
}
