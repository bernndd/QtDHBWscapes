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

class Stein;

#define FILE "HighscoreList.txt"

enum Schwierigkeit
{
	easy = 1,
	medium = 2,
	hard = 3,
};

enum StrikeType {
	horizontal = 0,
	vertikal = 1,
};

class Spielfeld
{
public:
	static const int fieldSize = 12;

	Stein* belegung[12][12];
	vector<Player> highscoreList;

	Spielfeld(string playername, Schwierigkeit level);

	//Propertys
	Schwierigkeit getLevel() { return level; }
	string getPlayerName() { return playerName; }
	int getFromX() { return fromX; }
	int getFromY() { return fromY; };
	int getToX() { return toX; }
	int getToY() { return toY; }
	int getTimeLeft() {return timeLeft;}
	int getPoints() { return punkte; }
	int getTimeLimit();

	//Methoden
	void setDestination(int toX, int toY);
	void setRoot(int fromX, int fromY);
	void resetSavedCoordinates(bool resetAllCoordinates);
	void addTimeAndPoints(int extraTime, int extraPoints);
	void updateField(int x, int y, int anz, StrikeType type);
	void calcPointsAndTime(int farbe, int anz);
	void fillFieldAfterStrike();
	int checkRowStrike(bool update);
	int checkColStrike(bool update);
	void writeHighscoreFile();

private:
	int fromX;
	int fromY;
	int toX;
	int toY;
	int punkte;
	int timeLeft;
	Schwierigkeit level;
	string playerName;
	bool successRead;

	void initFieldCheck();
	void readHighscoreFile();
};

