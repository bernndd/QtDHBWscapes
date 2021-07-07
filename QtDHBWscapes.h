#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtDHBWscapes.h"

// Spielsteine definieren
#define rot "border-image:url(://QtDHBWscapes//Ohne Hintergrund//davis_rm.png);"
#define blau "border-image:url(://QtDHBWscapes//Ohne Hintergrund//blau_rm.png);"
#define hellblau "border-image:url(://QtDHBWscapes//Ohne Hintergrund//hellblau_rm.png);"
#define gruen "border-image:url(://QtDHBWscapes//Ohne Hintergrund//gruen_rm.png);"
#define pink "border-image:url(://QtDHBWscapes//Ohne Hintergrund//pink_rm.png);"
#define gelb "border-image:url(://QtDHBWscapes//Ohne Hintergrund//gelb_rm.png);"
#define disco "border-image:url(://QtDHBWscapes//Ohne Hintergrund//disco_rm.png);"
#define bombe "border-image:url(D://QtDHBWscapes//Ohne Hintergrund//bombe_rm.png);"
#define horizontal "border-image:url(://QtDHBWscapes//Ohne Hintergrund//horizontal_rm.png);"
#define vertikal "border-image:url(://QtDHBWscapes//Ohne Hintergrund//vertikal_rm.png);"

class QtDHBWscapes : public QMainWindow
{
    Q_OBJECT

public:
    QtDHBWscapes(QWidget *parent = Q_NULLPTR);
    void ColorButton(int color, int y, int x);

private: 
    Ui::QtDHBWscapesClass ui;

};
