#include "Window.h"

//Window::Window( QWidget *parent ) :
// Window::Window() :
// 	QMainWindow(parent, Qt::Window),
// 	myConfig("battlezone.cfg")
Window::Window()
{
//	QWidget *mainWin = new QWidget( this );
	glWidget = new GLWidget;
//	setCentralWidget( mainWin );
	//QHBoxLayout *mainLayout = new QHBoxLayout(mainWin);
//	test = new QLabel(tr("test"), mainWin);
//	test->hide();
//	keys.insert( Qt::Key_Up, Forward );
//	keys.insert( Qt::Key_Left, RotateLeft );
//	keys.insert( Qt::Key_Right, RotateRight );
//	keys.insert( Qt::Key_Down, Reverse );
//	keys.insert( Qt::Key_Space, Shoot );
//	keys.insert( Qt::Key_Escape, Exit );
//
//	move = new QSound( "sound/move.wav", glWidget );
//	fire = new QSound( "sound/fire.wav", glWidget );
//	kill = new QSound( "sound/kill.wav", glWidget );
//	move->setLoops( 5 );

//TODO: Remove the following test code
	xSlider = createSlider();
	ySlider = createSlider();
	zSlider = createSlider();

	connect( xSlider, SIGNAL( valueChanged( int ) ), glWidget, SLOT( setXRotation( int ) ) );
	connect( glWidget, SIGNAL( xRotationChanged( int ) ), xSlider, SLOT( setValue( int ) ) );
	connect( ySlider, SIGNAL( valueChanged( int ) ), glWidget, SLOT( setYRotation( int ) ) );
	connect( glWidget, SIGNAL( yRotationChanged( int ) ), ySlider, SLOT( setValue( int ) ) );
	connect( zSlider, SIGNAL( valueChanged( int ) ), glWidget, SLOT( setZRotation( int ) ) );
	connect( glWidget, SIGNAL( zRotationChanged( int ) ), zSlider, SLOT( setValue( int ) ) );

	QHBoxLayout *mainLayout = new QHBoxLayout;
	mainLayout->addWidget( glWidget );
	mainLayout->addWidget( xSlider );
	mainLayout->addWidget( ySlider );
	mainLayout->addWidget( zSlider );
	setLayout( mainLayout );

	xSlider->setValue( 15 * 16 );
	ySlider->setValue( 345 * 16 );
	zSlider->setValue( 0 * 16 );
	// TODO: End test code
	setWindowTitle(tr("Battlezone"));
}

QSlider *Window::createSlider()
{
	// TODO: Test code
	QSlider *slider = new QSlider( Qt::Vertical );
	slider->setRange( 0, 360 * 16 );
	slider->setSingleStep( 16 );
	slider->setPageStep( 15 * 16 );
	slider->setTickInterval( 15 * 16 );
	slider->setTickPosition( QSlider::TicksRight );
	return slider;
}

void Window::keyPressEvent( QKeyEvent *event )
{
	if ( event->isAutoRepeat() || !keys.contains( event->key() ) ) {
		event->ignore();
		return;
	}

	Action a = keys[ event->key()];

	switch ( a ) {
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
	if ( event->isAutoRepeat() || !keys.contains( event->key() ) ) {
		event->ignore();
		return;
	}

	Action a = keys[ event->key()];

	switch ( a ) {

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


