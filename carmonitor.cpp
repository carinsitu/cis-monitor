#include "carmonitor.h"
#include "ui_carmonitor.h"

CarMonitor::CarMonitor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CarMonitor)
{
    ui->setupUi(this);
}

CarMonitor::~CarMonitor()
{
    delete ui;
}
