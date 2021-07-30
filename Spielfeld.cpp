#include "Spielfeld.h"



Game::Game(string playername, Level level)
{
	srand(time(0));
	//new initialization of the grid
	for (int i = 0; i < fieldSize; i++)
	{
		for (int j = 0; j < fieldSize; j++)
		{
			int zahl = rand() % 5;
			zahl++;
			Token *temp = new Token(zahl);
			occypency[i][j] = temp;
		}
	}

	initFieldCheck();

	this->level = level;
	timeLeft = getTimeLimit();

	resetSavedCoordinates(true);
	points = 0;
	playerName = playername;
	readHighscoreFile();
}
/// <summary>
/// resets all saved coordinates of a token to -1
/// </summary>
/// <param name="resetAllCoordinates"></param>
void Game::resetSavedCoordinates(bool resetAllCoordinates) {
	fromX = -1;
	fromY = -1;
	if (resetAllCoordinates)
	{
		toX = -1;
		toY = -1;
	}
}

/// <summary>
/// basic set Method for X and Y Coordinates, destination setting
/// </summary>
/// <param name="toX"></param>
/// <param name="toY"></param>
void Game::setDestination(int toX, int toY)
{
	this->toX = toX;
	this->toY = toY;
}
/// <summary>
/// basic set Method for X and Y Coordinates to set the origin of a strike
/// </summary>
/// <param name="toX"></param>
/// <param name="toY"></param>
void Game::setRoot(int fromX, int fromY)
{
	this->fromX = fromX;
	this->fromY = fromY;
}
/// <summary>
/// updates the time and the points
/// </summary>
/// <param name="extraTime"></param>
/// <param name="extraPoints"></param>
void Game::addTimeAndPoints(int extraTime, int extraPoints)
{
	timeLeft += extraTime;
	points += extraPoints;
}


/// <summary>
/// deletes all strikes, which formed after randomly creating the field
/// </summary>
void Game::initFieldCheck()
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
int Game::checkRowStrike(bool update)
{
	int count = 0;

	//starts checking at the bottom row (tokens fall down)
	for (int i = fieldSize - 1; i >= 0; i--)
	{
		count = 1;
		for (int j = 1; j < fieldSize; j++)
		{
			if (occypency[i][j]->getColor() == occypency[i][j - 1]->getColor()) //neighbor tokens are similar
				count++;
			else //neighbor tokens are different
			{
				if (count > 2)
				{
					if (update)
					{
						calcPointsAndTime(occypency[i][j]->getColor(), count);
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
					calcPointsAndTime(occypency[i][j]->getColor(), count);
					updateField(i, j - 1, count, horizontal);
				}
				return count;
			}
		}

		if (count > 2) //end of row, but at least 3 matching
		{
			if (update)
			{
				calcPointsAndTime(occypency[i][fieldSize - 1]->getColor(), count);
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
int Game::checkColStrike(bool update)
{
	int count = 0;

	for (int i = 0; i < fieldSize; i++) //column
	{
		count = 1;
		for (int j = fieldSize - 1; j > 0; j--) //row
		{
			if (occypency[j][i]->getColor() == occypency[j - 1][i]->getColor()) //tokens on top of each other are similar
				count++;

			else //tokens on top of each other are different
			{
				if (count > 2)
				{
					if (update)
					{
						calcPointsAndTime(occypency[j][i]->getColor(), count);
						updateField(j, i, count, vertical);
					}
					return count;
				}
				count = 1;
			}

			if (count == 5) //max. 5 tokens possible in a row
			{
				if (update)
				{
					calcPointsAndTime(occypency[j][i]->getColor(), count);
					updateField(j, i, count, vertical);
				}
				return count;
			}
		}
		if (count > 2) //end of column, but at least 3 matching
		{
			if (update)
			{
				calcPointsAndTime(occypency[0][i]->getColor(), count);
				updateField(count - 1, i, count, vertical);
			}
			return count;
		}
	}

	return 0;
}

/// <summary>
/// inits the different time values for the different diffuiculty levels
/// </summary>
/// <returns></returns>
int Game::getTimeLimit()
{
	switch (level)
	{
	case Level::medium: return 10; break;
	case Level::hard: return 5; break;
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
void Game::updateField(int x, int y, int anz, StrikeType type)
{
	if (type == horizontal)
	{
		int col = occypency[x][y]->getColor();

		//update elements of row
		for (int i = 0; i < anz; i++)
		{
			Token *temp = new Token(0);
			occypency[x][y - i] = temp;
		}

	}

	else if (type == vertical)
	{
		//update elements of column
		for (int i = 0; i < anz; i++)
		{
			Token *temp = new Token(0);
			occypency[x + i][y] = temp;
		}
	}

	fillFieldAfterStrike();

}


/// <summary>
/// lets the tokens fall down and fills the grid at the top
/// </summary>
void Game::fillFieldAfterStrike()
{
	//adds new token
	for (int i = 0; i < fieldSize; i++) //column 0 = left
	{
		for (int j = fieldSize - 1; j >= 0; j--) //row 0 = top
		{
			if (j == 0 && occypency[j][i]->getColor() == kein) //if theres space at the top, fill it up
			{
				Token* temp = new Token(rand() % 5 + 1);
				occypency[j][i] = temp;
				j = fieldSize - 1;
			} 

			else if (occypency[j][i]->getColor() == kein) //otherwise the position will go to the token above and the token at the position will be deleted
			{
				occypency[j][i] = occypency[j - 1][i];
				Token* temp = new Token(0);
				occypency[j - 1][i] = temp;
			}
		}

	}
}

/// <summary>
/// Calculate Time and Points
/// </summary>
/// <param name="farbe"> </param>
/// <param name="anz"> number of strike (3,4,5)</param>
void Game::calcPointsAndTime(int farbe, int anz)
{
	switch (level)
	{
	case easy: timeLeft += 3; points += anz; break;
	case medium: timeLeft += 2; points += anz * 2; break;
	default: timeLeft++; points += anz * 3; break;
	}
	if (timeLeft > getTimeLimit())
		timeLeft = getTimeLimit();
}

/// <summary>
/// Build Highscore list
/// </summary>
/// <returns> String with all Highscores </returns>
string Game::buildHighscoreList()
{
	string highscore = "";
	for (int i = 0; i < 10; i++)
		highscore.append(to_string(i + 1) + ". " + highscoreList[i].Name + " mit " + to_string(highscoreList[i].Points) + " erreichten Punkten!\n");

	return highscore;
}

/// <summary>
/// Read Data from Highscore Frame
/// </summary>
void Game::readHighscoreFile()
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

/// <summary>
/// Write Data to Highscore file
/// </summary>
void Game::writeHighscoreFile()
{

	sort(highscoreList.begin(), highscoreList.end(), greater<int>());
	ofstream output_file(FILE);

	for (int i = 0; i < 10; i++)
		output_file << highscoreList[i].Name << "-" << highscoreList[i].Points << endl;

	output_file.close();

}