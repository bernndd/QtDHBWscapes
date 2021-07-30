#include "Stein.h"

Bomb::Bomb()
{
	this->color = Color::bomb;
}

/// <summary>
/// Activate Bomb and remove other blocks
/// </summary>
/// <param name="game"></param>
/// <param name="x"> Coordinate </param>
/// <param name="y"> Coordinate </param>
void Bomb::activate(Game* game, int x, int y)
{
	//deletes token from origin
	game->occypency[x][y] = &Token(0);
	game->addTimeAndPoints(9 / (int)game->getLevel(), 10);


	//deletes all tokens left from the origin
	if (x > 0)
	{
		game->occypency[x - 1][y] = &Token(0);

		if (y > 0)
			game->occypency[x - 1][y - 1] = &Token(0);

		if (y < Game::fieldSize - 1)
			game->occypency[x - 1][y + 1] = &Token(0);
	}

	//deletes all tokens right from the origin
	if (x < Game::fieldSize - 1)
	{
		game->occypency[x + 1][y] = &Token(0);

		if (y > 0)
			game->occypency[x + 1][y - 1] = &Token(0);

		if (y < Game::fieldSize - 1)
			game->occypency[x + 1][y + 1] = &Token(0);
	}

	//deletes all tokens in the middle above the origin
	if (y > 0)
		game->occypency[x][y - 1] = &Token(0);

	//deletes all tokens in the middle under the origin
	if (y < Game::fieldSize - 1)
		game->occypency[x][y + 1] = &Token(0);


	game->fillFieldAfterStrike();
	game->resetSavedCoordinates(true);
	Move(game);
}