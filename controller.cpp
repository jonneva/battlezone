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

#include "controller.h"

controller::controller( QWidget *parent, int timerInterval )
{
	if( timerInterval == 0 ) m_timer = 0;
	else {
		m_timer = new QTimer( this );
		connect( m_timer, SIGNAL(timeout()), this, SLOT(timeOutSlot()) );
		m_timer->start( timerInterval );
	}
	cameraAngle = 0.0;
	cameraX = 0.0f, cameraY = 1.75f, cameraZ = 5.0f;
	losX = 0.0f, losY = 0.0f, losZ = -1.0f;


	Models = model(); // Parse models data file
	// Objects are compiled-in for demo but could just as easily be
	// put into a dynamic data structure
	tank = object3d(Models.tank);
	tankDestroyed = object3d(Models.deadTank);
	projectile = object3d(Models.projectile);

	isMovingZ = 0; // See header
	isRotating = 0;
	projectileActive = false;
	projectileLoadOrientation = true;
}

void controller::initializeGL()
{
	glShadeModel(GL_SMOOTH); // Smooth color transitions, in case lines are colored based on distance in the future

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Use highest-quality (slowest) perspective correction
}

// Called once when window is created, and every time the window is updated (handles aspect ratio and all that)
void controller::resizeGL( int width, int height )
{
	if(height <= 0) height = 1;

	glViewport( 0, 0, (GLint)width, (GLint)height );

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Set 45 degree FOV, keep 5:4 AR regardless of resolution
	gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
		gluLookAt(cameraX, cameraY, cameraZ,
			  cameraX + losX, cameraY + losY, cameraZ + losZ,
			  0.0f, 1.0f, 0.0f);
}

// Renders the frame
void controller::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glColor3f(0.0f, 1.0f, 0.0f); // Green color for rendering lines.
	cameraRotate(cameraAngle);

	tank.render();

	cameraRotate(cameraAngle);
	glTranslatef(5.0f, 0.0f, 0.0f);
	tankDestroyed.render();

	cameraRotate(cameraAngle);

	if(projectileActive) {
		if(projectileLoadOrientation) {
			projectile.cameraX = this->cameraX;
			projectile.cameraY = this->cameraY;
			projectile.cameraZ = this->cameraZ;
			projectile.losX = this->losX;
			projectile.losY = this->losY;
			projectile.losZ = this->losZ;
			projectileLoadOrientation = false;
		}
		glLoadIdentity();
		projectile.cameraX += projectile.losX * .3;
		projectile.cameraZ += projectile.losZ * .3;
		gluLookAt(projectile.cameraX, projectile.cameraY, projectile.cameraZ,
			  projectile.cameraX + projectile.losX, projectile.cameraY + projectile.losY, projectile.cameraZ + projectile.losZ,
			  0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, 1.7f, 0.0f);
		projectile.render(true);
	}
}

void controller::timeOutSlot()
{
	timeOut();
}

// This function is called every timerInterval milliseconds.
// Used for changing the camera angles, rotation, and other timed events
void controller::timeOut()
{
	tank.angle += 0.5f; // Rotate tank model 1 degree
	if(tank.angle > 360.0f)	tank.angle -= 360.0f; // Make sure angle stays valid
	if(tank.angle < -360.0) tank.angle += 360.0f;

	tankDestroyed.angle -= 0.5; // Rotate destroyed tank model half a degree
	if(tankDestroyed.angle > 360.0) tankDestroyed.angle -= 360.0f;
	if(tankDestroyed.angle < -360.0) tankDestroyed.angle += 360.0f;

	cameraAngle += isRotating * 0.03f; // If the user is pressing forward or backward key, move camera
	cameraMoveZ(isMovingZ); // If user is pressing left/right key, rotate the camera

	if(projectileActive) {
		if(projectile.cameraZ > 100) {
			qDebug() << "Projectile went too far. Killing.";
			projectileActive = false; // It's gone out of the gaming area. Kill it.
			projectileLoadOrientation = true; // Orient projectile on next shot.
			projectile.cameraZ = 0.0f;
		}
	}
	updateGL(); // Refresh render with new stuff
}

// Window must be at least this size (unused)
QSize controller::minimumSizeHint() const
{
	return QSize( 50, 50 );
}

// Try to make window this size
QSize controller::sizeHint() const
{
	return QSize(1024, 768);
}

// Rotate camera: 1 = right, -1 = left, 0 = not rotating
void controller::cameraRotate(float angle)
{
	losX =  std::sin(angle);
	losZ = -std::cos(angle);
	glLoadIdentity();
	gluLookAt(cameraX, cameraY, cameraZ,
			  cameraX + losX, cameraY + losY, cameraZ + losZ,
			  0.0f, 1.0f, 0.0f);
}

// Move camera forward (direction ==1), backward (direction == -1) or not at all (direction == 0)
void controller::cameraMoveZ(int direction)
{
	cameraX += direction * (losX) * 0.3f;
	cameraZ += direction * (losZ) * 0.3f;
	glLoadIdentity();
	gluLookAt(cameraX, cameraY, cameraZ,
			  cameraX + losX, cameraY + losY, cameraZ + losZ,
			  0.0f, 1.0f, 0.0f);
}

