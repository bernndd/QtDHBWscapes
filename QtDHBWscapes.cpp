#include "QtDHBWscapes.h"
#include <QPixmap>



QtDHBWscapes::QtDHBWscapes(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	paused = false;

	//Connection Menubar
	InitMenu();
}

//init Button connections
void QtDHBWscapes::InitMenu()
{
	connect(ui.startButton, SIGNAL(clicked()), this, SLOT(MenuStartPressed()));
	connect(ui.stoppButton, SIGNAL(clicked()), this, SLOT(MenuStoppPressed()));
	connect(ui.beendenButton, SIGNAL(clicked()), this, SLOT(exitGame()));
	connect(ui.hilfeButton, SIGNAL(clicked()), this, SLOT(MenuHelpPressed()));
	connect(ui.schwierigkeit, SIGNAL(valueChanged(int)), this, SLOT(editTimeValues(int)));
}

void QtDHBWscapes::editTimeValues(int value)
{
	switch (value + 1)
	{
	case 2: ui.zeit->setText(QString::number(10) + "s"); break;
	case 3: ui.zeit->setText(QString::number(5) + "s"); break;
	default: ui.zeit->setText(QString::number(20) + "s"); break;
	}
}

//Startbutton pressed
void QtDHBWscapes::MenuStartPressed()
{
	ui.graphicsView->setVisible(false);

	//Read Player Name, convert it  and make the Textedit and the label invisible
	QString QName = ui.lineEdit->text();
	std::string name = QName.toLocal8Bit().constData();
	//init difficulty
	int level = ui.schwierigkeit->value() + 1;
	game = new Spielfeld(name, Schwierigkeit(level));

	ui.lineEdit->setVisible(false);
	ui.label_2->setVisible(false);
	ui.stoppButton->setDisabled(false);
	initComponents();
	initField();
	ui.centralWidget->setLayout(field);
	ui.startButton->setDisabled(true);
	timerId = startTimer(1000);
}


//Pausebutton pressed
void QtDHBWscapes::MenuStoppPressed()
{
	if (paused) // already paused
	{
		for (int i = 0; i < 12; i++)
		{
			for (int j = 0; j < 12; j++)
			{
				btnArray[i][j]->setDisabled(false);
			}
		}
		ui.stoppButton->setText("Pause");
		paused = false;
		timerId = startTimer(1000);
	}
	else // resume
	{
		for (int i = 0; i < 12; i++)
		{
			for (int j = 0; j < 12; j++)
			{
				btnArray[i][j]->setDisabled(true);
			}
		}
		ui.stoppButton->setText("Weiter");
		paused = true;
		killTimer(timerId);
	}

}


//Helpbutton pressed
void QtDHBWscapes::MenuHelpPressed()
{
	endBox = new QMessageBox(this);
	endBox->setWindowTitle("Hilfe");
	endBox->setText("Fragen an die drei werden gegen ein Bier beantwortet :D\n");
	endBox->setIconPixmap(QPixmap("dhbwscapes_title.png").scaled(600, 400));

	endBox->exec();
}

void QtDHBWscapes::exitGame()
{
	exit(0);
}

void QtDHBWscapes::initComponents()
{
	//grid
	field = new QGridLayout;
	QMargins margin(20, 100, 20, 20);
	field->setContentsMargins(margin);
	field->setHorizontalSpacing(6);
	field->setVerticalSpacing(6);
	field->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);

}

//init whole grid
void QtDHBWscapes::initField()
{
	for (int i = 0; i < Spielfeld::fieldSize; i++)
	{
		for (int j = 0; j < Spielfeld::fieldSize; j++)
		{
			btnArray[i][j] = initButton(game->belegung[i][j]->getColor(), i, j);
			setButtonLayout(i, j);
			field->addWidget(btnArray[i][j], i, j);
		}
	}
	ui.centralWidget->setLayout(field);
}

//updates whole grid
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

