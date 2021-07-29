#include "Stein.h"

Bomb::Bomb()
{
	this->farbe = Farbe::bombe;
}

void Bomb::activate(Spielfeld* game, int x, int y)
{
	//deletes token from origin
	game->belegung[x][y] = &Stein(0);
	game->addTimeAndPoints(9 / (int)game->getLevel(), 10);


	//deletes all tokens left from the origin
	if (x > 0)
	{
		game->belegung[x - 1][y] = &Stein(0);

		if (y > 0)
			game->belegung[x - 1][y - 1] = &Stein(0);

		if (y < Spielfeld::fieldSize - 1)
			game->belegung[x - 1][y + 1] = &Stein(0);
	}

	//deletes all tokens right from the origin
	if (x < Spielfeld::fieldSize - 1)
	{
		game->belegung[x + 1][y] = &Stein(0);

		if (y > 0)
			game->belegung[x + 1][y - 1] = &Stein(0);

		if (y < Spielfeld::fieldSize - 1)
			game->belegung[x + 1][y + 1] = &Stein(0);
	}

	//deletes all tokens in the middle above the origin
	if (y > 0)
		game->belegung[x][y - 1] = &Stein(0);

	//deletes all tokens in the middle under the origin
	if (y < Spielfeld::fieldSize - 1)
		game->belegung[x][y + 1] = &Stein(0);


	game->fillFieldAfterStrike();
	game->resetSavedCoordinates(true);
	Move(game);
}