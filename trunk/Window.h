#ifndef WINDOW_H
#define WINDOW_H

#include <QApplication>
#include "controller.h"

class controller;

class Window : public QWidget
{
	Q_OBJECT

public:
	Window();
	config myConfig;

protected:
	void keyPressEvent( QKeyEvent *event );
	void keyReleaseEvent( QKeyEvent *event );
private:
	controller *myController;
	QSound *move;
	QSound *fire;
	QSound *kill;
	enum Action { Forward, RotateLeft, RotateRight, Reverse, Shoot, Exit  };
	QMap<int, Action> keys;
};

#endif
