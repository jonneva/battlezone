#include "Window.h"

Window::Window( QWidget *parent ) :
	QMainWindow(parent, Qt::Window),
	myConfig("battlezone.cfg")
{
	QWidget *mainWin = new QWidget( this );
	setCentralWidget( mainWin );
	//QHBoxLayout *mainLayout = new QHBoxLayout(mainWin);
	test = new QLabel(tr("test"), mainWin);
	test->hide();
	keys.insert( Qt::Key_Up, Forward );
	keys.insert( Qt::Key_Left, RotateLeft );
	keys.insert( Qt::Key_Right, RotateRight );
	keys.insert( Qt::Key_Down, Reverse );
	keys.insert( Qt::Key_Space, Shoot );
	keys.insert( Qt::Key_Escape, Exit );
	
	move = new QSound( "sound/move.wav", mainWin);
	fire = new QSound( "sound/fire.wav", mainWin);
	kill = new QSound( "sound/kill.wav", mainWin);
	move->setLoops(5);
}

void Window::keyPressEvent( QKeyEvent *event )
{
	if ( event->isAutoRepeat() || !keys.contains( event->key() ) )
	{
		event->ignore();
		return;
	}

	Action a = keys[ event->key() ];

	switch ( a )
	{
		case Forward:
			move->play();
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
	if ( event->isAutoRepeat() || !keys.contains( event->key() ) )
	{
		event->ignore();
		return;
	}

	Action a = keys[ event->key() ];

	switch ( a )
	{

	case Forward:
		move->stop();
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


