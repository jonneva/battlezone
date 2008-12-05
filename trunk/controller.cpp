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
	tank = object3d(Models.tank);
	tankDestroyed = object3d(Models.deadTank);
	projectile = object3d(Models.projectile);

	isMovingZ = 0; // See header
	isRotating = 0;

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
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,1000.0f);

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
	// Make the "ground"
//	glBegin(GL_QUADS);
//		glColor3f(1.0f,0.5f,0.0f);
//		glVertex3f( 1.0f,-1.0f, 1.0f);
//		glVertex3f(-1.0f,-1.0f, 1.0f);
//		glVertex3f(-1.0f,-1.0f,-1.0f);
//		glVertex3f( 1.0f,-1.0f,-1.0f);
//	glEnd();
	glTranslatef(0.0f,0.0f,-12.0f);

	glColor3f(0.0f, 1.0f, 0.0f); // Green color for rendering lines.
	cameraRotate(cameraAngle);
	tank.render();

	cameraRotate(cameraAngle);
	glTranslatef(5.0f, 0.0f, 0.0f);
	tankDestroyed.render();

	cameraRotate(cameraAngle);
	glTranslatef(-3.0f, 0.0f, 0.0f);
	projectile.render();

	glTranslatef(3.0f, 0.0f, -12.0f);
//	glPushMatrix(); glPopMatrix();
}

void controller::timeOutSlot()
{
	timeOut();
}

// This function is called every timerInterval milliseconds.
// Used for changing the camera angles, rotation, and other timed events
void controller::timeOut()
{
	tank.angle += 1.0f; // Rotate demo tank model
	if(tank.angle > 360.0f)	tank.angle -= 360.0f; // Make sure angle stays valid
	if(tank.angle < -360.0) tank.angle += 360.0f;

	tankDestroyed.angle -=1.0; // Rotate demo destroyed tank model
	if(tankDestroyed.angle > 360.0) tankDestroyed.angle -= 360.0f;
	if(tankDestroyed.angle < -360.0) tankDestroyed.angle += 360.0f;

	cameraAngle += isRotating * 0.03f; // If the user is pressing forward or backward key, move camera
	cameraMoveZ(isMovingZ); // If user is pressing left/right key, rotate the camera

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
//	angle /= 0.0174532925; // Convert angle to radians
	//float toRads = 0.0174532925; // pi/180
	losX = std::sin(angle);
	losZ = -std::cos(angle);
	//if(angle > 0.0000001f) qDebug() << "Angle: " << angle << ", sin(angle): " << sin(angle) << endl;
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

