#ifndef COCKPITMONITORVIEW_H
#define COCKPITMONITORVIEW_H

#include <QWidget>

#include "cockpit.h"

#include <QGraphicsView>

class CockpitMonitorView : public QWidget
{
    Q_OBJECT
public:
    explicit CockpitMonitorView(Cockpit* cockpit, QWidget* parent = nullptr);

private:
    QGraphicsView* m_view;

signals:

public slots:

private slots:
    void resizeEvent(QResizeEvent* event);
    void showEvent(QShowEvent* event);
};

#endif // COCKPITMONITORVIEW_H
