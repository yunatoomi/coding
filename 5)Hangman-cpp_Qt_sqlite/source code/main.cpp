#include "mainwindow.h"
#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setMinimumHeight(300);
    w.setMaximumHeight(300);
    w.setMinimumWidth(400);
    w.setMaximumWidth(400);
    w.show();

    return a.exec();
}
