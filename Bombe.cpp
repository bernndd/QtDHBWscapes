#include "Bombe.h"

void Bombe::activateBomb(Spielfeld game)
{
	int x = this->xKoordinate;
	int y = this->yKoordniate;

	//Entfernt Stein am Ursprung
	game.belegung[x][y] = Stein(-1);

	//Entfernt alle Steine links vom Ursprung
	if (x > 0)
	{
		game.belegung[x - 1][y] = Stein(-1);

		if (y > 0)
			game.belegung[x - 1][y - 1] = Stein(-1);

		if (y < Spielfeld::fieldSize - 1)
			game.belegung[x - 1][y + 1] = Stein(-1);
	}

	//Entfernt alle Steine rechts vom Ursprung
	if (x < Spielfeld::fieldSize - 1)
	{
		game.belegung[x + 1][y] = Stein(-1);

		if (y > 0)
			game.belegung[x + 1][y - 1] = Stein(-1);

		if (y < Spielfeld::fieldSize - 1)
			game.belegung[x + 1][y + 1] = Stein(-1);
	}

	//Entfernt Stein mittig über Ursprung
	if (y > 0)
		game.belegung[x][y - 1] = Stein(-1);

	//Entfernt Stein mittig unter Ursprung
	if (y < Spielfeld::fieldSize - 1)
		game.belegung[x][y + 1] = Stein(-1);
}