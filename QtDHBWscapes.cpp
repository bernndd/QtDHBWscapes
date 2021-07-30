#include "QtDHBWscapes.h"



QtDHBWscapes::QtDHBWscapes(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	paused = false;

	//Connection Menubar
	InitMenu();
}

/// <summary>
/// register events to the menu buttons
/// </summary>
void QtDHBWscapes::InitMenu()
{
	connect(ui.startButton, SIGNAL(clicked()), this, SLOT(MenuStartPressed()));
	connect(ui.stoppButton, SIGNAL(clicked()), this, SLOT(MenuStoppPressed()));
	connect(ui.beendenButton, SIGNAL(clicked()), this, SLOT(exitGame()));
	connect(ui.hilfeButton, SIGNAL(clicked()), this, SLOT(MenuHelpPressed()));
	connect(ui.schwierigkeit, SIGNAL(valueChanged(int)), this, SLOT(editTimeValues(int)));
}

/// <summary>
///	edit time display
/// </summary>
/// <param name="value"></param>
void QtDHBWscapes::editTimeValues(int value)
{
	//ui.zeit->setText(QString::number(game->getTimeLimit()) + "s");
	switch (value + 1)
	{
	case 2: ui.zeit->setText(QString::number(10) + "s"); break;
	case 3: ui.zeit->setText(QString::number(5) + "s"); break;
	default: ui.zeit->setText(QString::number(20) + "s"); break;
	}
}

/// <summary>
/// StartButton pressed
/// </summary>
void QtDHBWscapes::MenuStartPressed()
{
	ui.graphicsView->setVisible(false);

	//Read Player Name, convert it  and make the Textedit and the label invisible
	QString QName = ui.lineEdit->text();
	std::string name = QName.toLocal8Bit().constData();
	//init difficulty
	int level = ui.schwierigkeit->value() + 1;
	game = new Game(name, Level(level));

	ui.lineEdit->setVisible(false);
	ui.label_2->setVisible(false);
	ui.stoppButton->setDisabled(false);
	initComponents();
	initField();
	ui.centralWidget->setLayout(field);
	ui.startButton->setDisabled(true);
	timerId = startTimer(1000);
}


