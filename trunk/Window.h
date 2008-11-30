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

private:
	controller *myController;
};

#endif
