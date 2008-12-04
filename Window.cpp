#include "Window.h"

config myModels("battlezone.cfg");

Window::Window()
{
	myController = new controller(0, 50);

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
			qDebug("Entering Window::keyPressEvent, line %i", __LINE__);
			move->play();
			qDebug("Entering Window::keyPressEvent, line %i", __LINE__);
			break;

		case RotateLeft:
			move->play();
			break;

		case RotateRight:
			move->play();
			break;

		case Reverse:
			move->play();
			break;

		case Shoot:
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
			qDebug("Entering Window::keyReleaseEvent, line %i", __LINE__);
			move->stop();
			qDebug("Entering Window::keyReleaseEvent, line %i", __LINE__);
			break;

		case RotateLeft:
			move->stop();
			break;

		case RotateRight:
			move->stop();
			break;

		case Reverse:
			move->stop();
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



