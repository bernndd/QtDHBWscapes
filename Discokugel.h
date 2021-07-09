#pragma once
#include "Stein.h"

class Discokugel :
    public Stein
{
    //Eine Farbe wird entfernt
public:
    Discokugel();
    void Move(class Spielfeld spielfeld, int fromX, int fromY, int toX, int toY) override;
    void activateDisco(Spielfeld spielfeld);

private:
    Farbe color;
};


