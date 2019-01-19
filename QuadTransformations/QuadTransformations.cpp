/*
 * QuadTransformations.cpp
 *
 *  Created on: Nov 2, 2017
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

void init(void)
{
	glClearColor(1.0,1.0,1.0,0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,300,0.0,300.0);
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

class newQuad
{
private:
	float xCoords[4];
	float yCoords[4];
public:
	newQuad()
	{
		for (int i = 0; i < 4; i++)
		{
			xCoords[i] = 0;
			yCoords[i] = 0;
		}
	}

	newQuad(float coords[])
	{
		for(int i = 0; i < 4; i++)
		{
			xCoords[i] = coords[i*2];
			yCoords[i] = coords[(i*2)+1];
		}
	}

	void rotate(float xPt, float yPt, float rads)
	{
		for(int i = 0; i < 4; i++)
		{
			float x = xCoords[i];
			float y = yCoords[i];
			xCoords[i] = xPt + ((x - xPt) * cos(rads)) - ((y - yPt) * sin(rads));
			yCoords[i] = yPt + ((x - xPt) * sin(rads)) + ((y - yPt) * cos(rads));
		}
	}

	void translate (float xt, float yt)
	{
		for(int i = 0; i < 4; i++)
		{
			xCoords[i] += xt;
			yCoords[i] += yt;
		}
	}

	void scale (float xFix, float yFix, float xScale, float yScale)
	{
		for(int i = 0; i < 4; i++)
		{
			xCoords[i] = (xCoords[i] * xScale) + (xFix*(1-xScale));
			yCoords[i] = (yCoords[i] * yScale) + (yFix*(1-yScale));
		}
	}

	void display (pixColor fillColor,pixColor borderColor)
	{
		glClear(GL_COLOR_BUFFER_BIT);
//		for(int i = 0; i < 4; i++)
//		{
//			cout << xCoords[i] << "," << yCoords[i] << endl;
//		}
		int centerX = 0;
		int centerY = 0;
		pixColor white(1,1,1);
		glBegin(GL_LINE_LOOP);
			glColor3f(borderColor.getR(),borderColor.getG(),borderColor.getB());
			for(int i = 0; i < 4; i++)
			{
				glVertex2f(xCoords[i],yCoords[i]);
				centerX += xCoords[i];
				centerY += yCoords[i];
			}
		glEnd();
		centerX /= 4;
		centerY /= 4;

		floodFill4(centerX,centerY,fillColor,white);
		glFlush();

	}
};

void drawAndTransform()
{
	glClear(GL_COLOR_BUFFER_BIT);
	float coords[8] {0.0,100.0,50.0,150.0,100.0,100.0,50.0,25.0};
	pixColor blue(0,0,1);
	pixColor red(1,0,0);
	float rads = (5*M_PI) /3;
	float degrees = rads * (180/M_PI);


//Code for personally made functions
//	newQuad baseLine(coords);
//	newQuad transform(coords);
//	baseLine.display(blue,blue);
//
//	transform.rotate(50,10,rads);
//	transform.translate(0,100);
//	transform.scale(200,200,0.5,0.5);
//
//	transform.display(red,red);


//Code for the OpenGL functions
	glBegin(GL_POLYGON);
		glColor3f(0,0,1);
		for(int i = 0; i < 4; i++)
		{
			glVertex2f(coords[i*2], coords[(i*2)+1]);
		}
	glEnd();

		glTranslatef(143,96.5,0);
		glTranslatef(50,68.75,0);
		glRotatef(degrees,0,0,1);
		glTranslatef(-50,-68.75,0);
		glScalef(0.5,0.5,0);

		glBegin(GL_POLYGON);
		glColor3f(1,0,0);
		for(int i = 0; i < 4; i++)
		{
			glVertex2f(coords[i*2], coords[(i*2)+1]);
		}
		glEnd();

	glFlush();

}

int main (int argc, char ** argv)
{
//	glEnable(GL_LINE_SMOOTH);
	glutInit(&argc, argv); //leave
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //single buffer, rgb color scheme
	glutInitWindowPosition(0,0); //tells where to create the window
	glutInitWindowSize(300,300); //window size
	glutCreateWindow("Filled Olympic Rings"); //title of the window
	init(); //leave for now
	glutDisplayFunc(drawAndTransform); //runs function to show inside window that just was created
	glutMainLoop(); //
}
