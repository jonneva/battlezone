#include "view.h"

GLWidget::GLWidget( QWidget *parent )
		: QGLWidget( parent )
{
	object = 0;
	xRot = 0;
	yRot = 0;
	zRot = 0;

	trolltechGreen = QColor::fromCmykF( 0.40, 0.0, 1.0, 0.0 );
	trolltechPurple = QColor::fromCmykF( 0.39, 0.39, 0.0, 0.0 );
}

GLWidget::~GLWidget()
{
	makeCurrent();
	glDeleteLists( object, 1 );
}

QSize GLWidget::minimumSizeHint() const
{
	return QSize( 50, 50 );
}

QSize GLWidget::sizeHint() const
{
	return QSize(1024, 768);
}

void GLWidget::setXRotation( int angle )
{
	normalizeAngle( &angle );
	if ( angle != xRot ) {
		xRot = angle;
		emit xRotationChanged( angle );
		updateGL();
	}
}

void GLWidget::setYRotation( int angle )
{
	normalizeAngle( &angle );
	if ( angle != yRot ) {
		yRot = angle;
		emit yRotationChanged( angle );
		updateGL();
	}
}

void GLWidget::setZRotation( int angle )
{
	normalizeAngle( &angle );
	if ( angle != zRot ) {
		zRot = angle;
		emit zRotationChanged( angle );
		updateGL();
	}
}

void GLWidget::initializeGL()
{
	qglClearColor( trolltechPurple.dark() );
	object = makeObject();
	glShadeModel( GL_FLAT );
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_CULL_FACE );
}

void GLWidget::paintGL()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();
	glTranslated( 0.0, 0.0, -10.0 );
	glRotated( xRot / 16.0, 1.0, 0.0, 0.0 );
	glRotated( yRot / 16.0, 0.0, 1.0, 0.0 );
	glRotated( zRot / 16.0, 0.0, 0.0, 1.0 );
	glCallList( object );
}

void GLWidget::resizeGL( int width, int height )
{
	int side = qMin( width, height );
	glViewport(( width - side ) / 2, ( height - side ) / 2, side, side );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( -0.5, + 0.5, + 0.5, -0.5, 4.0, 15.0 );
	glMatrixMode( GL_MODELVIEW );
}

void GLWidget::mousePressEvent( QMouseEvent *event )
{
	lastPos = event->pos();
}

void GLWidget::mouseMoveEvent( QMouseEvent *event )
{
	int dx = event->x() - lastPos.x();
	int dy = event->y() - lastPos.y();

	if ( event->buttons() & Qt::LeftButton ) {
		setXRotation( xRot + 8 * dy );
		setYRotation( yRot + 8 * dx );
	} else if ( event->buttons() & Qt::RightButton ) {
		setXRotation( xRot + 8 * dy );
		setZRotation( zRot + 8 * dx );
	}
	lastPos = event->pos();
}

GLuint GLWidget::makeObject()
{
	GLuint list = glGenLists( 1 );
	glNewList( list, GL_COMPILE );

	glBegin( GL_QUADS );

	const double Pi = 3.14159265358979323846;
	const int NumSectors = 200;

	for ( int j = 0; j < 2; ++j ) {
		double r = 0.1 + ( j * 0.2 );

		for ( int i = 0; i < NumSectors; ++i ) {
			double angle1 = ( i * 2 * Pi ) / NumSectors;
			GLdouble x5 = ( r + 0.1 ) * sin( angle1 );
			GLdouble y5 = ( r + 0.1 ) * cos( angle1 );
			GLdouble x6 = r * sin( angle1 );
			GLdouble y6 = r * cos( angle1 );

			double angle2 = (( i + 1 ) * 2 * Pi ) / NumSectors;
			GLdouble x7 = r * sin( angle2 );
			GLdouble y7 = r * cos( angle2 );
			GLdouble x8 = ( r + 0.1 ) * sin( angle2 );
			GLdouble y8 = ( r + 0.1 ) * cos( angle2 );

			quad( x5, y5, x6, y6, x7, y7, x8, y8 );

			extrude( x6, y6, x7, y7 );
			extrude( x8, y8, x5, y5 );
		}
	}

	glEnd();

	glEndList();
	return list;
}

void GLWidget::quad( GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2,
					 GLdouble x3, GLdouble y3, GLdouble x4, GLdouble y4 )
{
	qglColor( trolltechGreen );

	glVertex3d( x1, y1, -0.05 );
	glVertex3d( x2, y2, -0.05 );
	glVertex3d( x3, y3, -0.05 );
	glVertex3d( x4, y4, -0.05 );

	glVertex3d( x4, y4, + 0.05 );
	glVertex3d( x3, y3, + 0.05 );
	glVertex3d( x2, y2, + 0.05 );
	glVertex3d( x1, y1, + 0.05 );
}

void GLWidget::extrude( GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2 )
{
	qglColor( trolltechGreen.dark( 250 + int( 100 * x1 ) ) );

	glVertex3d( x1, y1, + 0.05 );
	glVertex3d( x2, y2, + 0.05 );
	glVertex3d( x2, y2, -0.05 );
	glVertex3d( x1, y1, -0.05 );
}

void GLWidget::normalizeAngle( int *angle )
{
	while ( *angle < 0 )
		*angle += 360 * 16;
	while ( *angle > 360 * 16 )
		*angle -= 360 * 16;
}
