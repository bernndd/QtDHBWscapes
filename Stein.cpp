#include "Stein.h"


Token::Token() {}

Token::Token(int color)
{
	this->color = (Color)color;
}


/// <summary>
/// Return color number
/// </summary>
/// <returns></returns>
int Token::getColor()
{
	return this->color;
}

/// <summary>
/// Move Stone to new position
/// </summary>
/// <param name="spielfeld"></param>
void Token::Move(Game* spielfeld)
{
	int fromX = spielfeld->getFromX();
	int fromY = spielfeld->getFromY();
	int toX = spielfeld->getToX();
	int toY = spielfeld->getToY();

	if ((((fromX - toX) >= -1 && (fromX - toX) <= 1) && (fromY == toY)) || //checks if token is in range x coordinate
		((((fromY - toY) >= -1 && (fromY - toY) <= 1)) && (fromX == toX))) //and here for the y coordinate
	{
		
		//swap tokens and test if there´s a strike
		Token* temp = spielfeld->occypency[fromX][fromY];
		spielfeld->occypency[fromX][fromY] = spielfeld->occypency[toX][toY];
		spielfeld->occypency[toX][toY] = temp;

		int col = 0, row = 0;
		row = spielfeld->checkRowStrike(false);
		col = spielfeld->checkColStrike(false);

		//swap back if ther´s no strike
		if (col == 0 && row == 0)
		{
			spielfeld->occypency[toX][toY] = spielfeld->occypency[fromX][fromY];
			spielfeld->occypency[fromX][fromY] = temp;
		}

		else
		{

			if (row == 5 || col == 5)
			{
				//delete tokens and place disco ball
				spielfeld->checkRowStrike(true);
				spielfeld->checkColStrike(true);
				Disco* temp = new Disco();
				spielfeld->occypency[toX][toY] = temp;
			}

			else if (row == 4 || col == 4)
			{
				//delete tokens and place rocket
				spielfeld->checkRowStrike(true);
				spielfeld->checkColStrike(true);
				if (row == 4)
				{
					VerticalRocket* temp = new VerticalRocket();
					spielfeld->occypency[toX][toY] = temp;
				}
				else
				{
					HorizontalRocket* temp = new HorizontalRocket();
					spielfeld->occypency[toX][toY] = temp;
				}
			}

			else if (row == 3 && col == 3)
			{
				//delete tokens and place bomb

				//caches the strike color and deletes the row strike
				Token* temp = spielfeld->occypency[toX][toY];
				spielfeld->checkRowStrike(true);

				//adds a token of the same color where they cross, so that the column strike gets deleted as well
				spielfeld->occypency[toX][toY] = temp;
				spielfeld->checkColStrike(true);
				Bomb* temp2 = new Bomb();
				spielfeld->occypency[toX][toY] = temp2;
			}

			else if (row == 3)
				spielfeld->checkRowStrike(true);
			else if (col == 3)
				spielfeld->checkColStrike(true);


			spielfeld->resetSavedCoordinates(true);
			Move(spielfeld); //recursive call, because there could be a new strike
		}

	}
}


