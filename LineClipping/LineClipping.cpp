/*
 * LineClipping.cpp
 *
 *  Created on: Nov 10, 2017
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

void init(void)
{
	glClearColor(1.0,1.0,1.0,0.0);
	glMatrixMode(GL_PROJECTION);
//	gluOrtho2D(-51,51,-5.0,21.0);	//UNCOMMENT THIS FOR BUILT-IN
	gluOrtho2D(0,300,0,300);		//COMMENT THIS OUT FOR BUILT-IN
}

void setPixel(float x, float y)
{
	glBegin(GL_POINTS);
		glVertex3f(x,y,0);
	glEnd();
//	glFlush();
}

class wcPt2D
{
	private:
		GLfloat x, y;
	public:
	/* Default Constructor: initialize position as (0.0, 0.0). */
	wcPt2D()
	{
	x = y = 0.0;
	}

	void setCoords (GLfloat xCoord, GLfloat yCoord) {
	x = xCoord;
	y = yCoord;
	}
	GLfloat getx ( ) const {
	return x;
	}
	GLfloat gety ( ) const {
	return y;
	}
};

GLint clipTest (GLfloat p, GLfloat q, GLfloat * u1, GLfloat * u2)
{
	GLfloat r;
	GLint returnValue = true;
	if (p < 0.0) {
		r = q / p;
		if (r > *u2)
			returnValue = false;
		else
			if (r > *u1)
				*u1 = r;
	}
	else
		if (p > 0.0) {
		r = q / p;
		if (r < *u1)
			returnValue = false;
		else if (r < *u2)
			*u2 = r;
		}
		else
			/* Thus p = 0 and line is parallel to clipping boundary. */
			if (q < 0.0)
			/* Line is outside clipping boundary. */
				returnValue = false;

	return (returnValue);
}

void lineBres (int x0, int y0, int xEnd, int yEnd)
{
	int x1 = x0, x2 = xEnd, y1 = y0, y2 = yEnd;
	int dx = fabs(xEnd - x0);
	int dy = fabs(yEnd - y0);
	int p = 2 * dy - dx;
	int twoDy = 2 * dy;
	int twoDyMinusDx = 2 * (dy - dx);
	int twoDx = 2 * dx;
	int twoDxMinusDy = 2 * (dy - dx);
	int x, y;
	/* Determine which endpoint to use as start position. */
	if (x0 > xEnd) {
		x = xEnd;
		y = yEnd;
		xEnd = x0;
		yEnd = y0;
	}
	else {
		x = x0;
		y = y0;
	}
	//Delta x == 0
	if (dx == 0)
	{
		setPixel (x,y);
		while (y < yEnd)
		{
			y++;
			setPixel(x,y);
		}
	}

	//Delta y == 0
	else if (dy == 0)
	{
		setPixel(x,y);
		while (x < xEnd)
		{
			x++;
			setPixel(x,y);
		}
	}
	else
	{
		float m = float(y2-y1)/float(x2-x1);
		//print(m);
	//Delta y == delta x (slope == 1)
		if (m == 1)
		{
			setPixel(x,y);
			while (x < xEnd)
			{
				x++;
				y++;
				setPixel(x,y);
			}
		}
		else if (m == -1)
		{
			setPixel(x,y);
			while (x < xEnd)
			{
				x++;
				y--;
				setPixel(x,y);
			}
		}
		else if ((m < 1) && (m > 0))
		{

			setPixel (x, y);
			while (x < xEnd) {
				x++;
				if (p < 0)
					p += twoDy;
				else {
					y++;
					p += twoDyMinusDx;
				}
				setPixel (x, y);
			}
		}
		else if (m > 1)
		{
			p = twoDxMinusDy;
			setPixel (x, y);
			while (y < yEnd) {
				y++;
				if (p > 0)
					p -= twoDx;
				else {
					x++;
					p += twoDxMinusDy;
				}
				setPixel (x, y);
			}
		}
		else if ((m < 0) && (m > -1))
		{
			setPixel (x, y);
			while (x < xEnd) {
				x++;
				if (p < 0)
					p += twoDy;
				else {
					y--;
					p += twoDyMinusDx;
				}
				setPixel (x, y);
			}
		}
		else if (m < -1)
		{
			p = twoDxMinusDy;
			setPixel (x, y);
			while (y > yEnd) {
				y--;
				if (p > 0)
					p -= twoDx;
				else {
					x++;
					p += twoDxMinusDy;
				}
				setPixel (x, y);
			}
		}
		else
		{
			cout << "Cannot print line" << endl;
		}
	}
}

