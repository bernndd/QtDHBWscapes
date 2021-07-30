#pragma once
#include "Spielfeld.h"

enum Color {
	kein = 0,
	green = 1,
	yellow = 2,
	pink = 3,
	blue = 4,
	red = 5,
	disco = 6, //eine farbe wird entfernt
	rocketHorizontal = 7,// eine Zeile wird entfernt
	rocketVertical = 8,// eine Spalte wird entfernt
	bomb = 9,//entfernt unmittelbar umliegenden Steine

};

class Token
{
public:
	Token();
	Token(int color);
	int getColor();

	virtual void activate(class Game* spielfeld, int x, int y) {}
	virtual void Move(class Game* spielfeld);


protected:
	Color color;
};

class VerticalRocket : public Token 
{
public:
	VerticalRocket();
	void activate(class Game* spielfeld, int x, int y) override;
};

class HorizontalRocket : public Token
{
public:
	HorizontalRocket();
	void activate(class Game* spielfeld, int x, int y) override;
};

class Bomb : public Token
{
public:
	Bomb();
	void activate(class Game* spielfeld, int x, int y) override;
};

class Disco : public Token
{
public:
	Disco();
	void activate(class Game* spielfeld, int x, int y) override;
};