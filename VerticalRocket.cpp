#include "Stein.h"

VerticalRocket::VerticalRocket()
{
	this->farbe = Farbe::raketeVertikal;
}

void VerticalRocket::activate(Spielfeld* game, int x, int y)
{
	game->addTimeAndPoints(9 / (int)game->getLevel(), 20);

	//initializes the new row
	for (int i = 0; i < Spielfeld::fieldSize; i++)
	{

		game->belegung[i][y] = &Stein(rand() % 5 + 1);
	}
	game->resetSavedCoordinates(true);
	Move(game);
}