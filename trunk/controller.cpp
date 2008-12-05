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

	Models = model();
	tank = object3d(Models.tank);
	tankDestroyed = object3d(Models.deadTank);
	projectile = object3d(Models.projectile);

	isMovingZ = 0;
	isRotating = 0;
//	projectile = object3d(Models.projectile);

}

void controller::initializeGL()
{
	glShadeModel(GL_SMOOTH);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Use highest-quality (slowest) perspective correction

	// Anti-aliasing, see http://www.opengl.org/resources/code/samples/sig99/advanced99/notes/node120.html
	// Hmm, doesn't seem to actually work.
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	glEnable(GL_POINT_SMOOTH);
//	glEnable(GL_LINE_SMOOTH);
//	glEnable(GL_POLYGON_SMOOTH);
//	glHint(GL_POINT_SMOOTH, GL_NICEST);
//	glHint(GL_LINE_SMOOTH, GL_NICEST);
//	glHint(GL_POLYGON_SMOOTH, GL_NICEST);
}

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
//	gluLookAt(cameraX, cameraY, cameraZ,
//			  cameraX + losX, cameraY + losY, cameraZ + losZ,
//			  0.0f, 1.0f, 0.0f);
}

void controller::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();


	// Make the "ground"
//	glBegin(GL_QUADS);
//		glColor3f(1.0f,0.5f,0.0f);			// Set The Color To Orange
//		glVertex3f( 1.0f,-1.0f, 1.0f);			// Top Right Of The Quad (Bottom)
//		glVertex3f(-1.0f,-1.0f, 1.0f);			// Top Left Of The Quad (Bottom)
//		glVertex3f(-1.0f,-1.0f,-1.0f);			// Bottom Left Of The Quad (Bottom)
//		glVertex3f( 1.0f,-1.0f,-1.0f);			// Bottom Right Of The Quad (Bottom)
//	glEnd();
	glTranslatef(0.0f,0.0f,-12.0f);

	glColor3f(0.0f, 1.0f, 0.0f); // Green color for rendering lines.
	//cameraMoveZ(-1);
	cameraRotate(cameraAngle);
	tank.render();

	cameraRotate(cameraAngle);
	glTranslatef(5.0f, 0.0f, 0.0f);
	tankDestroyed.render();

	cameraRotate(cameraAngle);
	glTranslatef(-3.0f, 0.0f, 0.0f);
	projectile.render();

	glTranslatef(3.0f, 0.0f, -12.0f);
//	glPushMatrix();


	// Order is: Translate, Rotate, glBegin/End, LoadIdentity, Translate...
	// Move the camera first (gltranslate)

	//http://www.falloutsoftware.com/tutorials/gl/gl5.htm
	//http://www.opengl.org/discussion_boards/ubbthreads.php?ubb=showflat&Number=249692
	//http://www.opengl.org/discussion_boards/ubbthreads.php?ubb=showflat&Number=249280#Post249280

	//http://www.lighthouse3d.com/opengl/glut/index.php?6 Move forward, turn camera
}

void controller::timeOutSlot()
{
	timeOut();
}

void controller::timeOut()
{
	tank.angle += 0.5f; // Rotate demo tank model
	if(tank.angle > 360.0f)	tank.angle -= 360.0f;
	if(tank.angle < -360.0) tank.angle += 360.0f;

	tankDestroyed.angle -=2.8; // Rotate demo destroyed tank model
	if(tankDestroyed.angle > 360.0) tankDestroyed.angle -= 360.0f;
	if(tankDestroyed.angle < -360.0) tankDestroyed.angle += 360.0f; // Make sure angle stays valid
	cameraAngle += isRotating * 0.1f;
	cameraMoveZ(isMovingZ);

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

void controller::cameraMoveZ(int direction)
{
	cameraX += direction * (losX);
	cameraZ += direction * (losZ);
	glLoadIdentity();
	gluLookAt(cameraX, cameraY, cameraZ,
			  cameraX + losX, cameraY + losY, cameraZ + losZ,
			  0.0f, 1.0f, 0.0f);
}

