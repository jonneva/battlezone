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

void object3d::render(bool reorient)
{
	glRotatef(angle, 0.0f, 1.0f, 0.0f);

//	glPushMatrix();
	if(reorient) {
//		glLoadIdentity();
//		glPushMatrix();
//		glTranslatef(cameraX, cameraY, 0);
//		gluLookAt(cameraX, cameraY, cameraZ,
//				  cameraX + losX, cameraY + losY, cameraZ + losZ,
//				  0.0f, 1.0f, 0.0f);
	}
	glBegin(GL_LINES);
		// For every line in the model, render that line
		for(int line = 0; line < model3d.size(); line++) {
			 // Changed x/y/z order to account for model perspective differences
			glVertex3f(-model3d[line].x1, model3d[line].z1, -model3d[line].y1);
			glVertex3f(-model3d[line].x2, model3d[line].z2, -model3d[line].y2);
		}
	glEnd();
//	glPopMatrix();
	glLoadIdentity();
}
