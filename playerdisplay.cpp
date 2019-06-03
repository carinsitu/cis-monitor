#include "playerdisplay.h"

#include "playerview.h"
#include "videoinputitem.h"

#include <QGraphicsView>

PlayerDisplay::PlayerDisplay(const QCameraInfo& cameraInfo, QObject* parent) : QObject(parent)
{
    QGraphicsScene* scene = new QGraphicsScene(this);

    PlayerView* playerView = new PlayerView;
    playerView->view()->setScene(scene);
    playerView->show();

    QGraphicsItem* cameraItem = new VideoInputItem(cameraInfo);
    scene->addItem(cameraItem);

    m_osd = new QGraphicsItemGroup(cameraItem);

    // Display device name in OSD
    m_text = new QGraphicsSimpleTextItem(cameraInfo.deviceName(), m_osd);

    // Display a red rect in OSD (through whole scene)
    scene->addRect(0, 0, 320, 240, QPen(QColor("red")));
}

void PlayerDisplay::setMessage(QString message)
{
    m_text->setText(message);
}
