#pragma once
#include "Stein.h"
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <QPushButton>
#include <string>
#include <QTimer>

using namespace std;

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
	int secondsSinceLastMove;
	int timeLeft;
	Schwierigkeit level;

	int fromX;
	int fromY;
	int toX;
	int toY;


	Spielfeld(bool val);
	static const int fieldSize = 12;

	void updateField(int x, int y, int anz, StrikeType type);
	void calcPointsAndTime(int farbe, int anz);
	void fillFieldAfterStrike();

	int checkRowStrike(bool update);
	int checkColStrike(bool update);

private:
	void initFieldCheck();
};

