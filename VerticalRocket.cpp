#include "Stein.h"

VerticalRocket::VerticalRocket()
{
	this->color = Color::rocketVertical;
}

void VerticalRocket::activate(Game* game, int x, int y)
{
	game->addTimeAndPoints(9 / (int)game->getLevel(), 20);

	//initializes the new row
	for (int i = 0; i < Game::fieldSize; i++)
	{

		game->occypency[i][y] = &Token(rand() % 5 + 1);
	}
	game->resetSavedCoordinates(true);
	Move(game);
}