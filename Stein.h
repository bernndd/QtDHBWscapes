#pragma once
#include "Spielfeld.h"

enum Farbe {
	kein = 0,
	gruen = 1,
	gelb = 2,
	pink = 3,
	blau = 4,
	rot = 5,
	disco = 6, //eine farbe wird entfernt
	raketeHorizontal = 7,// eine Zeile wird entfernt
	raketeVertikal = 8,// eine Spalte wird entfernt
	bombe = 9,//entfernt unmittelbar umliegenden Steine

};

class Stein
{
public:
	Stein();
	Stein(int color);
	operator int();
	void Move(class Spielfeld spielfeld, int fromX, int fromY, int toX, int toY);


private:
	Farbe farbe;
};
