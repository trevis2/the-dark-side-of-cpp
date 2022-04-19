#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    #ifdef Q_OS_LINUX
    setlocale(LC_NUMERIC, "C");
    #endif
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
