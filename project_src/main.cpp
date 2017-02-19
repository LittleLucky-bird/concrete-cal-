#include "mainwindow.h"
#include <QApplication>
#include <QPaintEvent>
#include <QPainter>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
