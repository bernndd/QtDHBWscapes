#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtDHBWscapes.h"
#include "Spielfeld.h"
#include <QPushButton>
#include <QGridLayout>
#include <QSignalMapper>
#include <QMessageBox>

// Spielsteine definieren
#define rot_h "border-image:url(rot_rm.png);"
#define blau_h "border-image:url(blau_rm.png);"
#define hellblau_h "border-image:url(hellblau_rm.png);"
#define gruen_h "border-image:url(gruen_rm.png);"
#define pink_h "border-image:url(pink_rm.png);"
#define gelb_h "border-image:url(gelb_rm.png);"
#define disco_h "border-image:url(disco_rm.png);"
#define bombe_h "border-image:url(bombe_rm.png);"
#define horizontal_h "border-image:url(horizontal_rm.png);"
#define vertikal_h "border-image:url(vertikal_rm.png);"

class QtDHBWscapes : public QMainWindow
{
    Q_OBJECT

public:
    QtDHBWscapes(QWidget *parent = Q_NULLPTR);
    

private: 
    Ui::QtDHBWscapesClass ui;
    Spielfeld* game;
    QPushButton* btnArray[12][12];
    QGridLayout* field;
    QMessageBox* endBox;

    QPushButton* initButton(int color, int x, int y);
    void timerEvent(QTimerEvent* event);
    void initField();
    void updateField();
    void setButtonLayout(int x, int y);
    void initComponents();


private slots:
    void btnAction(int position);
};
