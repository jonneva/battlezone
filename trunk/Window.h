#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QApplication>
#include <QKeyEvent>
#include <QMap>
#include <QLayout>
#include <QSound>
#include <QLabel>
#include "controller.h"
#include "config.h"

class controller;

class Window : public QWidget
{
	Q_OBJECT

public:
//	Window(QWidget *parent=0);
	Window();
//	view* fov;
//	QLabel* test;
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

	// TODO: Remove these lines. Just for testing.
	controller *myController;

};

#endif
