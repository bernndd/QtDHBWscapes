#pragma once
#include "Stein.h"

class Bombe :
    public Stein
{
public:
    Bombe(int x, int y);
    void activateBomb(Spielfeld spielfeld);

private:
    int xKoordinate;
    int yKoordniate;
    Farbe color;
};
