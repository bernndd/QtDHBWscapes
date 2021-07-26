#include "Player.h"

Player::Player(string name, int punkte)
{
	Name = name;
	Punkte = punkte;
}

Player::operator int() {
	return Punkte;
}