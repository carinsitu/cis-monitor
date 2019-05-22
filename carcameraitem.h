#ifndef CARCAMERAITEM_H
#define CARCAMERAITEM_H

#include <QWidget>

#include <QGraphicsVideoItem>
#include <QCameraInfo>

class CarCameraItem : public QGraphicsVideoItem
{
public:
    CarCameraItem(const QCameraInfo &cameraInfo);
};

#endif // CARCAMERAITEM_H
