#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QtOpenGL>
#include <QGLWidget>
#include <QtGui>
#include <QTimer>
#include <QSound>
#include <QMap>

#include "config.h"

class QTimer;

class controller : public QGLWidget
{
	Q_OBJECT

private:
	QSound *move;
	QSound *fire;
	QSound *kill;
	enum Action { Forward, RotateLeft, RotateRight, Reverse, Shoot, Exit  };
	QMap<int,Action> keys;
	GLfloat rtri, rquad;
	QTimer *m_timer;

public:
	controller( QWidget *parent = 0, int timerInterval = 0 );
	QSize minimumSizeHint() const;
	QSize sizeHint() const;
	config myConfig;

protected:
	void initializeGL();
	void resizeGL( int width, int height );
	void paintGL();
	void timeOut();
	void keyPressEvent( QKeyEvent *event );
	void keyReleaseEvent( QKeyEvent *event );

protected slots:
	void timeOutSlot();

};


#endif