/// <summary>
/// Pause Button pressed
/// </summary>
void QtDHBWscapes::MenuStoppPressed()
{
	if (paused) // already paused -> enable the field , change button text, and resume the timer 
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
	else // resume -> disable the field, change buttontext and pause the timer
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


/// <summary>
/// Helpbutton pressed
/// </summary>
void QtDHBWscapes::MenuHelpPressed()
{
	endBox = new QMessageBox(this);
	endBox->setWindowTitle("Hilfe");
	endBox->setText("Match 3 Spiel, verbinde mindestens 3 Steine bevor die Zeitablaeuft!\nMit jedem gelungenen Zug erhoehen sich deine Punkte!\nSpezialsteine:\n\n Rakete: Entfernt die gesamte Reihe/ Spalte.  gibt es entweder vertikal oder Horizontal je nachdem in welche Richtung der entscheidene Stein bewegt wird.\n\nBombe: Entfernt alle umliegenden Steine, indem sie explodiert.\n\nDiscokugel: Entfernt alle Steine einer Random Farbe aus dem Spielfeld\n\n\nVIEL SPASS BEIM SPIELEN!!!");

	endBox->exec();
}

/// <summary>
/// exitbutton Pressed
/// </summary>
void QtDHBWscapes::exitGame()
{
	exit(0);
}

/// <summary>
/// Init Components
/// </summary>
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

/// <summary>
/// Field get initialised
/// </summary>
void QtDHBWscapes::initField()
{
	for (int i = 0; i < Game::fieldSize; i++)
	{
		for (int j = 0; j < Game::fieldSize; j++)
		{
			btnArray[i][j] = initButton(game->occypency[i][j]->getColor(), i, j);
			setButtonLayout(i, j);
			field->addWidget(btnArray[i][j], i, j);
		}
	}
	ui.centralWidget->setLayout(field);
}

/// <summary>
/// updates whole grid
/// </summary>
void QtDHBWscapes::updateField()
{
	for (int i = 0; i < Game::fieldSize; i++)
	{
		for (int j = 0; j < Game::fieldSize; j++)
		{
			setButtonLayout(i, j);
		}
	}

}


/// <summary>
/// sets token colors
/// </summary>
/// <param name="x"> Coordinate </param>
/// <param name="y"> Coordinate </param>
void QtDHBWscapes::setButtonLayout(int x, int y)
{
	int color = game->occypency[x][y]->getColor();

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


/// <summary>
/// inits tokenbuttons to a map 
/// </summary>
/// <param name="color"> Color number</param>
/// <param name="x"> Coordinate </param>
/// <param name="y"> Coordinate </param>
/// <returns></returns>
QPushButton* QtDHBWscapes::initButton(int color, int x, int y)
{
	QPushButton* temp = new QPushButton();
	temp->setFixedSize(QSize(35, 35));
	int position = x * Game::fieldSize + y;

	QSignalMapper* signalMapper = new QSignalMapper(this);
	connect(temp, SIGNAL(clicked()), signalMapper, SLOT(map()));
	signalMapper->setMapping(temp, position);
	connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(btnAction(int)));

	return temp;
}

/// <summary>
/// Button pressed from Gamefield
/// </summary>
/// <param name="position"> Position number </param>
void QtDHBWscapes::btnAction(int position)
{
	//calc position
	int x = position / Game::fieldSize;
	int y = position % Game::fieldSize;

	if (game->getFromX() == -1) // first tokens clicked  -> save position
	{
		game->setRoot(x, y);
		BorderButton(x, y);

		if (game->occypency[x][y]->getColor() > Color::red) //checks if its a normal tokens, not a special
		{
			game->occypency[x][y]->activate(game, x, y);

			game->resetSavedCoordinates(false);

			updateField();
		}
	}
	else  // second tokens clicked
	{
		game->setDestination(x, y);
		game->occypency[game->getFromX()][game->getFromY()]->Move(game);

		game->resetSavedCoordinates(true);
		updateField();
	}

	UpdatePoints();

}

/// <summary>
/// init png pictures of tokens with boarder (when clicked)
/// </summary>
/// <param name="x"> Coordinate </param>
/// <param name="y"> Coordinate </param>
void QtDHBWscapes::BorderButton(int x, int y)
{
	int color = game->occypency[x][y]->getColor();
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
	//updates Points
	ui.lcdNumber->display(game->getPoints());
	game->addTimeAndPoints(-1, -1);

	if (game->getTimeLeft() < 0)
		showGameResult();
}

/// <summary>
/// Show Result of Game if game over
/// </summary>
void QtDHBWscapes::showGameResult()
{
	endBox = new QMessageBox(this);
	// tries if the Highcore list data is accessible 
	try
	{
		ui.zeit->setText("VERLOREN");

		string output = "Sie haben " + to_string(game->getPoints()) + " Punkte erreicht!\n\n";


		if (game->getPoints() > game->highscoreList[9])//new highscore
		{
			game->highscoreList.push_back(Player(game->getPlayerName(), game->getPoints()));
			game->writeHighscoreFile();
			output = "Neuer Highscore!\n\n" + output + game->buildHighscoreList();;
		}

		else  // regular Game ending
		{
			output.append("Fuer einen Highscore benoetigen Sie mindestens " + to_string(game->highscoreList[9].Points) + " Punkte!\n\n" + game->buildHighscoreList());
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
		game = new Game(game->getPlayerName(), game->getLevel());
		updateField();
	}
	else
		exit(0);
}





/// <summary>
/// shows current points, and updates them
/// </summary>
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
