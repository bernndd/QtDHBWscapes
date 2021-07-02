#include "QtDHBWscapes.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtDHBWscapes w;
    w.show();
    return a.exec();
}
