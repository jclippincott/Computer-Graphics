/*
 * InteriorFill.cpp
 *
 *  Created on: Oct 25, 2017
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

class pixColor
{
private:
	float r,g,b;
public:
	pixColor()
	{
		r = 0;
		g = 0;
		b = 0;
	}
	pixColor(float a1, float b1, float c1)
	{
		r = a1;
		g = b1;
		b = c1;
	}
	void setR(float a)
	{
		r = a;
	}
	void setG(float a)
	{
		g = a;
	}
	void setB(float a)
	{
		b = a;
	}

	float getR()
	{
		return r;
	}
	float getG()
	{
		return g;
	}
	float getB()
	{
		return b;
	}

	void setNewVals(float a1, float b1, float c1)
	{
		r = a1;
		g = b1;
		b = c1;
	}

	bool isEqual(pixColor compare)
	{
		bool equal = false;

		if ((compare.getR() == r) && (compare.getG() == g) && (compare.getB() == b))
		{
			equal = true;
		}
		return equal;
	}

	void print()
	{
		cout << "RGB: " << r << "," << g << "," << b << endl;
	}
};

class screenPt
{
private:
	int x, y;
public:
	/* Default Constructor: initializes coordinate position to (0, 0). */
	screenPt()
	{
		x = y = 0;
	}
	void setCoords (int xCoordValue, int yCoordValue)
	{
		x = xCoordValue;
		y = yCoordValue;
	}
	int getx ( ) const
	{
		return x;
	}
	int gety ( ) const
	{
		return y;
	}
	void incrementx ( )
	{
		x++;
	}
	void decrementy ( )
	{
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
		glVertex3f(x,y,0);
	glEnd();
//	glFlush();
}

void setPixel(float x, float y, pixColor color)
{
	glColor3f(color.getR(),color.getG(),color.getB());
	glBegin(GL_POINTS);
		glVertex3f(x,y,0);
	glEnd();
}

pixColor getPixel (int x, int y)
{
	pixColor color;
	glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,&color);
	return color;
}

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

void floodFill4 (int x, int y, pixColor fillColor, pixColor interiorColor)
{
	pixColor color;
	/* Set current color to fillColor, then perform the following operations. */
	color = getPixel (x, y);

	if (color.isEqual(interiorColor))
	{
//		cout << x << ", " << y << endl;
		setPixel (x, y, fillColor); // Set color of pixel to fillColor.
		floodFill4 (x + 1, y, fillColor, interiorColor);
		floodFill4 (x - 1, y, fillColor, interiorColor);
		floodFill4 (x, y + 1, fillColor, interiorColor);
		floodFill4 (x, y - 1, fillColor, interiorColor);
	}
}

void boundaryFill4 (int x, int y, pixColor fillColor, pixColor borderColor)
{
	pixColor interiorColor;
	/* Set current color to fillColor, then perform the following operations. */
	interiorColor = getPixel (x, y);
	if((!(interiorColor.isEqual(borderColor))) && (!(interiorColor.isEqual(fillColor))))
	{
		cout << x << ", " << y << endl;
		setPixel (x, y, fillColor); // Set color of pixel to fillColor.
		boundaryFill4 (x + 1, y , fillColor, borderColor);
		boundaryFill4 (x - 1, y , fillColor, borderColor);
		boundaryFill4 (x , y + 1, fillColor, borderColor);
		boundaryFill4 (x , y - 1, fillColor, borderColor);
	}
}

void boundaryFill8 (int x, int y, pixColor fillColor, pixColor borderColor)
{
	glClear(GL_COLOR_BUFFER_BIT);
	pixColor interiorColor;
	/* Set current color to fillColor, then perform the following operations. */
	interiorColor = getPixel(x, y);
	if((!(interiorColor.isEqual(borderColor))) && (!(interiorColor.isEqual(fillColor))))
	{
		cout << x << ", " << y << endl;
		setPixel (x, y, fillColor); // Set color of pixel to fillColor.
		boundaryFill8 (x + 1, y, fillColor, borderColor);
		boundaryFill8 (x - 1, y, fillColor, borderColor);
		boundaryFill8 (x , y + 1, fillColor, borderColor);
		boundaryFill8 (x , y - 1, fillColor, borderColor);
		boundaryFill8 (x - 1, y - 1, fillColor, borderColor);
		boundaryFill8 (x + 1, y - 1, fillColor, borderColor);
		boundaryFill8 (x - 1, y + 1, fillColor, borderColor);
		boundaryFill8 (x + 1, y + 1, fillColor, borderColor);
	}
}

void drawEllipse()
{
	pixColor fillColor(0.0,0.0,0.0);
	pixColor borderColor(0.0,0.0,1.0);
	pixColor interiorColor(1.0,1.0,1.0);

	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();


	//Ellipse 1
	glColor3f(0,0,1);
	ellipseMidpoint(200,650,95,75);
//	floodFill4(200,650,fillColor,interiorColor);
	boundaryFill4(200,650,fillColor,borderColor);
	glFlush();

	//Ellipse 2
	glColor3f(0,0,0);
	fillColor.setNewVals(1.0,0.0,0.0);
	borderColor.setNewVals(0,0,0);
	ellipseMidpoint(400,650,95,75);
//	floodFill4(400,650,fillColor,interiorColor);
	boundaryFill4(400,650,fillColor,borderColor);
	glFlush();

	//Ellipse 3
	glColor3f(1,0,0);
	fillColor.setNewVals(1.0,1.0,0.0);
	borderColor.setNewVals(1,0,0);
	ellipseMidpoint(600,650,95,75);
//	floodFill4(600,650,fillColor,interiorColor);
	boundaryFill4(600,650,fillColor,borderColor);
	glFlush();

	//Ellipse 4
	glColor3f(1,1,0);
	fillColor.setNewVals(0.0,1.0,0.0);
	borderColor.setNewVals(1,1,0);
	ellipseMidpoint(300,550,95,75);
//	floodFill4(300,550,fillColor,interiorColor);
	boundaryFill4(300,550,fillColor,borderColor);
	glFlush();

	//Ellipse 5
	glColor3f(0,1,0);
	fillColor.setNewVals(0,0,1);
	borderColor.setNewVals(0,1,0);
	ellipseMidpoint(500,550,95,75);
//	floodFill4(500,550,fillColor,interiorColor);
	boundaryFill4(500,550,fillColor,borderColor);
	glFlush();
}

int main (int argc, char ** argv)
{
//	glEnable(GL_LINE_SMOOTH);
	glutInit(&argc, argv); //leave
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //single buffer, rgb color scheme
	glutInitWindowPosition(0,0); //tells where to create the window
	glutInitWindowSize(800,800); //window size
	glutCreateWindow("Filled Olympic Rings"); //title of the window
	init(); //leave for now
	glutDisplayFunc(drawEllipse); //runs function to show inside window that just was created
	glutMainLoop(); //
}
