#include "carmonitor.h"
#include "ui_carmonitor.h"

#include <QCameraInfo>

#include "playerdisplay.h"

CarMonitor::CarMonitor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CarMonitor)
{
    ui->setupUi(this);

    for(int i = 0; i<3; i++) {
        QString deviceName("/dev/video");
        deviceName += QString::number(i);
        createCameraView(QCameraInfo(deviceName.toUtf8()));
    }
}

CarMonitor::~CarMonitor()
{
    delete ui;
}

void CarMonitor::createCameraView(const QCameraInfo &cameraInfo)
{
    new PlayerDisplay(cameraInfo);
}
