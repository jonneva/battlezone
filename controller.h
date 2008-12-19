#ifndef CONTROLLER_H
#define CONTROLLER_H


#include <QtOpenGL>
#include <QGLWidget>
#include <QtGui>
#include <QTimer>
#include <QSound>
#include <QMap>
#include <QDebug>
#include <QtDebug>
#include <cmath>
#include "config.h"
#include "model.h"

class QTimer;

class controller : public QGLWidget
{
	Q_OBJECT
private:
	GLfloat rtri, rquad;
	QTimer *m_timer;
	model Models;	// [0] = tank, [1] = deadtank, [2] = projectile

public:
	controller( QWidget *parent = 0, int timerInterval = 0 );
	QSize minimumSizeHint() const;
	QSize sizeHint() const;
	object3d tank;
	object3d tankDestroyed;
	object3d projectile;

	GLfloat cameraAngle;
	GLfloat cameraX, cameraY, cameraZ; // Camera position
	GLfloat losX, losY, losZ; // Line of site

	void cameraRotate(float angle);
	void cameraMoveZ(int direction);

	qint8 isMovingZ; // Is camera moving? 1 = forward, -1 = back, 0 = not moving
	qint8 isRotating; // Is camera rotating? 1 = right, -1 = left, 0 = not rotating

	bool projectileActive; // Should we render the projectile? For demo purposes.
	bool projectileLoadOrientation; // Does the camera position of the firing tank need to be recorded?

protected:
	void initializeGL();
	void resizeGL( int width, int height );
	void paintGL();
	void timeOut();

protected slots:
	void timeOutSlot();
};




#endif
