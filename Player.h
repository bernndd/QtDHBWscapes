#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;


class Player
{
public:
	string Name;
	int Punkte;
	Player(string name, int punkte);
	operator int();
};

