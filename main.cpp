#include "mainwindow.h"

#include <QApplication>
#include "utils.h"
#include "vector.h"

int main(int argc, char *argv[])
{
    mats::Vec3 v;
    mats::Vec3 z(1.0, 2.0, 3.0);
    mats::Vec3 y(3.0, 2.8, 9.1);

    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    return a.exec();
}
