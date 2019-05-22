#include "carcameraitem.h"

CarCameraItem::CarCameraItem(const QCameraInfo &cameraInfo)
{
    // HACK: Hardcoded device= setting when video source is v4l2src
    QString env = QString("uvcvideo=v4l2src device=") + cameraInfo.deviceName() + QString( " ! jpegdec ! videoconvert");
    qputenv("QT_GSTREAMER_CAMERABIN_VIDEOSRC", env.toUtf8());

    QCamera* camera = new QCamera(cameraInfo);
    camera->setViewfinder(this);
    camera->start();
}
