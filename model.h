#ifndef MODEL_H
#define MODEL_H

#include <QFile>
#include <QString>
#include <QList>
#include <QtDebug>

#include "object3d.h"

class model
{
	public:
		model();
		model(QString file);

		QList<point3d> tank;
		QList<point3d> deadTank;
		QList<point3d> projectile;

		void parseModels(QString pathFile);

		void print(QList<point3d> printMe);
};

#endif // MODEL_H
