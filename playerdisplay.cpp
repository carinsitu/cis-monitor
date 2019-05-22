#include "playerdisplay.h"
#include "carcameraitem.h"

#include <QGraphicsView>

PlayerDisplay::PlayerDisplay(const QCameraInfo &cameraInfo, QObject *parent) : QObject(parent)
{
    QGraphicsScene* scene = new QGraphicsScene(this);

    QGraphicsView* playerView = new QGraphicsView();
    playerView->setScene(scene);
    playerView->setFixedSize(640,480);
    playerView->show();

    QGraphicsWidget *cameraItem = new CarCameraItem(cameraInfo, playerView);
    scene->addItem(cameraItem);

    m_osd = new QGraphicsItemGroup(cameraItem);

    // Display device name in OSD
    new QGraphicsSimpleTextItem(cameraInfo.deviceName(), m_osd);

    // Display a red rect in OSD (through whole scene)
    scene->addRect(0, 0, 320, 240, QPen(QColor("red")));
}
