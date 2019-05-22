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

    QGraphicsView* playerView = new QGraphicsView();
    playerView->setScene(scene);
    playerView->setFixedSize(640,480);
    playerView->show();

    QGraphicsWidget *cameraItem = new CarCameraItem(cameraInfo, playerView);
    view->scene()->addItem(cameraItem);
    view->setViewport(new QOpenGLWidget);

    QGraphicsSimpleTextItem *itemOSD = new QGraphicsSimpleTextItem(cameraItem);
    scene->addSimpleText(cameraInfo.deviceName());
    scene->addRect(0, 0, 320, 240, QPen(QColor("red")));

    view->show();

    qDebug() << "HELLO: " << cameraItem->size();
}
