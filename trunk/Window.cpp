#include "Window.h"

config myConfig("battlezone.cfg");

Window::Window()
{
	myController = new controller();

	QHBoxLayout *mainLayout = new QHBoxLayout;
	mainLayout->addWidget( myController );
	setLayout( mainLayout );

	setWindowTitle("Battlezone");
}






