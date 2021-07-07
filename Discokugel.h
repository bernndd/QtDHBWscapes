#pragma once
#include "Stein.h"

class Discokugel :
    public Stein
{
    //Eine Farbe wird entfernt
public:
    Discokugel();
    void activateDisco(Spielfeld spielfeld);

private:
    Farbe color;
};


