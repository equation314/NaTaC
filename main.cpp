#include "mainwindow.h"

#include <QTime>
#include <QApplication>

int main(int argc, char *argv[])
{
    qsrand(QTime::currentTime().msecsSinceStartOfDay());

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
