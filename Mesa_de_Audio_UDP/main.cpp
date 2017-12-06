#include "mainwindow.h"
#include <QApplication>
//teste
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QStateMachine machine;
    MainWindow w;
    w.show();

    return a.exec();
}
