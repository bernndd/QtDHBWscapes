#pragma once
#include "Stein.h"
#include <vector>
#include <stdlib.h>
#include <time.h>
using namespace std;

#define SIZEFIELD 12

enum StrikeType {
	horizontal = 0,
	vertikal = 1,
};

class Spielfeld
{
public:
	int belegung[12][12];
	int punkte;

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

