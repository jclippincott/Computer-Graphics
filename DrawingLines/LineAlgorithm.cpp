/*
 * LineAlgorithm.cpp
 *
 *  Created on: Oct 16, 2017
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

void print(string text)
{
	cout << text << endl;
}

void print(int text)
{
	cout << text << endl;
}

void init(void)
{
	glClearColor(1.0,1.0,1.0,0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,200,0.0,200.0);

}

void setPixel(float x, float y)
{
	glBegin(GL_POINTS);
		glVertex3f(x,y,0);
	glEnd();
//	glFlush();
}

void lineDDA (int x1, int y1, int x2, int y2)
{

	int dx = x2-x1;
	int dy = y2 - y1;
	int steps, k;
	float xIncrement, yIncrement;
	float x = x1;
	float y = y1;
	if (fabs (dx) > fabs (dy))
		steps = fabs (dx);
	else
		steps = fabs (dy);
	xIncrement = float (dx) / float (steps);
	yIncrement = float (dy) / float (steps);
	setPixel (round (x), round (y));
	for (k = 0; k < steps; k++) {
		x += xIncrement;
		y += yIncrement;
		setPixel (round (x), round (y));
	}
}


void lineBresenham (int x0, int y0, int xEnd, int yEnd)
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


void drawLineBresenham ()
{
	glClear(GL_COLOR_BUFFER_BIT);
	//house 1
	glColor3f (0.0, 0.0, 0.0);
	lineBresenham(5,5,5,20);
	lineBresenham(5,20,47,20);
	lineBresenham(47,5,47,20);
	lineBresenham(5,5,47,5);
	lineBresenham(5,20,26,41);
	lineBresenham(26,41,47,20);
	//house 2
	glColor3f (0.6, 0.4, 0.3);
	lineBresenham(55,5,55,20);
	lineBresenham(55,20,97,20);
	lineBresenham(97,5,97,20);
	lineBresenham(55,5,97,5);
	lineBresenham(55,20,76,100);
	lineBresenham(76,100,97,20);
	//house 3
	glColor3f (0.6, 0.0, 0.3);
	lineBresenham(105,5,105,20);
	lineBresenham(105,20,147,20);
	lineBresenham(147,5,147,20);
	lineBresenham(105,5,147,5);
	lineBresenham(105,20,126,25);
	lineBresenham(126,25,147,20);
	//star
	glColor3f(1.0,1.0,0.0);
	lineBresenham(105,100,147,100);
	lineBresenham(126,76,126,124);
	lineBresenham(147,124,105,76);
	lineBresenham(105,124,147,76);
	lineBresenham(137,76,116,124);
	lineBresenham(137,124,116,76);
	lineBresenham(147,88,105,112);
	lineBresenham(147,112,105,88);
	glFlush();
}

void drawLineDDA ()
{
	glClear(GL_COLOR_BUFFER_BIT);
	//house 1
	glColor3f (0.0, 0.0, 0.0);
	lineDDA(5,5,5,20);
	lineDDA(5,20,47,20);
	lineDDA(47,5,47,20);
	lineDDA(5,5,47,5);
	lineDDA(5,20,26,41);
	lineDDA(26,41,47,20);
	//house 2
	glColor3f (0.6, 0.4, 0.3);
	lineDDA(55,5,55,20);
	lineDDA(55,20,97,20);
	lineDDA(97,5,97,20);
	lineDDA(55,5,97,5);
	lineDDA(55,20,76,100);
	lineDDA(76,100,97,20);
	//house 3
	glColor3f (0.6, 0.0, 0.3);
	lineDDA(105,5,105,20);
	lineDDA(105,20,147,20);
	lineDDA(147,5,147,20);
	lineDDA(105,5,147,5);
	lineDDA(105,20,126,25);
	lineDDA(126,25,147,20);
	//star
	glColor3f(1.0,1.0,0.0);
	lineDDA(105,100,147,100);
	lineDDA(126,76,126,124);
	lineDDA(147,124,105,76);
	lineDDA(105,124,147,76);
	lineDDA(137,76,116,124);
	lineDDA(137,124,116,76);
	lineDDA(147,88,105,112);
	lineDDA(147,112,105,88);
	glFlush();
}

int main (int argc, char ** argv)
{
	glEnable(GL_LINE_SMOOTH);
	glutInit(&argc, argv); //leave
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //single buffer, rgb color scheme
	glutInitWindowPosition(0,0); //tells where to create the window
	glutInitWindowSize(200,200); //window size
	//glutCreateWindow("BuildingDDA"); //title of the window
	glutCreateWindow("BuildingBresenham"); //title of the window
	init(); //leave for now
	//glutDisplayFunc(drawLineDDA);
	glutDisplayFunc(drawLineBresenham); //runs function to show inside window that just was created
//	glutReshapeFunc(WavingFlag);
	glutMainLoop(); //
}
