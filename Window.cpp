//
// Battlezone
// A multiplayer remake of Atari's 1980 game: Battlezone
// Authors: Charles Burns
//          Trey Russell
//
// License: GPL3
// http://www.gnu.org/copyleft/gpl.html
//
// Requires QT 4.3 by Nokia's Trolltech software

#include "Window.h"

config myModels("battlezone.cfg");

Window::Window()
{
	myController = new controller(0, 10);

	QHBoxLayout *mainLayout = new QHBoxLayout;
	mainLayout->addWidget( myController );
	setLayout( mainLayout );

	setWindowTitle("Battlezone");

	move = new QSound(myConfig.soundMove);
	fire = new QSound(myConfig.soundFire);
	kill = new QSound(myConfig.soundKill);

	// Removed because sounds in a loop cannot be stopped until the current loop
	// finishes playing. (This can be added back later if it turns out to be the best way)
	//move->setLoops( 5 );

	keys.insert( Qt::Key_Up, Forward );
	keys.insert( Qt::Key_Left, RotateLeft );
	keys.insert( Qt::Key_Right, RotateRight );
	keys.insert( Qt::Key_Down, Reverse );
	keys.insert( Qt::Key_Space, Shoot );
	keys.insert( Qt::Key_Escape, Exit );}

void Window::keyPressEvent( QKeyEvent *event )
{
	qDebug("Entering Window::keyPressEvent");
	if ( event->isAutoRepeat() || !keys.contains( event->key() ) ) {
		// Move sound loops can be repeated in here
		event->ignore();
		return;
	}
	qDebug("Entering Window::keyPressEvent, line %i", __LINE__);

	Action a = keys[ event->key()];

	switch ( a ) {
		case Forward:
			move->play();
			myController->isMovingZ = 1;
			break;

		case Reverse:
			move->play();
			myController->isMovingZ = -1;
			break;

		case RotateLeft:
			move->play();
			myController->isRotating = -1;
			break;

		case RotateRight:
			move->play();
			myController->isRotating = 1;
			break;

		case Shoot:
			myController->projectileActive = true;
			myController->projectileLoadOrientation = true;
			fire->play();
			break;

		case Exit:
			QApplication::exit();
			break;

		default:
			event->ignore();
			return;
	}
	event->accept();
}


void Window::keyReleaseEvent( QKeyEvent *event )
{
	if ( event->isAutoRepeat() || !keys.contains( event->key() ) ) {
		event->ignore();
		return;
	}

	Action a = keys[ event->key()];

	switch ( a ) {

		case Forward:
			move->stop();
			myController->isMovingZ = 0;
			break;

		case Reverse:
			move->stop();
			myController->isMovingZ = 0;
			break;

		case RotateLeft:
			move->stop();
			myController->isRotating = 0;
			break;

		case RotateRight:
			move->stop();
			myController->isRotating = 0;
			break;

		case Shoot:
			break;

		case Exit:
			break;

		default:
			event->ignore();
			return;
	}

	event->accept();
}



