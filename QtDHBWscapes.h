#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtDHBWscapes.h"

// Spielsteine definieren
#define rot "border-image:url(D://DHBW//2. Semester//06_Programmieren//01_Programmieraufgabe//04_Bilder//Ohne Hintergrund//davis_rm.png);"
#define blau "border-image:url(D://DHBW//2. Semester//06_Programmieren//01_Programmieraufgabe//04_Bilder//Ohne Hintergrund//blau_rm.png);"
#define hellblau "border-image:url(D://DHBW//2. Semester//06_Programmieren//01_Programmieraufgabe//04_Bilder//Ohne Hintergrund//hellblau_rm.png);"
#define gruen "border-image:url(D://DHBW//2. Semester//06_Programmieren//01_Programmieraufgabe//04_Bilder//Ohne Hintergrund//gruen_rm.png);"
#define pink "border-image:url(D://DHBW//2. Semester//06_Programmieren//01_Programmieraufgabe//04_Bilder//Ohne Hintergrund//pink_rm.png);"
#define gelb "border-image:url(D://DHBW//2. Semester//06_Programmieren//01_Programmieraufgabe//04_Bilder//Ohne Hintergrund//gelb_rm.png);"
#define disco "border-image:url(D://DHBW//2. Semester//06_Programmieren//01_Programmieraufgabe//04_Bilder//Ohne Hintergrund//disco_rm.png);"
#define bombe "border-image:url(D://DHBW//2. Semester//06_Programmieren//01_Programmieraufgabe//04_Bilder//Ohne Hintergrund//bombe_rm.png);"
#define horizontal "border-image:url(D://DHBW//2. Semester//06_Programmieren//01_Programmieraufgabe//04_Bilder//Ohne Hintergrund//horizontal_rm.png);"
#define vertikal "border-image:url(D://DHBW//2. Semester//06_Programmieren//01_Programmieraufgabe//04_Bilder//Ohne Hintergrund//vertikal_rm.png);"

class QtDHBWscapes : public QMainWindow
{
    Q_OBJECT

public:
    QtDHBWscapes(QWidget *parent = Q_NULLPTR);
    void ColorButton(int color, int y, int x);

private:
    Ui::QtDHBWscapesClass ui;
};
