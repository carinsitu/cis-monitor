#ifndef COCKPITMONITOR_H
#define COCKPITMONITOR_H

#include "cockpit.h"

#include <QGroupBox>
#include <QGraphicsScene>

class CockpitMonitor : public QGroupBox
{
    Q_OBJECT
public:
    explicit CockpitMonitor(Cockpit* cockpit, QWidget* parent = nullptr);
signals:

public slots:
};

#endif // COCKPITMONITOR_H
