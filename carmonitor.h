#ifndef CARMONITOR_H
#define CARMONITOR_H

#include <QMainWindow>

namespace Ui {
class CarMonitor;
}

class CarMonitor : public QMainWindow
{
    Q_OBJECT

public:
    explicit CarMonitor(QWidget *parent = nullptr);
    ~CarMonitor();

private:
    Ui::CarMonitor *ui;
};

#endif // CARMONITOR_H
