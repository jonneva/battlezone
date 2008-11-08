#include "main.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	Window main;
	config myConfig("battlezone.cfg");

	main.setWindowTitle("BattleZone");
	main.resize(980,600);
	main.show();

	return app.exec();
}
