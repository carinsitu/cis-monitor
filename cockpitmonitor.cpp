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

    m_soundCardSelector = new QComboBox();
    m_soundCardSelector->addItem("");
    m_soundCardSelector->addItems(cockpit->soundPlayer()->listAllDevices());
    connect(m_soundCardSelector, SIGNAL(currentTextChanged(QString)), cockpit->soundPlayer(), SLOT(onSoundCardSelected(QString)));
    layout->addWidget(m_soundCardSelector);

    this->setLayout(layout);
}
