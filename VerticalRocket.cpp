#include "Stein.h"

VerticalRocket::VerticalRocket()
{
	this->farbe = Farbe::raketeVertikal;
}

void VerticalRocket::activate(Spielfeld* game, int x, int y)
{
	game->timeLeft += (9 / game->level);
	game->punkte += 20;
	//initializes the new row
	for (int i = 0; i < Spielfeld::fieldSize; i++)
	{

		game->belegung[i][y] = &Stein(rand() % 5 + 1);
	}
	game->fromX = -1;
	game->fromY = -1;
	game->toX = -1;
	game->toY = -1;
	Move(game);
}