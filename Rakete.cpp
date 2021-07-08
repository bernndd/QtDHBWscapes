#include "Rakete.h"

Rakete::Rakete(StrikeType st)
{
	this->strikeType = st;

	this->color = (st == StrikeType::vertikal) ? Farbe::raketeVertikal : Farbe::raketeHorizontal;
}

void Rakete::Move(Spielfeld spielfeld, int fromX, int fromY, int toX, int toY)
{
	if ((((fromX - toX) >= -1 && (fromX - toX) <= 1) && (fromY == toY)) ||  //Tauschen X Koordinate überprüfen
		((((fromY - toY) >= -1 && (fromY - toY) <= 1)) && (fromX == toX)))  //Tauschen Y Koordinate überprüfen
	{
		//Steine vertauschen
		Stein temp = spielfeld.belegung[fromX][fromY];
		spielfeld.belegung[fromX][fromY] = spielfeld.belegung[toX][toY];
		spielfeld.belegung[toX][toY] = temp;


		//Zeile bzw. Spalte entfernen
		if (this->strikeType == StrikeType::horizontal)
		{
			for (int i = 0; i < Spielfeld::fieldSize; i++)
			{
				spielfeld.belegung[toX][i] = Stein(-1);
			}
		}
		else
		{
			for (int i = 0; i < Spielfeld::fieldSize; i++)
			{
				spielfeld.belegung[i][toY] = Stein(-1);
			}
		}

		spielfeld.fillFieldAfterStrike();
	}
}