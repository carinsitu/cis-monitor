#include "carmonitor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CarMonitor w;
    w.show();

    return a.exec();
}
