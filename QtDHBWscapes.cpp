#include "QtDHBWscapes.h"
#include <QPixmap>

//#include <time.h>


float dur = 20; // Spielzeit 

QtDHBWscapes::QtDHBWscapes(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//Connection Menubar
	InitMenu();
}

void QtDHBWscapes::InitMenu()
{
	connect(ui.startButton, SIGNAL(clicked()), this, SLOT(MenuStartPressed()));
	connect(ui.stoppButton, SIGNAL(clicked()), this, SLOT(MenuStoppPressed()));
	connect(ui.beendenButton, SIGNAL(clicked()), this, SLOT(exitGame()));
	connect(ui.hilfeButton, SIGNAL(clicked()), this, SLOT(MenuHelpPressed()));
}

void QtDHBWscapes::MenuStartPressed()
{

	game = new Spielfeld(true);
	game->level = Schwierigkeit(ui.schwierigkeit->value() + 1);
	initComponents();
	initField();
	ui.centralWidget->setLayout(field);
	game->timerId = startTimer(1000);
}
void QtDHBWscapes::MenuStoppPressed()
{

}
void QtDHBWscapes::MenuHelpPressed()
{


}

void QtDHBWscapes::exitGame()
{
	exit(0);
}

void QtDHBWscapes::initComponents()
{
	//test
	//Spielfläche
	field = new QGridLayout;
	QMargins margin(20, 100, 20, 20);
	field->setContentsMargins(margin);
	field->setHorizontalSpacing(6);
	field->setVerticalSpacing(6);
	field->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);

}

void QtDHBWscapes::initField()
{

	for (int i = 0; i < Spielfeld::fieldSize; i++)
	{
		for (int j = 0; j < Spielfeld::fieldSize; j++)
		{
			btnArray[i][j] = initButton(game->belegung[i][j], i, j);
			setButtonLayout(i, j);
			field->addWidget(btnArray[i][j], i, j);
		}
	}

	ui.centralWidget->setLayout(field);

}

void QtDHBWscapes::updateField()
{

	for (int i = 0; i < Spielfeld::fieldSize; i++)
	{
		for (int j = 0; j < Spielfeld::fieldSize; j++)
		{
			setButtonLayout(i, j);
		}
	}

}


void QtDHBWscapes::setButtonLayout(int x, int y)
{
	int color = game->belegung[x][y];

	switch (color)
	{
	case 1:  btnArray[x][y]->setStyleSheet(gruen_h); break;
	case 2: btnArray[x][y]->setStyleSheet(gelb_h); break;
	case 3: btnArray[x][y]->setStyleSheet(pink_h); break;
	case 4: btnArray[x][y]->setStyleSheet(blau_h); break;
	case 5: btnArray[x][y]->setStyleSheet(rot_h); break;
	case 6: btnArray[x][y]->setStyleSheet(disco_h); break;
	case 7: btnArray[x][y]->setStyleSheet(horizontal_h); break;
	case 8: btnArray[x][y]->setStyleSheet(vertikal_h); break;
	case 9: btnArray[x][y]->setStyleSheet(bombe_h); break;
		//case 3: temp->setIcon(QIcon(QPixmap(hellblau_h))); break;
	default: break;
	}
}

QPushButton* QtDHBWscapes::initButton(int color, int x, int y)
{
	QPushButton* temp = new QPushButton();
	temp->setFixedSize(QSize(35, 35));
	int position = x * Spielfeld::fieldSize + y;

	QSignalMapper* signalMapper = new QSignalMapper(this);
	connect(temp, SIGNAL(clicked()), signalMapper, SLOT(map()));
	signalMapper->setMapping(temp, position);
	connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(btnAction(int)));

	return temp;
}

