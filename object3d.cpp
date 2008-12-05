#include "object3d.h"

// If no QList<point3d sent in parameter, must be manually set through public variable model3d
object3d::object3d()
{
	angle = 0.0f;
}

object3d::object3d(QList<point3d> &lines)
{
	model3d = lines;
	angle = 0.0f;
}
//	if (rotationDegrees >= 360.0f)
//		rotationDegrees = 0.0f;

void object3d::render(GLfloat rot)
{
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
//	glBegin(GL_POLYGON);
	glBegin(GL_LINES);
		for(int line = 0; line < model3d.size(); line++) {
			glVertex3f(-model3d[line].x1, model3d[line].z1, -model3d[line].y1); // Changed x/y/z order to account for model perspective differences
			glVertex3f(-model3d[line].x2, model3d[line].z2, -model3d[line].y2);
		}
	glEnd();
	glLoadIdentity();
}
