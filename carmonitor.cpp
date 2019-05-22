#include "carmonitor.h"
#include "ui_carmonitor.h"

#include <QCameraInfo>

#include <QGraphicsView>
#include <QGraphicsScene>

#include "carcameraitem.h"

CarMonitor::CarMonitor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CarMonitor)
{
    ui->setupUi(this);

    for(int i = 0; i<6; i++) {
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
    QGraphicsScene* scene = new QGraphicsScene(this);
    QGraphicsView* view = new QGraphicsView(scene, ui->centralWidget);
    ui->centralLayout->addWidget(view);

    QGraphicsVideoItem *cameraItem = new CarCameraItem(cameraInfo);
    view->scene()->addItem(cameraItem);

    QGraphicsSimpleTextItem *itemOSD = new QGraphicsSimpleTextItem(cameraItem);
    scene->addSimpleText(cameraInfo.deviceName());

    view->show();

    qDebug() << "HELLO: " << cameraItem->size();
}
