#include "Player.h"

Player::Player(string name, int punkte)
{
	Name = name;
	Points = punkte;
}

Player::operator int() {
	return Points;
}