void lineClipLiangBarsk (wcPt2D winMin, wcPt2D winMax, wcPt2D p1, wcPt2D p2)
{
	GLfloat u1 = 0.0, u2 = 1.0, dx = p2.getx ( ) - p1.getx ( ), dy;
	if (clipTest (-dx, p1.getx ( ) - winMin.getx ( ), &u1, &u2))
		if (clipTest (dx, winMax.getx ( ) - p1.getx ( ), &u1, &u2)) {
			dy = p2.gety ( ) - p1.gety ( );
			if (clipTest (-dy, p1.gety ( ) - winMin.gety ( ), &u1, &u2))
				if (clipTest (dy, winMax.gety ( ) - p1.gety ( ), &u1, &u2)) {
				if (u2 < 1.0) {
					p2.setCoords (p1.getx ( ) + u2 * dx, p1.gety ( ) + u2 * dy);
				}
				if (u1 > 0.0) {
					p1.setCoords (p1.getx ( ) + u1 * dx, p1.gety ( ) + u1 * dy);
				}
				lineBres (round (p1.getx ( )), round (p1.gety ( )),
							round (p2.getx ( )), round (p2.gety ( )));
		}
	}
}

void drawMountain()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,0,0);
	glBegin(GL_LINE_STRIP);
		glVertex2i(-35,-50);
		glVertex2i(-20,30);
		glVertex2i(-12,-10);
		glVertex2i(5,50);
		glVertex2i(12,-10);
		glVertex2i(25,30);
		glVertex2i(40,-50);
		glVertex2i(-35,-50);
	glEnd();
	glBegin(GL_LINE_STRIP);
		glVertex2i(-25,0);
		glVertex2i(-20,-10);
		glVertex2i(-15,0);
	glEnd();
	glBegin(GL_LINE_STRIP);
		glVertex2i(-10,0);
		glVertex2i(-5,-10);
		glVertex2i(5,0);
		glVertex2i(7,-10);
		glVertex2i(10,0);
	glEnd();
	glBegin(GL_LINE_STRIP);
		glVertex2i(15,0);
		glVertex2i(20,-10);
		glVertex2i(30,0);
	glEnd();
	glFlush();
}

void drawMountainBres()
{
	float coords[60] {15,0,30,80,30,80,38,40,38,40,55,100,55,100,62,40,62,40,75,80,75,80,90,0,25,50,30,40,30,40,35,50,40,50,45,40,45,40,55,50,55,50,57,40,57,40,60,50,65,50,70,40,70,40,80,50,15,0,90,0};
	wcPt2D min,max,currentMin,currentMax;

	min.setCoords(0,45);
	max.setCoords(100,100);

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,0,0);
	for (int i = 0; i < 15; i++)
	{
		float x0 = coords[i*4];
		float y0 = coords[(i*4)+1];
		float x1 = coords[(i*4)+2];
		float y1 = coords[(i*4)+3];

		currentMin.setCoords(x0,y0);
		currentMax.setCoords(x1,y1);
		lineClipLiangBarsk(min,max,currentMin,currentMax);
	}

	glFlush();


}



int main (int argc, char ** argv)
{
	glEnable(GL_LINE_SMOOTH);
	glutInit(&argc, argv); //leave
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //single buffer, rgb color scheme
	glutInitWindowPosition(200,200); //tells where to create the window
//	glViewport(0,0,200,200);																	//UNCOMMENT FOR BUILT-IN
	glutInitWindowSize(300,300); //window size
	glutCreateWindow("Clipped Mountains"); //title of the window
	init(); //leave for now
//	glutDisplayFunc(drawMountain); //runs function to show inside window that just was created					//UNCOMMENT FOR BUILT-IN
	glutDisplayFunc(drawMountainBres);																			//COMMENT OUT FOR BUILT-IN
	glutMainLoop(); //
}
