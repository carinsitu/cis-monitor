#include "carmonitor.h"
#include "ui_carmonitor.h"

#include <QCameraInfo>

CarMonitor::CarMonitor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CarMonitor)
{
    ui->setupUi(this);
    setCamera(QCameraInfo::defaultCamera());

}

CarMonitor::~CarMonitor()
{
    delete ui;
}

void CarMonitor::setCamera(const QCameraInfo &cameraInfo)
{
    m_camera.reset(new QCamera(cameraInfo));
    m_camera->setViewfinder(ui->viewfinder);
    m_camera->start();
}
