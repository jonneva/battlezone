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

#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <QGLWidget>

// Represents a point in 3D space
typedef struct point3d {
	float x1;
	float y1;
	float z1;
	float x2;
	float y2;
	float z2;
};

// Represents a 3D model
class object3d {
public:
	object3d();
	object3d(QList<point3d> &lines);
	void render(bool reorient = false);
	QList<point3d> model3d;
	GLfloat angle;

	// This object's orientation, if used
	GLfloat cameraX, cameraY, cameraZ; // Camera position
	GLfloat losX, losY, losZ; // Line of site to orienting object
};
#endif // OBJECT3D_H
