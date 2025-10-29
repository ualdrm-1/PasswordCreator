#include "mainwindow.h"

#include <QApplication>
#include <QMainWindow>

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("Password Generator");

    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowIcon(QIcon(":/image/icon.png"));

    w.show();
    return a.exec();
}
