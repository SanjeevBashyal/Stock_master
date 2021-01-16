#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.set_req_ui(w.ui);
    w.defaults();
    w.show();
    return a.exec();
}
