#pragma once
#include "Stein.h"

class Rakete :
    public Stein
{
    //eine Reihe/Spalte wird entfernt
public:
    Rakete(StrikeType st);
    void Move(Spielfeld spielfeld, int fromX, int fromY, int toX, int toY);


private:
    StrikeType strikeType;
    Farbe color;
};


