#ifndef COCKPITHEADSETVIEW_H
#define COCKPITHEADSETVIEW_H

#include <QDialog>

#include "cockpit.h"

#include <QGraphicsView>
#include <QScreen>

class CockpitHeadsetView : public QDialog
{
    Q_OBJECT
public:
    explicit CockpitHeadsetView(Cockpit* cockpit, QWidget* parent = nullptr);
    void setScreen(QScreen* screen);

private:
    QGraphicsView* m_view;

signals:

public slots:

private slots:
    void resizeEvent(QResizeEvent* event);
    void showEvent(QShowEvent* event);
};

#endif // COCKPITHEADSETVIEW_H
