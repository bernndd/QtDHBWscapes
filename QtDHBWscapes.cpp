#include "QtDHBWscapes.h"
#include "Spielfeld.h"
#include <time.h>
#include <QTimer>
#include <QDebug>
#include <string>

int Sec = 180, dur = 180; // Spielzeit ( beite die gleichen Werte

QtDHBWscapes::QtDHBWscapes(QWidget* parent)
	: QMainWindow(parent)
{
    srand(time(NULL));
    ui.setupUi(this);
    ui.Button_1_1->setStyleSheet(blau_h);
    ui.Button_1_2->setStyleSheet(bombe_h);
    ui.Button_1_3->setStyleSheet(disco_h);
    ui.Button_1_4->setStyleSheet(gelb_h);
    ui.Button_1_5->setStyleSheet(gruen_h);
    ui.Button_1_6->setStyleSheet(hellblau_h);
    ui.Button_1_7->setStyleSheet(horizontal_h);
    ui.Button_1_8->setStyleSheet(pink_h);
    ui.Button_1_9->setStyleSheet(rot_h);
    ui.Button_1_10->setStyleSheet(vertikal_h);
    
    Spielfeld game(true);

    //for (int i = 0; i < Spielfeld::fieldSize; i++)
    //{
    //    for (int j = 0; j < Spielfeld::fieldSize; j++)
    //    {
    //        ColorButton(Spielfeld::belegung.at(i).at(j), i, j);
    //    }
    //}

    for (int x = 1; x < 13; x++)
    {
        for (int y = 1; y < 13; y++)
        {
            int color = rand() % 10 + 1;
            ColorButton(color, y, x);

        }
    }

    for (int x = 1; x < 13; x++)
    {
        for (int y = 1; y < 13; y++)
        {
            int color = rand() % 10 + 1;
            ColorButton(color, y, x);
            
        }
    }
}
	for (int x = 1; x < 13; x++)
	{
		for (int y = 1; y < 13; y++)
		{
			int color = rand() % 10 + 1;
			ColorButton(color, y, x);

		}
	}

	timerId = startTimer(1000);
}


void QtDHBWscapes::ButtonClicked()
{
    
}

QPushButton* QtDHBWscapes::GetButtonByCoords(int y, int x)
{
    QString Button = "Button_";
    if (x < 10)
    {
        Button.append(x + 48); //append(std::to_string(x));
    }
    else
    {
        Button.append("1");
        Button.append((x - 10) + 48);
    }
    Button.append("_");
    if (y < 10)
    {
        Button.append(y + 48);
    }
    else
    {
        Button.append("1");
        Button.append((y - 10) + 48);
    }
    return ui.gridLayoutWidget->findChild<QPushButton*>(Button);
}

void QtDHBWscapes::setConnectionFromButtons()
{
    for (int x = 1; x < 13; x++)
    {
        for (int y = 1; y < 13; y++)
        {
            QObject::connect(GetButtonByCoords(y, x), SIGNAL(clicked()), this, SLOT(ButtonClicked()));
        }
    }
}



/*
* Set Color to Button on y,x
*/
void  QtDHBWscapes::ColorButton(int color, int y, int x)
{
    QPushButton* bt = GetButtonByCoords(y,x);
    if (bt != NULL)
    {
        switch (color)
        {
        case 1:
            bt->setStyleSheet(rot_h);
            break;
        case 2:
            bt->setStyleSheet(blau_h);
            break;
        case 3:
            bt->setStyleSheet(hellblau_h);
            break;
        case 4:
            bt->setStyleSheet(gruen_h);
            break;
        case 5:
            bt->setStyleSheet(pink_h);
            break;
        case 6:
            bt->setStyleSheet(gelb_h);
            break;
        case 7:
            bt->setStyleSheet(disco_h);
            break;
        case 8:
            bt->setStyleSheet(bombe_h);
            break;
        case 9:
            bt->setStyleSheet(horizontal_h);
            break;
        case 10:
            bt->setStyleSheet(vertikal_h);
            break;
        default:
            break;
        }
        
    }
	QString Button = "Button_";
	if (x < 10)
	{
		Button.append(x + 48); //append(std::to_string(x));
	}
	else
	{
		Button.append("1");
		Button.append((x - 10) + 48);
	}
	Button.append("_");
	if (y < 10)
	{
		Button.append(y + 48);
	}
	else
	{
		Button.append("1");
		Button.append((y - 10) + 48);
	}

	QPushButton* bt = ui.gridLayoutWidget->findChild<QPushButton*>(Button);
	if (bt != NULL)
	{
		switch (color)
		{
		case 1:
			bt->setStyleSheet(rot);
			break;
		case 2:
			bt->setStyleSheet(blau);
			break;
		case 3:
			bt->setStyleSheet(hellblau);
			break;
		case 4:
			bt->setStyleSheet(gruen);
			break;
		case 5:
			bt->setStyleSheet(pink);
			break;
		case 6:
			bt->setStyleSheet(gelb);
			break;
		case 7:
			bt->setStyleSheet(disco);
			break;
		case 8:
			bt->setStyleSheet(bombe);
			break;
		case 9:
			bt->setStyleSheet(horizontal);
			break;
		case 10:
			bt->setStyleSheet(vertikal);
			break;
		default:
			break;
		}

	}
}

QtDHBWscapes::~QtDHBWscapes()
{
	killTimer(timerId);
	//delete ui; klappt net
}

void QtDHBWscapes::timerEvent(QTimerEvent* event)//Update
{
	std::string str;
	qDebug();
	if (((Sec % 60) < 10) && (Sec > 0)) // For adding an additional zero when its smaller than 10
	{
		str = ("<html><head/><body><p><span style =\"font-size:18pt;\">" + std::to_string(Sec / 60) + ":0" + std::to_string(Sec % 60) + "</span></p></body></html>");
	}

	else if (Sec == 0) // Time is up
	{
		ui.PopUp->setStyleSheet("border-image:url(://QtDHBWscapes//Ohne Hintergrund//TimesUp.png);");
		str = "<html><head/><body><p><span style =\"font-size:18pt;\">Time is up !</span></p></body></html>";
		killTimer(timerId);
	}
	else
	{
		str =("<html><head/><body><p><span style =\"font-size:18pt;\">" +  std::to_string(Sec / 60) + ":" + std::to_string(Sec % 60) + "</span></p></body></html>");
	}
	QString qstr = QString::fromStdString(str);
	ui.displayTime->setText(qstr);
	ui.timeBar->setValue((double)Sec / (double)dur * 100);
	Sec--;
	
}