void QtDHBWscapes::btnAction(int position)
{


	int x = position / Spielfeld::fieldSize;
	int y = position % Spielfeld::fieldSize;

	if (game->fromX == -1)
	{
		game->fromX = x;
		game->fromY = y;
		BorderButton(x, y);


		if (game->belegung[x][y] > Farbe::rot)
		{
			switch (Farbe(game->belegung[x][y]))
			{
			case Farbe::disco:
			{
				Stein(game->belegung[x][y]).activateDisco(game, x, y);
			}break;
			case Farbe::bombe:
			{
				Stein(game->belegung[x][y]).activateBomb(game, x, y);
			}break;
			case Farbe::raketeHorizontal:
			{
				Stein(game->belegung[x][y]).activateHorizontalRocket(game, x);
			}break;
			case Farbe::raketeVertikal:
			{
				Stein(game->belegung[x][y]).activateVerticalRocket(game, y);
			}break;
			default:break;
			}
			game->fromX = -1;
			game->fromY = -1;

			updateField();
		}
	}
	else
	{

		game->toX = x;
		game->toY = y;
		Stein(game->belegung[game->fromX][game->fromY]).Move(game);

		game->fromX = -1;
		game->fromY = -1;
		game->toX = -1;
		game->toY = -1;
		updateField();
	}

	//Punkte aktualisieren
	UpdatePoints();

}

void QtDHBWscapes::BorderButton(int x, int y)
{
	int color = game->belegung[x][y];

	switch (color)
	{
	case 1:  btnArray[x][y]->setStyleSheet(gruen_border); break;
	case 2: btnArray[x][y]->setStyleSheet(gelb_border); break;
	case 3: btnArray[x][y]->setStyleSheet(pink_border); break;
	case 4: btnArray[x][y]->setStyleSheet(blau_border); break;
	case 5: btnArray[x][y]->setStyleSheet(rot_border); break;
	case 6: btnArray[x][y]->setStyleSheet(disco_border); break;
	case 7: btnArray[x][y]->setStyleSheet(horizontal_border); break;
	case 8: btnArray[x][y]->setStyleSheet(vertikal_border); break;
	case 9: btnArray[x][y]->setStyleSheet(bombe_border); break;
		//case 3: temp->setIcon(QIcon(QPixmap(hellblau_h))); break;
	default: break;
	}
}

//QtDHBWscapes::~QtDHBWscapes()
//{
//killTimer(game->timerId);
//}

void QtDHBWscapes::timerEvent(QTimerEvent* event)//Is executed everytime the timer triggers
{
	game->secondsSinceLastMove++;
	if (game->secondsSinceLastMove == 5)
	{
		/*
		*
		* Problem ist, dass er nur checkt ob ein Strike vorliegt und nicht dass er guckt ob eine MÖGLICH WÄRE
		if (game->checkColStrike(false) == 0 && game->checkRowStrike(false) == 0) //TODO Testen
		{
			//Fenster Spielende
			endBox = new QMessageBox(this);
			endBox->setText("Keine Spielzüge mehr möglich!");
			//endBox->setIconPixmap(QPixmap("TimesUp.png"));
			endBox->exec();
		}
		#*/
	}
	ui.progressBar->setValue(int((float(game->timeLeft) / dur) * 100));
	game->timeLeft--;
	if (game->timeLeft == 0)
	{
		endBox = new QMessageBox(this);
		endBox->setText("Zeit abgelaufen!");
		//endBox->setIconPixmap(QPixmap("TimesUp.png"));
		endBox->exec();
	}

	//TODO Anzeige in Menüleiste aktualisieren



}



void QtDHBWscapes::UpdatePoints()
{
	if (ui.lcdNumber->checkOverflow(game->punkte))
	{
		int digit = ui.lcdNumber->digitCount();
		ui.lcdNumber->setDigitCount(digit + 2);
		ui.lcdNumber->display(game->punkte);
		ui.lcdNumber->setSegmentStyle(QLCDNumber::Filled);
	}
	else
	{

		ui.lcdNumber->display(game->punkte);
	}



}
