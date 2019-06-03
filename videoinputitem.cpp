#include "videoinputitem.h"

VideoInputItem::VideoInputItem(const QCameraInfo& cameraInfo, QGraphicsItem* parent) : QGraphicsVideoItem(parent)
{
    QString pipelines =
        "uvcvideo:v4l2src ! jpegdec ! videoconvert;tw686x:v4l2src norm=255 ! video/x-raw,format=YUY2,interlace-mode=interleaved ! deinterlace ! videoconvert";
    qputenv("QT_GSTREAMER_CAMERABIN_VIDEOSRC_PIPELINE", pipelines.toUtf8());

    QCamera* camera = new QCamera(cameraInfo);
    camera->setViewfinder(this);
    camera->start();
}
