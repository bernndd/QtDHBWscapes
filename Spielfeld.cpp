#include "Spielfeld.h"


Spielfeld::Spielfeld(bool val)
{
	srand(time(0));
	//initialisierung der Belegung zu Beginn NEU
	for (int i = 0; i < fieldSize; i++)
	{
		for (int j = 0; j < fieldSize; j++)
		{
			belegung[i][j] = Stein(rand() % 5);
		}
	}

	initFieldCheck();
	punkte = 0;
}


/// <summary>
/// Entfernt alle Strikes, die nach erstellen des randomisierten Spielfeldes entstanden sind
/// </summary>
void Spielfeld::initFieldCheck()
{
	int a = 1, b = 1;

	while (a > 0 || b > 0)
	{
		a = checkColStrike(true);
		b = checkRowStrike(true);
	}

}


/// <summary>
/// �berpr�ft ob in einer Zeile ein Strike vorliegt
/// </summary>
/// <param name="update">true => Spielfeld wird aktualisiert</param>
/// <returns>Strikel�nge</returns>
int Spielfeld::checkRowStrike(bool update)
{
	//WORKS!
	int count = 0;

	//F�ngt an in der untersten Reihe zu Pr�fen (Steine fallen nach unten)
	for (int i = fieldSize - 1; i >= 0; i--)
	{
		count = 1;
		for (int j = 1; j < fieldSize; j++)
		{
			if (belegung[i][j] == belegung[i][j - 1]) //nebeneinanderliegende Steine identisch
				count++;
			else //nebeneinanderliegende Steine verschieden
			{
				if (count > 2)
				{
					if (update)
						updateField(i, j - 1, count, horizontal);
					return count;
				}
				count = 1;
			}

			if (count == 5) //max. 5 Steine in einer Reihe m�glich
			{
				if (update)
					updateField(i, j - 1, count, horizontal);
				return count;
			}
		}

		if (count > 2) //Zeile zu Ende aber mind. 3 Identische
		{
			if (update)
				updateField(i, fieldSize - 1, count, horizontal);
			return count;
		}
	}

	return 0;
}

/// <summary>
/// �berpr�ft ob in einer Spalte ein Strike vorliegt
/// </summary>
/// <param name="update">true => Spielfeld wird aktualisiert</param>
/// <returns>Strikel�nge</returns>
int Spielfeld::checkColStrike(bool update)
{
	//WORKS!
	int count = 0;

	for (int i = 0; i < fieldSize; i++) //Spalte
	{
		count = 1;
		for (int j = fieldSize - 1; j > 0; j--) //Zeile
		{
			if (belegung[j][i] == belegung[j - 1][i]) //�bereinanderliegende Steine identisch
				count++;

			else //�bereinanderliegende Steine verschieden
			{
				if (count > 2)
				{
					if (update)
						updateField(j, i, count, vertikal);
					return count;
				}
				count = 1;
			}

			if (count == 5) //max. 5 Steine in einer Reihe m�glich
			{
				if (update)
					updateField(j, i, count, vertikal);
				return count;
			}
		}
		if (count > 2) //Spalte zu Ende aber mind. 3 Identische
		{
			if (update)
				updateField(count - 1, i, count, vertikal);
			return count;
		}
	}

	return 0;
}



/// <summary>
/// Entfernt die vorliegenden Strikes
/// </summary>
/// <param name="x">= Zeile</param>
/// <param name="y">= Spalte</param>
/// <param name="anz">= Strikel�nge</param>
/// <param name="type">= horizontal/vertikal</param>
void Spielfeld::updateField(int x, int y, int anz, StrikeType type)
{
	if (type == horizontal)
	{
		int col = belegung[x][y];

		//Elemente der Zeile werden aktualisiert
		for (int i = 0; i < anz; i++)
		{
			belegung[x][y - i] = Stein(-1);
		}

	}

	else if (type == vertikal)
	{
		//Elemente der Spalte y werden aktualisiert
		for (int i = 0; i < anz; i++)
		{
			belegung[x + i][y] = Stein(-1);
		}
	}

	fillFieldAfterStrike();

}


/// <summary>
/// L�sst die Steine nachrutschen und f�llt von oben auf
/// </summary>
void Spielfeld::fillFieldAfterStrike()
{
	//Neuen Stein nachschieben
	srand(time(0));
	for (int i = 0; i < fieldSize; i++) //Spalte 0 = links
	{
		for (int j = fieldSize - 1; j >= 0; j--) //Zeile 0 = oben
		{
			if (j == 0 && belegung[j][i] == kein) //In der obersten Zeile werden neue Steine erzeugt falls Platz ist
			{
				belegung[j][i] = Stein(rand() % 5);
				j = fieldSize - 1;
			}

			else if (belegung[j][i] == kein) //ansonsten wird der Position der �bergeordnete zugeordnet und dieser Platz frei gemacht
			{
				belegung[j][i] = belegung[j - 1][i];
				belegung[j - 1][i] = Stein(-1);
			}
		}

	}
}