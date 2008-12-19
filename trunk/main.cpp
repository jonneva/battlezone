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

#include "main.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	Window window;
	window.resize(window.sizeHint());
	window.show();
	return app.exec();
}
