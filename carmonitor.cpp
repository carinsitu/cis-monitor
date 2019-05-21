#include "carmonitor.h"
#include "ui_carmonitor.h"

#include <QCameraInfo>

CarMonitor::CarMonitor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CarMonitor)
{
    ui->setupUi(this);

    const QList<QCameraInfo> availableCameras = QCameraInfo::availableCameras();
    for (const QCameraInfo &cameraInfo : availableCameras) {
        qDebug() << cameraInfo;
    }

    setCamera(QCameraInfo("/dev/video0"));
}

CarMonitor::~CarMonitor()
{
    delete ui;
}

void CarMonitor::setCamera(const QCameraInfo &cameraInfo)
{
    qDebug() << "Selected camera: " << cameraInfo;
    m_camera.reset(new QCamera(cameraInfo));
    m_camera->setViewfinder(ui->viewfinder);
    m_camera->start();
    qDebug() << m_camera->error();
    qDebug() << "Used camera: " << QCameraInfo(*m_camera);
}
