#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QLayout>
#include "view.h"

class Window : public QMainWindow
{
    Q_OBJECT

	public:
	Window();
	view* fov;

};

#endif
