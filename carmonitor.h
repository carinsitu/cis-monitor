#ifndef CARMONITOR_H
#define CARMONITOR_H

#include <QMainWindow>
#include <QCamera>

namespace Ui {
class CarMonitor;
}

class CarMonitor : public QMainWindow
{
    Q_OBJECT

public:
    explicit CarMonitor(QWidget *parent = nullptr);
    ~CarMonitor();

private slots:
    void setCamera(const QCameraInfo &cameraInfo);

private:
    Ui::CarMonitor *ui;
    QScopedPointer<QCamera> m_camera;
};

#endif // CARMONITOR_H
