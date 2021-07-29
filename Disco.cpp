#include "Stein.h"

Disco::Disco()
{
	this->color = Color::disco;
}

void Disco::activate(Game* game, int x, int y)
{
	//chooses a random color and deletes every token of that color in the game
	int color = rand() % 5 + 1;

	game->addTimeAndPoints(12 / (int)game->getLevel(), 50);


	for (int i = 0; i < Game::fieldSize; i++)
	{
		for (int j = 0; j < Game::fieldSize; j++)
		{
			if (game->occypency[i][j]->getColor() == color)
			{
				game->occypency[i][j] = &Token(0);
			}
		}
	}

	//delete disco ball
	game->occypency[x][y] = &Token(0);

	game->fillFieldAfterStrike();
	game->resetSavedCoordinates(true);
	Move(game);
}