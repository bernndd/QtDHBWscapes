#pragma once
#include "Spielfeld.h"

enum Farbe {
	kein = 0,
	gruen = 1,
	gelb = 2,
	pink = 3,
	blau = 4,
	rot = 5,
	disco = 6, //one color gets deleted
	raketeHorizontal = 7,// one row gets deleted
	raketeVertikal = 8,// one column gets deleted
	bombe = 9,//explodes, and deletes nearby tokens

};

class Stein
{
public:
	Stein();
	Stein(int color);

	int getColor() { return farbe; };

	virtual void activate(class Spielfeld* spielfeld, int x, int y) {}
	virtual void Move(class Spielfeld* spielfeld);


protected:
	Farbe farbe;
};

class VerticalRocket : public Stein 
{
public:
	VerticalRocket();
	void activate(class Spielfeld* spielfeld, int x, int y) override;
};

class HorizontalRocket : public Stein
{
public:
	HorizontalRocket();
	void activate(class Spielfeld* spielfeld, int x, int y) override;
};

class Bomb : public Stein
{
public:
	Bomb();
	void activate(class Spielfeld* spielfeld, int x, int y) override;
};

class Disco : public Stein
{
public:
	Disco();
	void activate(class Spielfeld* spielfeld, int x, int y) override;
};