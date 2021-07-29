#pragma once
#include "Stein.h"
#include "Player.h"
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <QPushButton>
#include <string>
#include <QTimer>

using namespace std;

class Token;

#define FILE "HighscoreList.txt"

enum Level
{
	easy = 1,
	medium = 2,
	hard = 3,
};

enum StrikeType {
	horizontal = 0,
	vertikal = 1,
};

class Game
{
public:
	static const int fieldSize = 12;

	Token* occypency[12][12];
	vector<Player> highscoreList;

	Game(string playername, Level level);

	//Properties
	Level getLevel() { return level; }
	string getPlayerName() { return playerName; }
	int getFromX() { return fromX; }
	int getFromY() { return fromY; };
	int getToX() { return toX; }
	int getToY() { return toY; }
	int getTimeLeft() {return timeLeft;}
	int getPoints() { return points; }
	int getTimeLimit();

	//Methoden
	void setDestination(int toX, int toY);
	void setRoot(int fromX, int fromY);
	void resetSavedCoordinates(bool resetAllCoordinates);
	void addTimeAndPoints(int extraTime, int extraPoints);
	void updateField(int x, int y, int anz, StrikeType type);
	void calcPointsAndTime(int farbe, int anz);
	void fillFieldAfterStrike();
	void writeHighscoreFile();
	int checkRowStrike(bool update);
	int checkColStrike(bool update);
	string buildHighscoreList();

private:
	int fromX;
	int fromY;
	int toX;
	int toY;
	int points;
	int timeLeft;
	Level level;
	string playerName;
	bool successRead;

	void initFieldCheck();
	void readHighscoreFile();
};

