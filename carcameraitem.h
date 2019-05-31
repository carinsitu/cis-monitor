#ifndef CARCAMERAITEM_H
#define CARCAMERAITEM_H

#include <QWidget>

#include <QGraphicsVideoItem>
#include <QCameraInfo>
#include <QGst/Ui/GraphicsVideoWidget>
#include <QGst/Pipeline>
#include <QGst/Bin>

class CarCameraItem : public QGst::Ui::GraphicsVideoWidget
{
public:
    CarCameraItem(const QCameraInfo& cameraInfo, QGraphicsView* view);

private:
    QGst::BinPtr m_videoSource;
    QGst::PipelinePtr m_pipeline;
};

#endif // CARCAMERAITEM_H
