#pragma once
#include "Spielfeld.h"
#include <QPushButton>

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
	//QPushButton* Button;

	void activateBomb(class Spielfeld* spielfeld, int x, int y);
	void activateDisco(class Spielfeld* spielfeld, int x, int y);
	void activateVerticalRocket(class Spielfeld* game, int y);
	void activateHorizontalRocket(class Spielfeld* game, int x);
	virtual void Move(class Spielfeld* spielfeld);


private:
	Farbe farbe;
};
