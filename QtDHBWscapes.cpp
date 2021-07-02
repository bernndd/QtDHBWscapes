#include "QtDHBWscapes.h"

QtDHBWscapes::QtDHBWscapes(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.pushButton->setStyleSheet("border-image:url(D://DHBW//Privat//gehirn.png);");
}
