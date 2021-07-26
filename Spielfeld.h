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
	int belegung[12][12];
	int punkte;
	int secondsLeft;
	int timerId;
	int timeLeft;
	Schwierigkeit level;
	string playerName;
	vector<Player> highscoreList;

	int fromX;
	int fromY;
	int toX;
	int toY;


	Spielfeld(string playername, Schwierigkeit level);
	static const int fieldSize = 12;

	int timeLimit();
	void updateField(int x, int y, int anz, StrikeType type);
	void calcPointsAndTime(int farbe, int anz);
	void fillFieldAfterStrike();

	int checkRowStrike(bool update);
	int checkColStrike(bool update);
	void writeHighscoreFile();

private:
	bool successRead;
	void initFieldCheck();
	void readHighscoreFile();
};

