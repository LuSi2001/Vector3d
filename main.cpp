#include "mainwindow.h"

#include <QApplication>
#include "vector.h"

using Vec3 = mats::Vector3<float>;

int main(int argc, char *argv[])
{
    Vec3    v;

    v * 1;


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
