#include "Stein.h"

HorizontalRocket::HorizontalRocket()
{
	this->color = Color::rocketHorizontal;
}

/// <summary>
/// Active Rocket and remove horizontal line
/// </summary>
/// <param name="game"></param>
/// <param name="x"> Coordinate </param>
/// <param name="y"> Coordinate </param>
void HorizontalRocket::activate(Game* game, int x, int y)
{
	game->addTimeAndPoints(9 / (int)game->getLevel(), 20);
	//deletes row and makes the token above fall down
	for (int i = 0; i < Game::fieldSize; i++)
	{
		game->occypency[x][i] = &Token(0);
	}
	game->fillFieldAfterStrike();
	game->resetSavedCoordinates(true);
	Move(game);
}