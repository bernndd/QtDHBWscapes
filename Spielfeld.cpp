#include "Spielfeld.h"



Spielfeld::Spielfeld(string playername, Schwierigkeit level)
{
	srand(time(0));
	//new initialization of the grid
	for (int i = 0; i < fieldSize; i++)
	{
		for (int j = 0; j < fieldSize; j++)
		{
			int zahl = rand() % 5;
			zahl++;
			Stein *temp = new Stein(zahl);
			belegung[i][j] = temp;
		}
	}

	initFieldCheck();

	this->level = level;
	timeLeft = getTimeLimit();

	fromX = -1;
	fromY = -1;
	toX = -1;
	toY = -1;
	punkte = 0;
	playerName = playername;
	readHighscoreFile();
}


void Spielfeld::addTimeAndPoints(int extraTime, int extraPoints)
{
	timeLeft += extraTime;
	punkte += extraPoints;
}

int Spielfeld::getTimeLeft() {
	return this->timeLeft;
}

/// <summary>
/// deletes all strikes, which formed after randomly creating the field
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
/// checks if theres a strike in the row
/// </summary>
/// <param name="update">true => grid is getting updated</param>
/// <returns>Strikelänge</returns>
int Spielfeld::checkRowStrike(bool update)
{
	int count = 0;

	//starts checking at the bottom row (tokens fall down)
	for (int i = fieldSize - 1; i >= 0; i--)
	{
		count = 1;
		for (int j = 1; j < fieldSize; j++)
		{
			if (belegung[i][j]->getColor() == belegung[i][j - 1]->getColor()) //neighbor tokens are similar
				count++;
			else //neighbor tokens are different
			{
				if (count > 2)
				{
					if (update)
					{
						calcPointsAndTime(belegung[i][j]->getColor(), count);
						updateField(i, j - 1, count, horizontal);
					}
					return count;
				}
				count = 1;
			}

			if (count == 5) //max. 5 tokens possible in row 
			{
				if (update)
				{
					calcPointsAndTime(belegung[i][j]->getColor(), count);
					updateField(i, j - 1, count, horizontal);
				}
				return count;
			}
		}

		if (count > 2) //end of row, but at least 3 matching
		{
			if (update)
			{
				calcPointsAndTime(belegung[i][fieldSize - 1]->getColor(), count);
				updateField(i, fieldSize - 1, count, horizontal);
			}
			return count;
		}
	}

	return 0;
}

/// <summary>
/// checks if there a strike in a column
/// </summary>
/// <param name="update">true => grid ist getting updated </param>
/// <returns>Strikelänge</returns>
int Spielfeld::checkColStrike(bool update)
{
	int count = 0;

	for (int i = 0; i < fieldSize; i++) //column
	{
		count = 1;
		for (int j = fieldSize - 1; j > 0; j--) //row
		{
			if (belegung[j][i]->getColor() == belegung[j - 1][i]->getColor()) //tokens on top of each other are similar
				count++;

			else //tokens on top of each other are different
			{
				if (count > 2)
				{
					if (update)
					{
						calcPointsAndTime(belegung[j][i]->getColor(), count);
						updateField(j, i, count, vertikal);
					}
					return count;
				}
				count = 1;
			}

			if (count == 5) //max. 5 tokens possible in a row
			{
				if (update)
				{
					calcPointsAndTime(belegung[j][i]->getColor(), count);
					updateField(j, i, count, vertikal);
				}
				return count;
			}
		}
		if (count > 2) //end of column, but at least 3 matching
		{
			if (update)
			{
				calcPointsAndTime(belegung[0][i]->getColor(), count);
				updateField(count - 1, i, count, vertikal);
			}
			return count;
		}
	}

	return 0;
}

string Spielfeld::getPlayerName() { return playerName; }

Schwierigkeit Spielfeld::getLevel() { return level; }

int Spielfeld::getPoints() { return punkte; }

int Spielfeld::getTimeLimit()
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
/// deletes all strikes
/// </summary>
/// <param name="x">= Zeile</param>
/// <param name="y">= Spalte</param>
/// <param name="anz">= Strikelänge</param>
/// <param name="type">= horizontal/vertikal</param>
void Spielfeld::updateField(int x, int y, int anz, StrikeType type)
{
	if (type == horizontal)
	{
		int col = belegung[x][y]->getColor();

		//update elements of row
		for (int i = 0; i < anz; i++)
		{
			Stein *temp = new Stein(0);
			belegung[x][y - i] = temp;
		}

	}

	else if (type == vertikal)
	{
		//update elements of column
		for (int i = 0; i < anz; i++)
		{
			Stein *temp = new Stein(0);
			belegung[x + i][y] = temp;
		}
	}

	fillFieldAfterStrike();

}


/// <summary>
/// lets the tokens fall down and fills the grid at the top
/// </summary>
void Spielfeld::fillFieldAfterStrike()
{
	//adds new token
	for (int i = 0; i < fieldSize; i++) //column 0 = left
	{
		for (int j = fieldSize - 1; j >= 0; j--) //row 0 = top
		{
			if (j == 0 && belegung[j][i]->getColor() == kein) //if theres space at the top, fill it up
			{
				Stein* temp = new Stein(rand() % 5 + 1);
				belegung[j][i] = temp;
				j = fieldSize - 1;
			} 

			else if (belegung[j][i]->getColor() == kein) //otherwise the position will go to the token above and the token at the position will be deleted
			{
				belegung[j][i] = belegung[j - 1][i];
				Stein* temp = new Stein(0);
				belegung[j - 1][i] = temp;
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
	if (timeLeft > getTimeLimit())
		timeLeft = getTimeLimit();
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