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

	//Variablen mit benötigten Lese- und Schreibzugriff von Außen
	Stein* belegung[12][12];
	int punkte;
	int timeLeft;
	vector<Player> highscoreList;

	int fromX;
	int fromY;
	int toX;
	int toY;

	Spielfeld(string playername, Schwierigkeit level);

	//Get-Methoden
	string getPlayerName();
	Schwierigkeit getLevel();
	int getTimeLimit();

	//Logik-Methoden
	int checkRowStrike(bool update);
	int checkColStrike(bool update);
	void updateField(int x, int y, int anz, StrikeType type);
	void fillFieldAfterStrike();

	void calcPointsAndTime(int farbe, int anz);
	void resetSavedCoordinates();
	void writeHighscoreFile();

private:
	//Variablen mit max. Lesezugriff von Außen
	Schwierigkeit level;
	string playerName;
	bool successRead;

	//weitere Methoden
	void initFieldCheck();
	void readHighscoreFile();
};

