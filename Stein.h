#pragma once
#include "Spielfeld.h"

enum Color {
	// deleted token
	kein = 0, 

	//standard token
	green = 1,
	yellow = 2,
	pink = 3,
	blue = 4,
	red = 5,

	//special token
	disco = 6, //removes a random color
	rocketHorizontal = 7,// removes a row
	rocketVertical = 8,// removes a color
	bomb = 9, //removes the token around the bomb

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