#include "Spielfeld.h"



Spielfeld::Spielfeld(bool val)
{
	/*belegung.resize(fieldSize, vector<int>(fieldSize));*/
	srand(time(0));
	//initialisierung der Belegung zu Beginn NEU
	for (int i = 0; i < fieldSize; i++)
	{
		for (int j = 0; j < fieldSize; j++)
		{
			belegung[i][j] = Stein(rand() % 5 + 1);
		}
	}

	initFieldCheck();

	fromX = -1;
	fromY = -1;
	toX = -1;
	toY = -1;
	timeLeft = 20;
	secondsSinceLastMove = 0;
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
/// Überprüft ob in einer Zeile ein Strike vorliegt
/// </summary>
/// <param name="update">true => Spielfeld wird aktualisiert</param>
/// <returns>Strikelänge</returns>
int Spielfeld::checkRowStrike(bool update)
{
	//WORKS!
	int count = 0;

	//Fängt an in der untersten Reihe zu Prüfen (Steine fallen nach unten)
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
					{
						calcPointsAndTime(belegung[i][j], count);
						updateField(i, j - 1, count, horizontal);
					}
					return count;
				}
				count = 1;
			}

			if (count == 5) //max. 5 Steine in einer Reihe möglich
			{
				if (update)
				{
					calcPointsAndTime(belegung[i][j], count);
					updateField(i, j - 1, count, horizontal);
				}
				return count;
			}
		}

		if (count > 2) //Zeile zu Ende aber mind. 3 Identische
		{
			if (update)
			{
				calcPointsAndTime(belegung[i][fieldSize - 1], count);
				updateField(i, fieldSize - 1, count, horizontal);
			}
			return count;
		}
	}

	return 0;
}

/// <summary>
/// Überprüft ob in einer Spalte ein Strike vorliegt
/// </summary>
/// <param name="update">true => Spielfeld wird aktualisiert</param>
/// <returns>Strikelänge</returns>
int Spielfeld::checkColStrike(bool update)
{
	//WORKS!
	int count = 0;

	for (int i = 0; i < fieldSize; i++) //Spalte
	{
		count = 1;
		for (int j = fieldSize - 1; j > 0; j--) //Zeile
		{
			if (belegung[j][i] == belegung[j - 1][i]) //übereinanderliegende Steine identisch
				count++;

			else //übereinanderliegende Steine verschieden
			{
				if (count > 2)
				{
					if (update)
					{
						calcPointsAndTime(belegung[j][i], count);
						updateField(j, i, count, vertikal);
					}
					return count;
				}
				count = 1;
			}

			if (count == 5) //max. 5 Steine in einer Reihe möglich
			{
				if (update)
				{
					calcPointsAndTime(belegung[j][i], count);
					updateField(j, i, count, vertikal);
				}
				return count;
			}
		}
		if (count > 2) //Spalte zu Ende aber mind. 3 Identische
		{
			if (update)
			{
				calcPointsAndTime(belegung[0][i], count);
				updateField(count - 1, i, count, vertikal);
			}
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
/// <param name="anz">= Strikelänge</param>
/// <param name="type">= horizontal/vertikal</param>
void Spielfeld::updateField(int x, int y, int anz, StrikeType type)
{
	if (type == horizontal)
	{
		int col = belegung[x][y];

		//Elemente der Zeile werden aktualisiert
		for (int i = 0; i < anz; i++)
		{
			belegung[x][y - i] = Stein(0);
		}

	}

	else if (type == vertikal)
	{
		//Elemente der Spalte y werden aktualisiert
		for (int i = 0; i < anz; i++)
		{
			belegung[x + i][y] = Stein(0);
		}
	}

	fillFieldAfterStrike();

}


/// <summary>
/// Lässt die Steine nachrutschen und füllt von oben auf
/// </summary>
void Spielfeld::fillFieldAfterStrike()
{
	//Neuen Stein nachschieben
	//srand(time(0));
	for (int i = 0; i < fieldSize; i++) //Spalte 0 = links
	{
		for (int j = fieldSize - 1; j >= 0; j--) //Zeile 0 = oben
		{
			if (j == 0 && belegung[j][i] == kein) //In der obersten Zeile werden neue Steine erzeugt falls Platz ist
			{
				belegung[j][i] = Stein(rand() % 5 + 1);
				j = fieldSize - 1;
			}

			else if (belegung[j][i] == kein) //ansonsten wird der Position der übergeordnete zugeordnet und dieser Platz frei gemacht
			{
				belegung[j][i] = belegung[j - 1][i];
				belegung[j - 1][i] = Stein(0);
			}
		}

	}
}


void Spielfeld::calcPointsAndTime(int farbe, int anz)
{
	punkte += anz;
	timeLeft += anz / level;
	if (timeLeft > 20)
		timeLeft = 20;
}