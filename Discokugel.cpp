#include "Discokugel.h"

Discokugel::Discokugel()
{
	this->color = Farbe::disco;
}

void Discokugel::activateDisco(Spielfeld spielfeld)
{
	//TODO Testen und Punkte berechnen

	for (int i = 0; i < Spielfeld::fieldSize; i++)
	{
		for (int j = 0; j < Spielfeld::fieldSize; j++)
		{
			if (spielfeld.belegung[i][j] == this->color)
			{
				spielfeld.belegung[i][j] = Stein(-1);
			}
		}
	}

	spielfeld.fillFieldAfterStrike();
}