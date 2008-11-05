#include "Window.h"
#include <QPushButton>
#include <QtGui>
#include <QSize>

Window::Window()
{
    MainWidget = new QWidget;
    setCentralWidget(MainWidget);
    MainWidget->setFixedSize(1000, 500);
   
    createMenus();
}

void Window::createMenus()
{
 	fileMenu = menuBar()->addMenu(tr("&File"));
	//fileMenu->addAction(NewGameAction);
 	
        helpMenu = menuBar()->addMenu(tr("&Help"));
	//helpMenu->addAction(HelpAction);
}

void Window::createActions()
{
    HelpAction = new QAction(tr("&Help"), this);
    HelpAction->setShortcut(tr("Ctrl+H"));
    connect(HelpAction, SIGNAL(triggered()), this, SLOT(Help()));
}

void Window::Help()
{
 	
			   
}
