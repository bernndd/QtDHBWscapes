#include "Stein.h"

Disco::Disco()
{
	this->farbe = Farbe::disco;
}

void Disco::activate(Spielfeld* game, int x, int y)
{
	//chooses a random color and deletes every token of that color in the game
	int color = rand() % 5 + 1;

	game->addTimeAndPoints(12 / (int)game->getLevel(), 50);


	for (int i = 0; i < Spielfeld::fieldSize; i++)
	{
		for (int j = 0; j < Spielfeld::fieldSize; j++)
		{
			if (game->belegung[i][j]->getColor() == color)
			{
				game->belegung[i][j] = &Stein(0);
			}
		}
	}

	//delete disco ball
	game->belegung[x][y] = &Stein(0);

	game->fillFieldAfterStrike();
	game->resetSavedCoordinates(true);
	Move(game);
}