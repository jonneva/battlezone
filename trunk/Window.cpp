#include "Window.h"

Window::Window() :
	QMainWindow()
{
	QWidget *mainWin = new QWidget( this );
	setCentralWidget( mainWin );
	QHBoxLayout *mainLayout = new QHBoxLayout(mainWin);

	fov = new view();
	mainLayout->addWidget(fov);
}
