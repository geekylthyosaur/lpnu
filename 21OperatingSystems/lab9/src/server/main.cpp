#include "mainwindow.h"
#include "worker.h"

#include <QApplication>

char Worker::separator = '@';
char Worker::iseparator = '#';

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
