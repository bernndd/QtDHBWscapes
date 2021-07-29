#include "Stein.h"


Stein::Stein() {}

Stein::Stein(int color)
{
	this->farbe = (Farbe)color;
}

int Stein::getColor()
{
	return this->farbe;
}

void Stein::Move(Spielfeld* spielfeld)
{
	int fromX = spielfeld->fromX;
	int fromY = spielfeld->fromY;
	int toX = spielfeld->toX;
	int toY = spielfeld->toY;

	if ((((fromX - toX) >= -1 && (fromX - toX) <= 1) && (fromY == toY)) || //checks if token is in range x coordinate
		((((fromY - toY) >= -1 && (fromY - toY) <= 1)) && (fromX == toX))) //and here for the y coordinate
	{
		
		//swap tokens and test if there´s a strike
		Stein* temp = spielfeld->belegung[fromX][fromY];
		spielfeld->belegung[fromX][fromY] = spielfeld->belegung[toX][toY];
		spielfeld->belegung[toX][toY] = temp;

		int col = 0, row = 0;
		row = spielfeld->checkRowStrike(false);
		col = spielfeld->checkColStrike(false);

		//swap back if ther´s no strike
		if (col == 0 && row == 0)
		{
			spielfeld->belegung[toX][toY] = spielfeld->belegung[fromX][fromY];
			spielfeld->belegung[fromX][fromY] = temp;
		}

		else
		{

			if (row == 5 || col == 5)
			{
				//delete tokens and place disco ball
				spielfeld->checkRowStrike(true);
				spielfeld->checkColStrike(true);
				Disco* temp = new Disco();
				spielfeld->belegung[toX][toY] = temp;
			}

			else if (row == 4 || col == 4)
			{
				//delete tokens and place rocket
				spielfeld->checkRowStrike(true);
				spielfeld->checkColStrike(true);
				if (row == 4)
				{
					VerticalRocket* temp = new VerticalRocket();
					spielfeld->belegung[toX][toY] = temp;
				}
				else
				{
					HorizontalRocket* temp = new HorizontalRocket();
					spielfeld->belegung[toX][toY] = temp;
				}
			}

			else if (row == 3 && col == 3)
			{
				//delete tokens and place bomb

				//caches the strike color and deletes the row strike
				Stein* temp = spielfeld->belegung[toX][toY];
				spielfeld->checkRowStrike(true);

				//adds a token of the same color where they cross, so that the column strike gets deleted as well
				spielfeld->belegung[toX][toY] = temp;
				spielfeld->checkColStrike(true);
				Bomb* temp2 = new Bomb();
				spielfeld->belegung[toX][toY] = temp2;
			}

			else if (row == 3)
				spielfeld->checkRowStrike(true);
			else if (col == 3)
				spielfeld->checkColStrike(true);


			spielfeld->fromX = -1;
			spielfeld->fromY = -1;
			spielfeld->toX = -1;
			spielfeld->toY = -1;
			Move(spielfeld); //recursive call, because there could be a new strike
		}

	}
}


