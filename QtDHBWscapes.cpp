#include "QtDHBWscapes.h"
#include "Spielfeld.h"
#include <time.h>

QtDHBWscapes::QtDHBWscapes(QWidget *parent)
    : QMainWindow(parent)
{
    srand(time(NULL));
    ui.setupUi(this);
    ui.Button_1_1->setStyleSheet(blau);
    ui.Button_1_2->setStyleSheet(bombe);
    ui.Button_1_3->setStyleSheet(disco);
    ui.Button_1_4->setStyleSheet(gelb);
    ui.Button_1_5->setStyleSheet(gruen);
    ui.Button_1_6->setStyleSheet(hellblau);
    ui.Button_1_7->setStyleSheet(horizontal);
    ui.Button_1_8->setStyleSheet(pink);
    ui.Button_1_9->setStyleSheet(rot);
    ui.Button_1_10->setStyleSheet(vertikal);
    
    Spielfeld game(true);

    //for (int i = 0; i < Spielfeld::fieldSize; i++)
    //{
    //    for (int j = 0; j < Spielfeld::fieldSize; j++)
    //    {
    //        ColorButton(Spielfeld::belegung.at(i).at(j), i, j);
    //    }
    //}

    for (int x = 1; x < 13; x++)
    {
        for (int y = 1; y < 13; y++)
        {
            int color = rand() % 10 + 1;
            ColorButton(color, y, x);

        }
    }

    for (int x = 1; x < 13; x++)
    {
        for (int y = 1; y < 13; y++)
        {
            int color = rand() % 10 + 1;
            ColorButton(color, y, x);
            
        }
    }
}

void  QtDHBWscapes::ColorButton(int color, int y, int x)
{
    QString Button = "Button_";
    if (x < 10)
    {
        Button.append(x + 48); //append(std::to_string(x));
    }
    else
    {
        Button.append("1");
        Button.append((x - 10) + 48);
    }
    Button.append("_");
    if (y < 10)
    {
        Button.append(y + 48);
    }
    else
    {
        Button.append("1");
        Button.append((y-10) + 48);
    }
    
    QPushButton* bt = ui.gridLayoutWidget->findChild<QPushButton*>(Button);
    if (bt != NULL)
    {
        switch (color)
        {
        case 1:
            bt->setStyleSheet(rot);
            break;
        case 2:
            bt->setStyleSheet(blau);
            break;
        case 3:
            bt->setStyleSheet(hellblau);
            break;
        case 4:
            bt->setStyleSheet(gruen);
            break;
        case 5:
            bt->setStyleSheet(pink);
            break;
        case 6:
            bt->setStyleSheet(gelb);
            break;
        case 7:
            bt->setStyleSheet(disco);
            break;
        case 8:
            bt->setStyleSheet(bombe);
            break;
        case 9:
            bt->setStyleSheet(horizontal);
            break;
        case 10:
            bt->setStyleSheet(vertikal);
            break;
        default:
            break;
        }
        
    }
}
