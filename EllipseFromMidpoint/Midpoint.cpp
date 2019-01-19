/*
 * Midpoint.cpp
 *
 *  Created on: Oct 19, 2017
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

class screenPt
{
private:
	int x, y;
public:
	/* Default Constructor: initializes coordinate position to (0, 0). */
	screenPt ( ) {
	x = y = 0;
	}
	void setCoords (int xCoordValue, int yCoordValue) {
	x = xCoordValue;
	y = yCoordValue;
	}
	int getx ( ) const {
		return x;
	}
	int gety ( ) const {
	return y;
	}
	void incrementx ( ) {
	x++;
	}
	void decrementy ( ) {
	y--;
	}
};

void init(void)
{
	glClearColor(1.0,1.0,1.0,0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,800,0.0,800.0);

}

void setPixel(float x, float y)
{
	glBegin(GL_POINTS);
		glVertex3i(x,y,1);
	glEnd();
//	glFlush();
}

/* The following procedure accepts values for an ellipse
* center position and its semimajor and semiminor axes, then
* calculates ellipse positions using the midpoint algorithm.
*/
void ellipseMidpoint (int xCenter, int yCenter, int Rx, int Ry)
{
	int Rx2 = Rx * Rx;
	int Ry2 = Ry * Ry;
	int twoRx2 = 2 * Rx2;
	int twoRy2 = 2 * Ry2;
	int p;
	int x = 0;
	int y = Ry;
	int px = 0;
	int py = twoRx2 * y;
	void ellipsePlotPoints (int, int, int, int);
	/* Plot the initial point in each quadrant. */
	ellipsePlotPoints (xCenter, yCenter, x, y);
	/* Region 1 */
	p = round (Ry2 - (Rx2 * Ry) + (0.25 * Rx2));
	while (px < py) {
		x++;
		px += twoRy2;
		if (p < 0)
			p += Ry2 + px;
		else {
			y--;
			py -= twoRx2;
			p += Ry2 + px - py;
		}
		ellipsePlotPoints (xCenter, yCenter, x, y);
	}
	/* Region 2 */
	p = round (Ry2 * (x+0.5) * (x+0.5) + Rx2 * (y-1) * (y-1) - Rx2 * Ry2);
	while (y > 0) {
		y--;
		py -= twoRx2;
		if (p > 0)
			p += Rx2 - py;
		else {
			x++;
			px += twoRy2;
			p += Rx2 - py + px;
		}
		ellipsePlotPoints (xCenter, yCenter, x, y);
	}
}

void ellipsePlotPoints (int xCenter, int yCenter, int x, int y)
{
setPixel (xCenter + x, yCenter + y);
setPixel (xCenter - x, yCenter + y);
setPixel (xCenter + x, yCenter - y);
setPixel (xCenter - x, yCenter - y);
}

void circleMidpoint (GLint xc, GLint yc, GLint radius)
{
	screenPt circPt;
	GLint p = 1 - radius; // Initial value for midpoint parameter.
	circPt.setCoords (0, radius); // Set coordinates for top point of circle.
	void circlePlotPoints (GLint, GLint, screenPt);
	/* Plot the initial point in each circle quadrant. */
	circlePlotPoints (xc, yc, circPt);
	/* Calculate next point and plot in each octant. */
	while (circPt.getx ( ) < circPt.gety ( )) {
		circPt.incrementx ( );
		if (p < 0)
			p += 2 * circPt.getx ( ) + 1;
		else {
			circPt.decrementy ( );
			p += 2 * (circPt.getx ( ) - circPt.gety ( )) + 1;
		}
		circlePlotPoints (xc, yc, circPt);
	}
}
void circlePlotPoints (GLint xc, GLint yc, screenPt circPt)
{
	setPixel (xc + circPt.getx ( ), yc + circPt.gety ( ));
	setPixel (xc - circPt.getx ( ), yc + circPt.gety ( ));
	setPixel (xc + circPt.getx ( ), yc - circPt.gety ( ));
	setPixel (xc - circPt.getx ( ), yc - circPt.gety ( ));
	setPixel (xc + circPt.gety ( ), yc + circPt.getx ( ));
	setPixel (xc - circPt.gety ( ), yc + circPt.getx ( ));
	setPixel (xc + circPt.gety ( ), yc - circPt.getx ( ));
	setPixel (xc - circPt.gety ( ), yc - circPt.getx ( ));
}

void drawCircle()
{
	glPointSize(3);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,0,1);
	circleMidpoint(200,650,95);
	glColor3f(0,0,0);
	circleMidpoint(400,650,95);
	glColor3f(1,0,0);
	circleMidpoint(600,650,95);
	glColor3f(1,1,0);
	circleMidpoint(300,550,95);
	glColor3f(0,1,0);
	circleMidpoint(500,550,95);
	glFlush();
}

void drawEllipse()
{
	glPointSize(3);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,0,1);
	ellipseMidpoint(200,650,95,75);
	glColor3f(0,0,0);
	ellipseMidpoint(400,650,95,75);
	glColor3f(1,0,0);
	ellipseMidpoint(600,650,95,75);
	glColor3f(1,1,0);
	ellipseMidpoint(300,550,95,75);
	glColor3f(0,1,0);
	ellipseMidpoint(500,550,95,75);
	glFlush();
}

int main (int argc, char ** argv)
{
	glEnable(GL_LINE_SMOOTH);
	glutInit(&argc, argv); //leave
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //single buffer, rgb color scheme
	glutInitWindowPosition(0,0); //tells where to create the window
	glutInitWindowSize(800,800); //window size
	//glutCreateWindow("BuildingDDA"); //title of the window
	glutCreateWindow("Olympic Rings"); //title of the window
	init(); //leave for now
	//glutDisplayFunc(drawLineDDA);
	glutDisplayFunc(drawEllipse); //runs function to show inside window that just was created
//	glutReshapeFunc(WavingFlag);
	glutMainLoop(); //
}


