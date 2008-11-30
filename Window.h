#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QApplication>
#include <QKeyEvent>
#include <QLayout>
#include <QLabel>
#include "controller.h"


class controller;

class Window : public QWidget
{
	Q_OBJECT

public:
//	Window(QWidget *parent=0);
	Window();
//	view* fov;
//	QLabel* test;


private:


	// TODO: Remove these lines. Just for testing.
	controller *myController;

};

#endif
