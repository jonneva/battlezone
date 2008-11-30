#include "controller.h"

controller::controller( QWidget *parent, int timerInterval )
{
	myConfig = config("battlezone.cfg");
	QSound move(myConfig.soundMove);
	QSound fire(myConfig.soundFire);
	QSound kill(myConfig.soundKill);
	move.setLoops( 5 );

	keys.insert( Qt::Key_Up, Forward );
	keys.insert( Qt::Key_Left, RotateLeft );
	keys.insert( Qt::Key_Right, RotateRight );
	keys.insert( Qt::Key_Down, Reverse );
	keys.insert( Qt::Key_Space, Shoot );
	keys.insert( Qt::Key_Escape, Exit );

	if( timerInterval == 0 )
		m_timer = 0;
	else
	{
		m_timer = new QTimer( this );
		connect( m_timer, SIGNAL(timeout()), this, SLOT(timeOutSlot()) );
		m_timer->start( timerInterval );
	}

	rtri = rquad = 0.0f;
}

void controller::keyPressEvent( QKeyEvent *event )
{
	cerr << "Entering controller::keyPressEvent" << endl;
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


void controller::keyReleaseEvent( QKeyEvent *event )
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


void controller::initializeGL()
{
	glShadeModel(GL_SMOOTH);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void controller::resizeGL( int width, int height )
{
	height = height?height:1;

	glViewport( 0, 0, (GLint)width, (GLint)height );

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void controller::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(-1.5f,0.0f,-6.0f);
	glRotatef(rtri,0.0f,1.0f,0.0f);

	glBegin(GL_TRIANGLES);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f( 0.0f, 1.0f, 0.0f);
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f(-1.0f,-1.0f, 1.0f);
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f( 1.0f,-1.0f, 1.0f);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f( 0.0f, 1.0f, 0.0f);
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f( 1.0f,-1.0f, 1.0f);
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f( 1.0f,-1.0f, -1.0f);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f( 0.0f, 1.0f, 0.0f);
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f( 1.0f,-1.0f, -1.0f);
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(-1.0f,-1.0f, -1.0f);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f( 0.0f, 1.0f, 0.0f);
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(-1.0f,-1.0f,-1.0f);
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f(-1.0f,-1.0f, 1.0f);
	glEnd();

	glLoadIdentity();
	glTranslatef(1.5f,0.0f,-6.0f);
	glRotatef(rquad,1.0f,0.0f,0.0f);

	glColor3f(0.5f,0.5f,1.0f);
	glBegin(GL_QUADS);
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f( 1.0f, 1.0f,-1.0f);
		glVertex3f(-1.0f, 1.0f,-1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f( 1.0f, 1.0f, 1.0f);
		glColor3f(1.0f,0.5f,0.0f);
		glVertex3f( 1.0f,-1.0f, 1.0f);
		glVertex3f(-1.0f,-1.0f, 1.0f);
		glVertex3f(-1.0f,-1.0f,-1.0f);
		glVertex3f( 1.0f,-1.0f,-1.0f);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f( 1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f,-1.0f, 1.0f);
		glVertex3f( 1.0f,-1.0f, 1.0f);
		glColor3f(1.0f,1.0f,0.0f);
		glVertex3f( 1.0f,-1.0f,-1.0f);
		glVertex3f(-1.0f,-1.0f,-1.0f);
		glVertex3f(-1.0f, 1.0f,-1.0f);
		glVertex3f( 1.0f, 1.0f,-1.0f);
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f,-1.0f);
		glVertex3f(-1.0f,-1.0f,-1.0f);
		glVertex3f(-1.0f,-1.0f, 1.0f);
		glColor3f(1.0f,0.0f,1.0f);
		glVertex3f( 1.0f, 1.0f,-1.0f);
		glVertex3f( 1.0f, 1.0f, 1.0f);
		glVertex3f( 1.0f,-1.0f, 1.0f);
		glVertex3f( 1.0f,-1.0f,-1.0f);
	glEnd();
}

void controller::timeOutSlot()
{
	timeOut();
}


void controller::timeOut()
{
	rtri += 0.5f;
	rquad -= 0.25f;

	updateGL();
}

QSize controller::minimumSizeHint() const
{
	return QSize( 50, 50 );
}

QSize controller::sizeHint() const
{
	return QSize(1024, 768);
}

