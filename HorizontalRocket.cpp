#include "Stein.h"

HorizontalRocket::HorizontalRocket()
{
	this->farbe = Farbe::raketeHorizontal;
}

void HorizontalRocket::activate(Spielfeld* game, int x, int y)
{
	game->addTimeAndPoints(9 / (int)game->getLevel(), 20);
	//deletes row and makes the token above fall down
	for (int i = 0; i < Spielfeld::fieldSize; i++)
	{
		game->belegung[x][i] = &Stein(0);
	}
	game->fillFieldAfterStrike();
	game->fromX = -1;
	game->fromY = -1;
	game->toX = -1;
	game->toY = -1;
	Move(game);
}