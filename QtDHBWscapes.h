#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtDHBWscapes.h"
#include "Spielfeld.h"
#include <QPushButton>
#include <QGridLayout>
#include <QSignalMapper>
#include <QMessageBox>

// define tokens
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

//tokens with border
#define rot_border "border-image:url(rot_border.png);"
#define blau_border "border-image:url(blau_border.png);"
#define hellblau_border "border-image:url(hellblau_border.png);"
#define gruen_border "border-image:url(gruen_border.png);"
#define pink_border "border-image:url(pink_border.png);"
#define gelb_border "border-image:url(gelb_border.png);"
#define disco_border "border-image:url(disco_border.png);"
#define bombe_border "border-image:url(bombe_border.png);"
#define horizontal_border "border-image:url(horizontal_border.png);"
#define vertikal_border "border-image:url(vertikal_border.png);"

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
    void showGameResult();
    void initField();
    void updateField();
    void setButtonLayout(int x, int y);
    void initComponents();


    void cleanGrid();
    void InitMenu();
    void BorderButton(int x, int y);
    void UpdatePoints();
<<<<<<< HEAD

    bool paused;
    int timerId;
=======
>>>>>>> 8316ab60b817132bd41aa68591c5437b830cd7b6
    

private slots:
    void btnAction(int position);
    void exitGame();
    void MenuStartPressed();
    void MenuStoppPressed();
    void MenuHelpPressed();
    void editTimeValues(int value);
};
