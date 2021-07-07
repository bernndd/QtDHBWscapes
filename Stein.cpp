#include "Stein.h"
#include "Rakete.h"
#include "Discokugel.h"
#include "Bombe.h"

Stein::Stein() {}

Stein::Stein(int color)
{
	color++;
	this->farbe = (Farbe)color;
}

Stein::operator int()
{
	return this->farbe;
}

void Stein::Move(Spielfeld spielfeld, int fromX, int fromY, int toX, int toY)
{
	if ((((fromX - toX) >= -1 && (fromX - toX) <= 1) && (fromY == toY)) || //Tauschen X Koordinate überprüfen
		((((fromY - toY) >= -1 && (fromY - toY) <= 1)) && (fromX == toX))) //Tauschen Y Koordinate überprüfen
	{
		//Steine probeweise vertauschen und überprüfen ob dann ein Strike vorliegt
		Stein temp = spielfeld.belegung[fromX][fromY];
		spielfeld.belegung[fromX][fromY] = spielfeld.belegung[toX][toY];
		spielfeld.belegung[toX][toY] = temp;

		int col = 0, row = 0;
		row = spielfeld.checkRowStrike(false);
		col = spielfeld.checkColStrike(false);

		//Zurücktauschen falls kein Strike vorliegt
		if (col == 0 && row == 5)
		{
			spielfeld.belegung[toX][toY] = spielfeld.belegung[fromX][fromY];
			spielfeld.belegung[fromX][fromY] = temp;
		}

		else
		{
			if (row == 5 || col == 5)
			{
				//Entferne Strike und positioniere Discokugel
				spielfeld.checkRowStrike(true);
				spielfeld.checkColStrike(true);
				spielfeld.belegung[toX][toY] = Discokugel();
			}

			else if (row == 4 || col == 4)
			{
				//Entferne Strike und positioniere Rakete
				spielfeld.checkRowStrike(true);
				spielfeld.checkColStrike(true);
				if (row == 4)
					spielfeld.belegung[toX][toY] = Rakete(StrikeType::horizontal);
				else
					spielfeld.belegung[toX][toY] = Rakete(StrikeType::vertikal);
			}

			else if (row == 3 && col == 3)
			{
				//Entferne Strike und positioniere Bombe

				//Zwischenspeicherung der Strikefarbe und entfernen des Zeilenstrikes
				int temp = spielfeld.belegung[toX][toY];
				spielfeld.checkRowStrike(true);

				//Füge an Schnittstelle gleichen Stein wieder ein damit Spaltenstrike auch entfernt wird
				spielfeld.belegung[toX][toY] = temp;
				spielfeld.checkColStrike(true);
				spielfeld.belegung[toX][toY] = Bombe(toX, toY);
			}

			else if (row == 3)
				spielfeld.checkRowStrike(true);
			else if (col == 3)
				spielfeld.checkColStrike(true);

			Move(spielfeld, 0, 0, 0, 0); //rekursiver Aufruf, da sich ein neuer Strike ergeben haben könnte.
		}

	}
	else
	{
		//TODO Exception werfen
	}
}