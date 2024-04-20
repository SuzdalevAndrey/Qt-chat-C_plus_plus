#include "mainwindow.h"
#include "loginwindow.h"
#include <QApplication>
#include "QListWidget"
#include "qpushbutton.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
