#include "main.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QPushButton hello("Hello world!");

	
	config myConfig("battlezone.cfg");
	
	hello.show();
	return app.exec();
}