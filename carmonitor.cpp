#include "carmonitor.h"
#include "ui_carmonitor.h"

#include <QCameraInfo>
#include <QGraphicsVideoItem>
#include <QGraphicsView>
#include <QGraphicsScene>

CarMonitor::CarMonitor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CarMonitor)
{
    ui->setupUi(this);

    const QList<QCameraInfo> availableCameras = QCameraInfo::availableCameras();
    for (const QCameraInfo &cameraInfo : availableCameras) {
        createCameraView(cameraInfo);
    }

}

CarMonitor::~CarMonitor()
{
    delete ui;
}

void CarMonitor::createCameraView(const QCameraInfo &cameraInfo)
{
    // HACK: Hardcoded device= setting when video source is v4l2src
    QString env = QString("uvcvideo=v4l2src device=") + cameraInfo.deviceName() + QString( " ! jpegdec ! videoconvert");
    qputenv("QT_GSTREAMER_CAMERABIN_VIDEOSRC", env.toUtf8());

    QCamera* camera = new QCamera(cameraInfo);
    QGraphicsScene* scene = new QGraphicsScene(this);
    QGraphicsView* view = new QGraphicsView(scene, ui->centralWidget);
    ui->verticalLayout->addWidget(view);

    QGraphicsVideoItem *item = new QGraphicsVideoItem;
    camera->setViewfinder(item);
    view->scene()->addItem(item);
    view->show();
    camera->start();
}
