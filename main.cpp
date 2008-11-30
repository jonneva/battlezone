#include "main.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	Window window;
//	config myConfig("battlezone.cfg");
	window.resize(window.sizeHint());
	window.show();
	return app.exec();
}
