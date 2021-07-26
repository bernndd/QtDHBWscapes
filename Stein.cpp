#include "Stein.h"


Stein::Stein() {}

Stein::Stein(int color)
{
	this->farbe = (Farbe)color;
}


Stein::operator int()
{
	return this->farbe;
}

void Stein::Move(Spielfeld* spielfeld)
{
	int fromX = spielfeld->fromX;
	int fromY = spielfeld->fromY;
	int toX = spielfeld->toX;
	int toY = spielfeld->toY;

	if ((((fromX - toX) >= -1 && (fromX - toX) <= 1) && (fromY == toY)) || //checks if token is in range x coordinate
		((((fromY - toY) >= -1 && (fromY - toY) <= 1)) && (fromX == toX))) //and here for the y coordinate
	{
		
		//swap tokens and test if there´s a strike
		Stein temp = spielfeld->belegung[fromX][fromY];
		spielfeld->belegung[fromX][fromY] = spielfeld->belegung[toX][toY];
		spielfeld->belegung[toX][toY] = temp;

		int col = 0, row = 0;
		row = spielfeld->checkRowStrike(false);
		col = spielfeld->checkColStrike(false);

		//swap back if ther´s no strike
		if (col == 0 && row == 0)
		{
			spielfeld->belegung[toX][toY] = spielfeld->belegung[fromX][fromY];
			spielfeld->belegung[fromX][fromY] = temp;
		}

		else
		{
			spielfeld->secondsSinceLastMove = 0;

			if (row == 5 || col == 5)
			{
				//delete tokens and place disco ball
				spielfeld->checkRowStrike(true);
				spielfeld->checkColStrike(true);
				spielfeld->belegung[toX][toY] = Stein(Farbe::disco);
			}

			else if (row == 4 || col == 4)
			{
				//delete tokens and place rocket
				spielfeld->checkRowStrike(true);
				spielfeld->checkColStrike(true);
				if (row == 4)
					spielfeld->belegung[toX][toY] = Stein(Farbe::raketeVertikal);
				else
					spielfeld->belegung[toX][toY] = Stein(Farbe::raketeHorizontal);
			}

			else if (row == 3 && col == 3)
			{
				//delete tokens and place bomb

				//caches the strike color and deletes the row strike
				int temp = spielfeld->belegung[toX][toY];
				spielfeld->checkRowStrike(true);

				//adds a token of the same color where they cross, so that the column strike gets deleted as well
				spielfeld->belegung[toX][toY] = temp;
				spielfeld->checkColStrike(true);
				spielfeld->belegung[toX][toY] = Stein(Farbe::bombe);
			}

			else if (row == 3)
				spielfeld->checkRowStrike(true);
			else if (col == 3)
				spielfeld->checkColStrike(true);


			spielfeld->fromX = -1;
			spielfeld->fromY = -1;
			spielfeld->toX = -1;
			spielfeld->toY = -1;
			Move(spielfeld); //recursive call, because there could be a new strike
		}

	}
}


void Stein::activateVerticalRocket(class Spielfeld* game, int y)
{

	game->timeLeft += (9 / game->level);
	game->punkte += 20;
	//initializes the new row
	for (int i = 0; i < Spielfeld::fieldSize; i++)
	{
		
		game->belegung[i][y] = Stein(rand() % 5 + 1);
	}
	game->fromX = -1;
	game->fromY = -1;
	game->toX = -1;
	game->toY = -1;
	Move(game);
}

void Stein::activateHorizontalRocket(class Spielfeld* game, int x)
{
	game->timeLeft += (9 / game->level);
	game->punkte += 20;
	//deletes row and makes the token above fall down
	for (int i = 0; i < Spielfeld::fieldSize; i++)
	{
		game->belegung[x][i] = Stein(0);
	}
	game->fillFieldAfterStrike();
	game->fromX = -1;
	game->fromY = -1;
	game->toX = -1;
	game->toY = -1;
	Move(game);
}

void Stein::activateDisco(Spielfeld* game, int x, int y)
{
	//chooses a random color and deletes every token of that color in the game
	int color = rand() % 5 + 1;
	game->punkte += 50;
	game->timeLeft += (12/ game->level);

	for (int i = 0; i < Spielfeld::fieldSize; i++)
	{
		for (int j = 0; j < Spielfeld::fieldSize; j++)
		{
			if (game->belegung[i][j] == color)
			{
				game->belegung[i][j] = Stein(0);
			}
		}
	}

	//delete disco ball
	game->belegung[x][y] = Stein(0);

	game->fillFieldAfterStrike();
	game->fromX = -1;
	game->fromY = -1;
	game->toX = -1;
	game->toY = -1;
	Move(game);
}

void Stein::activateBomb(Spielfeld* game, int x, int y)
{
	//deletes token from origin
	game->belegung[x][y] = Stein(0);
	game->punkte += 10;
	game->timeLeft += (9 / game->level);

	//deletes all tokens left from the origin
	if (x > 0)
	{
		game->belegung[x - 1][y] = Stein(0);

		if (y > 0)
			game->belegung[x - 1][y - 1] = Stein(0);

		if (y < Spielfeld::fieldSize - 1)
			game->belegung[x - 1][y + 1] = Stein(0);
	}

	//deletes all tokens right from the origin
	if (x < Spielfeld::fieldSize - 1)
	{
		game->belegung[x + 1][y] = Stein(0);

		if (y > 0)
			game->belegung[x + 1][y - 1] = Stein(0);

		if (y < Spielfeld::fieldSize - 1)
			game->belegung[x + 1][y + 1] = Stein(0);
	}

	//deletes all tokens in the middle above the origin
	if (y > 0)
		game->belegung[x][y - 1] = Stein(0);

	//deletes all tokens in the middle under the origin
	if (y < Spielfeld::fieldSize - 1)
		game->belegung[x][y + 1] = Stein(0);


	game->fillFieldAfterStrike();
	game->fromX = -1;
	game->fromY = -1;
	game->toX = -1;
	game->toY = -1;
	Move(game);
}