//
// Battlezone
// A multiplayer remake of Atari's 1980 game: Battlezone
// Authors: Charles Burns
//          Trey Russell
//
// License: GPL3
// http://www.gnu.org/copyleft/gpl.html
//
// Requires QT 4.3 by Nokia's Trolltech software

#include "model.h"

model::model()
{
	parseModels("models.dat");
}

model::model(QString file)
{
	parseModels(file);
}

void model::parseModels(QString filePath)
{
		QFile file(filePath);
		if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
				qDebug() << "Could not open file: '" << filePath << "' on line "
				<< __LINE__ << " in " << __FILE__;
		}
		else
		{

		QString currentLine = file.readLine();
		currentLine = file.readLine();
		while(currentLine.size() != 1)
		{
			point3d line;
			int i = 0;
			int e = 1;

			while(e <= 6)
			{
				QString point = currentLine.section(' ', i, i);
				if(point != "")
				{
					float p = point.toFloat();
					if( e == 1 ) { line.x1 = p; }
					else if ( e == 2 ) {line.y1 = p; }
					else if ( e == 3 ) {line.z1 = p; }
					else if ( e == 4 ) {line.x2 = p; }
					else if ( e == 5 ) {line.y2 = p; }
					else if ( e == 6 ) {line.z2 = p; }
					else{}
					e++;
				}
				i++;
			}
			tank.append(line);
			currentLine = file.readLine();
		}
#ifdef __DEBUG
		qDebug() << "Tank points:";
		this->print(tank);
#endif
		currentLine = file.readLine();
		currentLine = file.readLine();
		while(currentLine.size() != 1)
		{
			point3d line;
			int i = 0;
			int e = 1;

			while(e <= 6)
			{
				QString point = currentLine.section(' ', i, i);
				if(point != "")
				{
					float p = point.toFloat();
					if( e == 1 ) { line.x1 = p; }
					else if ( e == 2 ) {line.y1 = p; }
					else if ( e == 3 ) {line.z1 = p; }
					else if ( e == 4 ) {line.x2 = p; }
					else if ( e == 5 ) {line.y2 = p; }
					else if ( e == 6 ) {line.z2 = p; }
					else{}
					e++;
				}
				i++;
			}
			deadTank.append(line);
			currentLine = file.readLine();
		}
#ifdef __DEBUG
		qDebug() << "Dead Tank points:";
		this->print(deadTank);
#endif
		currentLine = file.readLine();
		currentLine = file.readLine();
		while(currentLine.size() != 1)
		{
			point3d line;
			int i = 0;
			int e = 1;

			while(e <= 6)
			{
				QString point = currentLine.section(' ', i, i);
				if(point != "")
				{
					float p = point.toFloat();
					if( e == 1 ) { line.x1 = p; }
					else if ( e == 2 ) {line.y1 = p; }
					else if ( e == 3 ) {line.z1 = p; }
					else if ( e == 4 ) {line.x2 = p; }
					else if ( e == 5 ) {line.y2 = p; }
					else if ( e == 6 ) {line.z2 = p; }
					else{}
					e++;
				}
				i++;
			}
			projectile.append(line);
			currentLine = file.readLine();
		}
#ifdef __DEBUG
		qDebug() << "Projectile points:";
		this->print(projectile);
#endif
	}
}

void model::print(QList<point3d> printMe)
{
	for(int i = 0; i < printMe.size(); i++)
	{
		qDebug() << printMe[i].x1 << "  " << printMe[i].y1 << "  " << printMe[i].z1 << "      "
				 << printMe[i].x2 << "  " << printMe[i].y2 << "  " << printMe[i].z2 << endl;
	}
}
