#include "Stein.h"

HorizontalRocket::HorizontalRocket()
{
	this->farbe = Farbe::raketeHorizontal;
}

void HorizontalRocket::activate(Spielfeld* game, int x, int y)
{
	game->timeLeft += (9 / game->getLevel());
	game->punkte += 20;
	//deletes row and makes the token above fall down
	for (int i = 0; i < Spielfeld::fieldSize; i++)
	{
		game->belegung[x][i] = &Stein(0);
	}
	game->fillFieldAfterStrike();
	game->resetSavedCoordinates();
	Move(game);
}