#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;


class Player
{
public:
	Player(string name, int points);
	operator int();
	string Name;
	int Points;

};

