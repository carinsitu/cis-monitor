#ifndef VIDEOINPUTITEM_H
#define VIDEOINPUTITEM_H

#include <QWidget>

#include <QGraphicsVideoItem>
#include <QCameraInfo>

class VideoInputItem : public QGraphicsVideoItem
{
public:
    VideoInputItem(const QCameraInfo& cameraInfo);
};

#endif // VIDEOINPUTITEM_H
