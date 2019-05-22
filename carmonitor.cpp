#include "carmonitor.h"
#include "ui_carmonitor.h"

#include <QCameraInfo>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QOpenGLWidget>

#include "carcameraitem.h"

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
    QGraphicsScene* scene = new QGraphicsScene(this);
    QGraphicsView* view = new QGraphicsView(scene, this);
    ui->centralLayout->addWidget(view);

    QGraphicsWidget *cameraItem = new CarCameraItem(cameraInfo, view);

    view->scene()->addItem(cameraItem);
    view->setViewport(new QOpenGLWidget);

    QGraphicsSimpleTextItem *itemOSD = new QGraphicsSimpleTextItem(cameraItem);
    scene->addSimpleText(cameraInfo.deviceName());

    view->show();

    qDebug() << "HELLO: " << cameraItem->size();
}
