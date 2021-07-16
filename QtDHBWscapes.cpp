#include "QtDHBWscapes.h"
#include <QPixmap>

//#include <time.h>


int Sec = 30, dur = 30; // Spielzeit (beide die gleichen Werte)

QtDHBWscapes::QtDHBWscapes(QWidget* parent)
	: QMainWindow(parent)
{
    //srand(time(NULL));
    ui.setupUi(this);
    //ui.PopUp->setVisible(false);
    


    initComponents();
    initField();
    ui.centralWidget->setLayout(field);



	//timerId = startTimer(1000);
}


void QtDHBWscapes::initComponents()
{
    //Spielfläche
    field = new QGridLayout;
    QMargins margin(20, 20, 20, 20);
    field->setContentsMargins(margin);
    field->setHorizontalSpacing(6);
    field->setVerticalSpacing(6);
    field->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);

    game = new Spielfeld(true);


	//Fenster Spielende
	timesUpBox = new QMessageBox(this);
	//timesUpBox->setText("Zeit ist um!");
	timesUpBox->setIconPixmap(QPixmap("TimesUp.png"));
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

			//cleanGrid();
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
		//cleanGrid();
		updateField();
	}

}

//QtDHBWscapes::~QtDHBWscapes()
//{
//	killTimer(timerId);
//}
//
//void QtDHBWscapes::timerEvent(QTimerEvent* event)//Is executed everytime the timer triggers
//{
//	std::string str;
//	qDebug();
//	if (((Sec % 60) < 10) && (Sec > 0)) // For adding an additional zero when its smaller than 10, just visual purpose
//	{
//		str = ("<html><head/><body><p><span style =\"font-size:18pt;\">" + std::to_string(Sec / 60) + ":0" + std::to_string(Sec % 60) + "</span></p></body></html>");
//	}
//
//	else if (Sec == 0) // Time is up
//	{
//        ui.PopUp->setVisible(true);
//		ui.PopUp->setStyleSheet("border-image:url(://QtDHBWscapes//Ohne Hintergrund//TimesUp.png);"); // loads a picture
//		str = "<html><head/><body><p><span style =\"font-size:18pt;\">Time is up !</span></p></body></html>"; //Displays that the time is up
//		killTimer(timerId); // kills Timer
//	}
//	else //creating an array which is also the stylesheet for the Label
//	{
//		str =("<html><head/><body><p><span style =\"font-size:18pt;\">" +  std::to_string(Sec / 60) + ":" + std::to_string(Sec % 60) + "</span></p></body></html>");
//	}
//    //Setting the Label, so that it Displays the Time and also adjusts the Progress bar so that it shows the right percentage
//	QString qstr = QString::fromStdString(str);
//	ui.displayTime->setText(qstr);
//	ui.timeBar->setValue((double)Sec / (double)dur * 100);
//	Sec--;
//	
//}
