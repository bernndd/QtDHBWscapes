#include "QtDHBWscapes.h"
#include "Spielfeld.h"
#include <time.h>
#include <QTimer>
#include <QDebug>
#include <string>

int Sec = 30, dur = 30; // Spielzeit (beide die gleichen Werte)

QtDHBWscapes::QtDHBWscapes(QWidget* parent)
	: QMainWindow(parent)
{
    srand(time(NULL));
    ui.setupUi(this);
    
    //Spielfeld game(true);
    ui.PopUp->setVisible(false);

    for (int x = 1; x < 13; x++)
    {
        for (int y = 1; y < 13; y++)
        {
            int color = rand() % 10 + 1;
            ColorButton(color, y, x);
       
        }
    }
	timerId = startTimer(1000); //starts Timer with 1 sec duration
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
}

QtDHBWscapes::~QtDHBWscapes()
{
	killTimer(timerId);
}

void QtDHBWscapes::timerEvent(QTimerEvent* event)//Is executed everytime the timer triggers
{
	std::string str;
	qDebug();
	if (((Sec % 60) < 10) && (Sec > 0)) // For adding an additional zero when its smaller than 10, just visual purpose
	{
		str = ("<html><head/><body><p><span style =\"font-size:18pt;\">" + std::to_string(Sec / 60) + ":0" + std::to_string(Sec % 60) + "</span></p></body></html>");
	}

	else if (Sec == 0) // Time is up
	{
        ui.PopUp->setVisible(true);
		ui.PopUp->setStyleSheet("border-image:url(://QtDHBWscapes//Ohne Hintergrund//TimesUp.png);"); // loads a picture
		str = "<html><head/><body><p><span style =\"font-size:18pt;\">Time is up !</span></p></body></html>"; //Displays that the time is up
		killTimer(timerId); // kills Timer
	}
	else //creating an array which is also the stylesheet for the Label
	{
		str =("<html><head/><body><p><span style =\"font-size:18pt;\">" +  std::to_string(Sec / 60) + ":" + std::to_string(Sec % 60) + "</span></p></body></html>");
	}
    //Setting the Label, so that it Displays the Time and also adjusts the Progress bar so that it shows the right percentage
	QString qstr = QString::fromStdString(str);
	ui.displayTime->setText(qstr);
	ui.timeBar->setValue((double)Sec / (double)dur * 100);
	Sec--;
	
}