//sets token colors
void QtDHBWscapes::setButtonLayout(int x, int y)
{
	int color = game->belegung[x][y]->getColor();

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
	default: break;
	}
}


//inits tokenbuttons to a map 
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

		if (game->belegung[x][y]->getColor() > Farbe::rot)
		{
			game->belegung[x][y]->activate(game, x, y);

			game->fromX = -1;
			game->fromY = -1;

			updateField();
		}
	}
	else
	{
		game->toX = x;
		game->toY = y;
		game->belegung[game->fromX][game->fromY]->Move(game);

		game->fromX = -1;
		game->fromY = -1;
		game->toX = -1;
		game->toY = -1;
		updateField();
	}

	UpdatePoints();

}

void QtDHBWscapes::BorderButton(int x, int y)
{
	int color = game->belegung[x][y]->getColor();
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
	default: break;
	}
}


/// <summary>
/// executed everytime the timer triggers
/// </summary>
/// <param name="event"></param>
void QtDHBWscapes::timerEvent(QTimerEvent* event)
{
	//updates Progress bar
	ui.progressBar->setValue(int((float(game->getTimeLeft()) / game->getTimeLimit()) * 100));
	ui.zeit->setText(QString::number(game->getTimeLeft()) + "s");
	game->addTimeAndPoints(-1, -1);

	if (game->getTimeLeft() < 0)
		showGameResult();
}

void QtDHBWscapes::showGameResult()
{
	endBox = new QMessageBox(this);
	try
	{
		ui.zeit->setText("VERLOREN");

		string output = "Sie haben " + to_string(game->getPoints()) + " Punkte erreicht!\n\n";

		string highscore;

		

		if (game->getPoints() > game->highscoreList[9])
		{
			//new highscore
			game->highscoreList.push_back(Player(game->getPlayerName(), game->getPoints()));
			game->writeHighscoreFile();
			for (int i = 0; i < 10; i++)
				highscore.append(to_string(i + 1) + ". " + game->highscoreList[i].Name + " mit " + to_string(game->highscoreList[i].Punkte) + " erreichten Punkten!\n");

			output = "Neuer Highscore!\n\n" + output + highscore;
		}

		else
		{
			for (int i = 0; i < 10; i++)
				highscore.append(to_string(i + 1) + ". " + game->highscoreList[i].Name + " mit " + to_string(game->highscoreList[i].Punkte) + " erreichten Punkten!\n");

			output.append("Fuer einen Highscore benoetigen Sie mindestens " + to_string(game->highscoreList[9].Punkte) + " Punkte!\n\n" + highscore);
			//endBox->setIconPixmap(QPixmap("TimesUp.png").scaled(400, 400)); wollt ihr das sch�ne bild nicht haben :(((
		}
		endBox->setText(QString::fromStdString(output));
	}

	catch (exception)
	{
		endBox->setText("Fehler beim Zugriff auf Highscore-Liste.\nHave you tried turn it off and on again?");
	}

	endBox->exec();

	//Play a new game??
	QMessageBox::StandardButton reply;
	reply = QMessageBox::question(endBox, "Neustart?", "Moechten Sie noch eine Runde spielen?", QMessageBox::Yes | QMessageBox::No);
	if (reply == QMessageBox::Yes)
	{
		game = new Spielfeld(game->getPlayerName(), game->getLevel());
		updateField();
	}
	else
		exit(0);
}





//shows current points, and updates them
void QtDHBWscapes::UpdatePoints()
{
	if (ui.lcdNumber->checkOverflow(game->getPoints()))
	{
		int digit = ui.lcdNumber->digitCount();
		ui.lcdNumber->setDigitCount(digit + 2);
		ui.lcdNumber->display(game->getPoints());
		ui.lcdNumber->setSegmentStyle(QLCDNumber::Filled);
	}
	else
	{
		ui.lcdNumber->display(game->getPoints());
	}
}
