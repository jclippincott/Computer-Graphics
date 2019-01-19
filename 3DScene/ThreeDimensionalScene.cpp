/*
 * ThreeDimensionalScene.cpp
 *
 *  Created on: Dec 6, 2017
 *      Author: Jesse
 */

#include <math.h>
#include <GL/glut.h>
#include <windows.h>
#include <GL/glu.h>
#include <GL/gl.h>

using namespace std;

GLint winWidth = 600, winHeight = 600; // Initial display-window size.
GLdouble xView = 0.0, zView = 0.0, yView = 0.0; // Viewing-coordinate origin.
GLfloat xref = 50.0, yref = 50.0, zref = 0.0; // Look-at point.
GLfloat Vx = 0.0, Vy = 1.0, Vz = 0.0; // View-up vector.

/* Set coordinate limits for the clipping window: */
GLfloat xwMin = -40.0, ywMin = -60.0, xwMax = 40.0, ywMax = 60.0;

/* Set positions for near and far clipping planes: */
GLfloat dnear = 25.0, dfar = 125.0;
void init (void)
{
	glClearColor (1.0, 1.0, 1.0, 0.0);

	glMatrixMode (GL_MODELVIEW);
	gluLookAt(xView, yView, zView, xref, yref, zref, Vx, Vy, Vz);

	glMatrixMode (GL_PROJECTION);
	glFrustum (xwMin, xwMax, ywMin, ywMax, dnear, dfar);
}
void displayFcn (void)
{
	glClear (GL_COLOR_BUFFER_BIT);

	/* Set parameters for a square fill area. */
//	glColor3f (0.0, 1.0, 0.0); // Set fill color to green.
//	glPolygonMode (GL_FRONT, GL_FILL);
//	glPolygonMode (GL_BACK, GL_LINE); // Wire-frame back face.
//	glBegin (GL_QUADS);
//		glVertex3f (0.0, 0.0, 0.0);
//		glVertex3f (100.0, 0.0, 0.0);
//		glVertex3f (100.0, 100.0, 0.0);
//		glVertex3f (0.0, 100.0, 0.0);
//	glEnd ( );

	float sphereX = 0;
	float sphereY = 0;
	float sphereZ = 50;

	glBegin(GL_QUAD_STRIP);
		for (float i = 0; i < (2*M_PI); i+=0.001)
		{
			for (float j = 0; j < M_PI; j+=0.1)
			{
				float newX = sphereX + (20 * cos(i) * sin(j));
				float newZ = sphereZ + (20 * sin(i) * sin(i));
				float newY = sphereY + (20 * cos(j));

				glVertex3f(newX,newY,newZ);

			}
		}

	glEnd();
	glFlush ( );
}
void reshapeFcn (GLint newWidth, GLint newHeight)
{
	glViewport (0, 0, newWidth, newHeight);

	winWidth = newWidth;
	winHeight = newHeight;
}
int main (int argc, char** argv)
{
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition (50, 50);
	glutInitWindowSize (winWidth, winHeight);
	glutCreateWindow ("Perspective View of A Square");
	init ( );
	glutDisplayFunc (displayFcn);
	glutReshapeFunc (reshapeFcn);
	glutMainLoop ( );
}
