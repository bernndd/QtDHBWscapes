#include "Stein.h"
#include <string>

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

	if ((((fromX - toX) >= -1 && (fromX - toX) <= 1) && (fromY == toY)) || //Tauschen X Koordinate �berpr�fen
		((((fromY - toY) >= -1 && (fromY - toY) <= 1)) && (fromX == toX))) //Tauschen Y Koordinate �berpr�fen
	{
		//Steine probeweise vertauschen und �berpr�fen ob dann ein Strike vorliegt
		Stein temp = spielfeld->belegung[fromX][fromY];
		spielfeld->belegung[fromX][fromY] = spielfeld->belegung[toX][toY];
		spielfeld->belegung[toX][toY] = temp;

		int col = 0, row = 0;
		row = spielfeld->checkRowStrike(false);
		col = spielfeld->checkColStrike(false);

		//Zur�cktauschen falls kein Strike vorliegt
		if (col == 0 && row == 0)
		{
			spielfeld->belegung[toX][toY] = spielfeld->belegung[fromX][fromY];
			spielfeld->belegung[fromX][fromY] = temp;
		}

		else
		{
			if (row == 5 || col == 5)
			{
				//Entferne Strike und positioniere Discokugel
				spielfeld->checkRowStrike(true);
				spielfeld->checkColStrike(true);
				spielfeld->belegung[toX][toY] = Stein(Farbe::disco);
			}

			else if (row == 4 || col == 4)
			{
				//Entferne Strike und positioniere Rakete
				spielfeld->checkRowStrike(true);
				spielfeld->checkColStrike(true);
				if (row == 4)
					spielfeld->belegung[toX - 1][toY] = Stein(Farbe::raketeHorizontal);
				else
					spielfeld->belegung[toX][toY] = Stein(Farbe::raketeVertikal);
			}

			else if (row == 3 && col == 3)
			{
				//Entferne Strike und positioniere Bombe

				//Zwischenspeicherung der Strikefarbe und entfernen des Zeilenstrikes
				int temp = spielfeld->belegung[toX][toY];
				spielfeld->checkRowStrike(true);

				//F�ge an Schnittstelle gleichen Stein wieder ein damit Spaltenstrike auch entfernt wird
				spielfeld->belegung[toX][toY] = temp;
				spielfeld->checkColStrike(true);
				//spielfeld.belegung[toX][toY] = Bombe::Bombe(toX, toY);
			}

			else if (row == 3)
				spielfeld->checkRowStrike(true);
			else if (col == 3)
				spielfeld->checkColStrike(true);


			spielfeld->fromX = -1;
			spielfeld->fromY = -1;
			spielfeld->toX = -1;
			spielfeld->toY = -1;
			Move(spielfeld); //rekursiver Aufruf, da sich ein neuer Strike ergeben haben k�nnte.
		}

	}
	else
	{
		//TODO Exception werfen
	}
}


void Stein::activateVerticalRocket(class Spielfeld* game, int y)
{
	//initialisiert direkt die Reihe neu
	for (int i = 0; i < Spielfeld::fieldSize; i++)
	{
		game->belegung[i][y] = Stein(rand() % 5 + 1);
	}
}

void Stein::activateHorizontalRocket(class Spielfeld* game, int x)
{
	//Entfernt Reihe und l�sst �bergeordnete nachfallen
	for (int i = 0; i < Spielfeld::fieldSize; i++)
	{
		game->belegung[x][i] = Stein(0);
	}
	game->fillFieldAfterStrike();
}

void Stein::activateDisco(Spielfeld* spielfeld, int x, int y)
{
	//Entfernt random eine Farbe komplett vom Spielfeld
	int color = rand() % 5 + 1;


	for (int i = 0; i < Spielfeld::fieldSize; i++)
	{
		for (int j = 0; j < Spielfeld::fieldSize; j++)
		{
			if (spielfeld->belegung[i][j] == color)
			{
				spielfeld->belegung[i][j] = Stein(0);
			}
		}
	}

	//Discokugel entfernen
	spielfeld->belegung[x][y] = Stein(0);

	spielfeld->fillFieldAfterStrike();
}

void Stein::activateBomb(Spielfeld* game, int x, int y)
{
	//Entfernt Stein am Ursprung
	game->belegung[x][y] = Stein(0);

	//Entfernt alle Steine links vom Ursprung
	if (x > 0)
	{
		game->belegung[x - 1][y] = Stein(0);

		if (y > 0)
			game->belegung[x - 1][y - 1] = Stein(0);

		if (y < Spielfeld::fieldSize - 1)
			game->belegung[x - 1][y + 1] = Stein(0);
	}

	//Entfernt alle Steine rechts vom Ursprung
	if (x < Spielfeld::fieldSize - 1)
	{
		game->belegung[x + 1][y] = Stein(0);

		if (y > 0)
			game->belegung[x + 1][y - 1] = Stein(0);

		if (y < Spielfeld::fieldSize - 1)
			game->belegung[x + 1][y + 1] = Stein(0);
	}

	//Entfernt Stein mittig �ber Ursprung
	if (y > 0)
		game->belegung[x][y - 1] = Stein(0);

	//Entfernt Stein mittig unter Ursprung
	if (y < Spielfeld::fieldSize - 1)
		game->belegung[x][y + 1] = Stein(0);


	game->fillFieldAfterStrike();
}