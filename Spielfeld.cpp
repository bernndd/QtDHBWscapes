#include "Spielfeld.h"



Spielfeld::Spielfeld(string playername, Schwierigkeit level)
{
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

	this->level = level;
	timeLeft = timeLimit();

	fromX = -1;
	fromY = -1;
	toX = -1;
	toY = -1;
	punkte = 0;
	playerName = playername;
	readHighscoreFile();
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

int Spielfeld::timeLimit()
{
	switch (level)
	{
	case Schwierigkeit::medium: return 10; break;
	case Schwierigkeit::hard: return 5; break;
	default: return 20; break;
		break;
	}
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
	switch (level)
	{
	case easy: timeLeft += 3; punkte += anz; break;
	case medium: timeLeft += 2; punkte += anz * 2; break;
	default: timeLeft++; punkte += anz * 3; break;
	}
	if (timeLeft > timeLimit())
		timeLeft = timeLimit();
}


void Spielfeld::readHighscoreFile()
{
	try
	{

		ifstream input_file(FILE);

		string zeile, player, points;


		while (input_file >> zeile)
		{
			player = zeile.substr(0, zeile.find("-"));
			points = zeile.substr(zeile.find("-") + 1, zeile.length());
			highscoreList.push_back(Player(player, stoi(points)));

		}
		input_file.close();
		successRead = true;
		sort(highscoreList.begin(), highscoreList.end(), greater<int>());
	}

	catch (exception) {}

}

void Spielfeld::writeHighscoreFile()
{

	sort(highscoreList.begin(), highscoreList.end(), greater<int>());
	ofstream output_file(FILE);

	for (int i = 0; i < 10; i++)
		output_file << highscoreList[i].Name << "-" << highscoreList[i].Punkte << endl;

	output_file.close();

}