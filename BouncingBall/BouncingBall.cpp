/*
 * BouncingBall.cpp
 *
 *  Created on: Nov 27, 2017
 *      Author: Jesse
 */

#include <stdlib.h>
#include <math.h>
#include <string>
#include <iostream>
#include <GL/glut.h>
#include <windows.h>
#include <GL/glu.h>
#include <GL/gl.h>

using namespace std;

const double TWO_PI = 6.2831853;

GLsizei winWidth = 500, winHeight = 500; // Initial display window size.
GLuint regHex; // Define name for display list.
static GLfloat rotTheta = 0.0;
GLfloat newX = -150.0;
GLfloat newY = 200.0;

class scrPt {
public:
	GLint x, y;
};

static void init (void)
{
	scrPt hexVertex;
	GLdouble hexTheta;
	GLint i,k;

	glClearColor (1.0, 1.0, 1.0, 0.0);
	/* Set up a display list for a red regular hexagon.
	* Vertices for the hexagon are six equally spaced
	* points around the circumference of a circle.
	*/

	regHex = glGenLists (1);
	glNewList (regHex, GL_COMPILE);
	glColor3f (1.0, 0.0, 0.0);
	glBegin (GL_POLYGON);
	for (k = 0; k < 66; k++) {
		hexTheta = TWO_PI * k / 50;
		hexVertex.x = 50 * cos (hexTheta);
		hexVertex.y = 50 * sin (hexTheta);
		glVertex2i (hexVertex.x, hexVertex.y);
	}

	glColor3f(0,1,0);
	for (i = 0; i < 3; i++)
	{
		hexTheta = TWO_PI * i / 3;
		hexVertex.x = 50 * cos (hexTheta);
		hexVertex.y = 50 * sin (hexTheta);
		glVertex2i (hexVertex.x, hexVertex.y);
	}

	glEnd ( );
	glEndList ( );
}
void displayHex (void)
{
	glClear (GL_COLOR_BUFFER_BIT);

	glPushMatrix ( );
	glTranslatef (newX,newY,0);
	glRotatef (rotTheta, 0.0, 0.0, 1.0);
	glCallList (regHex);
	glPopMatrix ( );

	glutSwapBuffers ( );

	glFlush ( );
}
void rotateHex (void)
{
	newX += 1;
	newY = 200 * fabs(sin((6.26*newX)+(TWO_PI))) * exp(-0.005*newX);

	rotTheta -= 2.0 - ((newX+150)/350);

	if (rotTheta > 360.0)
		rotTheta -= 360.0;

	glutPostRedisplay ( );
}

void winReshapeFcn (GLint newWidth, GLint newHeight)
{
	glViewport (0, 0, (GLsizei) newWidth, (GLsizei) newHeight);

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ( );
	gluOrtho2D (-320.0, 320.0, -320.0, 320.0);

	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ( );

	glClear (GL_COLOR_BUFFER_BIT);
}
void mouseFcn (GLint button, GLint action, GLint x, GLint y)
{
	switch (button) {
		case GLUT_MIDDLE_BUTTON: // Start the rotation.
			if (action == GLUT_DOWN)
				glutIdleFunc (rotateHex);
			break;
		case GLUT_RIGHT_BUTTON: // Stop the rotation.
			if (action == GLUT_DOWN)
				glutIdleFunc (NULL);
			break;
		default:
			break;
	}
}
void MyKeyboardFunc(unsigned char Key, int x, int y)
{
	switch(Key)
	{
		case 'a': glutIdleFunc (rotateHex); break;
		case 'b': glutIdleFunc (NULL); break;
	};
}
int main (int argc, char** argv)
{
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition (150, 150);
	glutInitWindowSize (winWidth, winHeight);
	glutCreateWindow ("Animation Example");

	init ( );
	glutDisplayFunc (displayHex);
	glutReshapeFunc (winReshapeFcn);
	//glutIdleFunc (rotateHex);
	glutMouseFunc (mouseFcn);
	glutKeyboardFunc(MyKeyboardFunc);
	glutMainLoop ( );
}
