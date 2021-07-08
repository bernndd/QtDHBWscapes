#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtDHBWscapes.h"

// Spielsteine definieren
#define rot_h "border-image:url(://QtDHBWscapes//Ohne Hintergrund//davis_rm.png);"
#define blau_h "border-image:url(://QtDHBWscapes//Ohne Hintergrund//blau_rm.png);"
#define hellblau_h "border-image:url(://QtDHBWscapes//Ohne Hintergrund//hellblau_rm.png);"
#define gruen_h "border-image:url(://QtDHBWscapes//Ohne Hintergrund//gruen_rm.png);"
#define pink_h "border-image:url(://QtDHBWscapes//Ohne Hintergrund//pink_rm.png);"
#define gelb_h "border-image:url(://QtDHBWscapes//Ohne Hintergrund//gelb_rm.png);"
#define disco_h "border-image:url(://QtDHBWscapes//Ohne Hintergrund//disco_rm.png);"
#define bombe_h "border-image:url(://QtDHBWscapes//Ohne Hintergrund//bombe_rm.png);"
#define horizontal_h "border-image:url(://QtDHBWscapes//Ohne Hintergrund//horizontal_rm.png);"
#define vertikal_h "border-image:url(://QtDHBWscapes//Ohne Hintergrund//vertikal_rm.png);"

class QtDHBWscapes : public QMainWindow
{
    Q_OBJECT

public:
    QtDHBWscapes(QWidget *parent = Q_NULLPTR);
    void ColorButton(int color, int y, int x);
    void setConnectionFromButtons();
    QPushButton* GetButtonByCoords(int y, int x);

private slots:
    void ButtonClicked();
    ~QtDHBWscapes();

private: 
    Ui::QtDHBWscapesClass ui;
    int timerId;

protected:
    void timerEvent(QTimerEvent* event);
};
