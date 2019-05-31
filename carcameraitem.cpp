#include "carcameraitem.h"
#include <QGst/Ui/GraphicsVideoSurface>

CarCameraItem::CarCameraItem(const QCameraInfo& cameraInfo, QGraphicsView* view)
{
    if (!cameraInfo.isNull()) {
        // Prepare video element
        QGst::Ui::GraphicsVideoSurface* surface = new QGst::Ui::GraphicsVideoSurface(view);
        this->setSurface(surface);

        this->setPreferredSize(640, 480);

        // Video source
        m_videoSource = QGst::Bin::fromDescription("v4l2src device=" + cameraInfo.deviceName() + " ! jpegdec ! videoconvert");

        // Sink
        QGst::ElementPtr videoSink = surface->videoSink();

        // Pipeline
        m_pipeline = QGst::Pipeline::create();
        m_pipeline->add(m_videoSource, surface->videoSink());

        // Link source/sink
        m_videoSource->link(videoSink);
        m_pipeline->setState(QGst::StatePlaying);
    }
}
