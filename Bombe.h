#pragma once
#include "Stein.h"

class Bombe :
    public Stein
{
public:
    Bombe(int x, int y);
    void Move(class Spielfeld spielfeld, int fromX, int fromY, int toX, int toY) override;
    void activateBomb(Spielfeld spielfeld);

private:
    int xKoordinate;
    int yKoordniate;
    Farbe color;
};
