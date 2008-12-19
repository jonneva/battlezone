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

#ifndef WINDOW_H
#define WINDOW_H

#include <QApplication>
#include "controller.h"
#include "model.h"

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
