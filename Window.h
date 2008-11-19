#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QKeyEvent>
#include <QMap>
#include <QLayout>
#include <QSound>
#include <QLabel>
#include "view.h"
#include "config.h"

class Window : public QMainWindow
{
    Q_OBJECT

	public:
	Window( QWidget *parent=0);
	view* fov;
	QLabel* test;
	config myConfig;

	protected:

	virtual void keyPressEvent( QKeyEvent *event );
	virtual void keyReleaseEvent( QKeyEvent *event );

	private:

	enum Action { Forward, RotateLeft, RotateRight, Reverse, Shoot, Exit  };
	QMap<int,Action> keys;
	
	QSound *move;
	QSound *fire;
	QSound *kill;
};

#endif
