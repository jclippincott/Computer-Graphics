/*
 * PixelArt.cpp
 *
 *  Created on: Sep 12, 2017
 *      Author: Jesse
 */

#include <string>
#include <iostream>
#include <GL/glut.h>
#include <windows.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include "PixelArt.h"
#include <math.h>

using namespace std;

#include "PixelArt.h"

void init(void)
{
	glClearColor(0.8,0.8,0.8,0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,800,0.0,800.0);

}

void setPixel(float x, float y, float a, float b, float c)
{
	glColor3f(a,b,c);
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
//	glFlush();
}

void pixelCircle (float r, float x, float y, bool filled)
{
	int i,j,xCheck,yCheck, count;
	float d2r;

//draws fill for the circle
	if (filled)
	{
		for(i=0;i<glutGet(GLUT_WINDOW_WIDTH);i++)
		{
			for(j=0;j<glutGet(GLUT_WINDOW_HEIGHT);j++)
			{
				xCheck = x-i;
				yCheck = y-j;
				if ((xCheck*xCheck + yCheck*yCheck) <= (r*r))
				{
					setPixel(i,j,1,1,0);
					if(j==0)
						glFlush();
				}
			}
		}
	}

//draws black outline of eyes
	for(i=0;i<glutGet(GLUT_WINDOW_WIDTH);i++)
	{
		for(j=glutGet(GLUT_WINDOW_HEIGHT)/2;j<glutGet(GLUT_WINDOW_HEIGHT);j++)
		{
			xCheck = x-i;
			yCheck = y-j;
			if ((xCheck*xCheck + yCheck*yCheck) <= ((r/3)*(r/3)))
			{
				setPixel(i-(glutGet(GLUT_WINDOW_WIDTH)/9),j+(glutGet(GLUT_WINDOW_WIDTH)/20),0,0,0);
				setPixel(i+(glutGet(GLUT_WINDOW_WIDTH)/9),j+(glutGet(GLUT_WINDOW_WIDTH)/20),0,0,0);
				if(j==0)
					glFlush();
			}
		}
	}

//draws yellow coverup for the bottom part of eyes
	for(i=0;i<glutGet(GLUT_WINDOW_WIDTH);i++)
	{
		for(j=glutGet(GLUT_WINDOW_HEIGHT)/2;j<glutGet(GLUT_WINDOW_HEIGHT);j++)
		{
			xCheck = x-i;
			yCheck = y-j;
			if ((xCheck*xCheck + yCheck*yCheck) <= ((r/4)*(r/4)))
			{
				setPixel(i-(glutGet(GLUT_WINDOW_WIDTH)/9),j+(glutGet(GLUT_WINDOW_WIDTH)/20),1,1,0);
				setPixel(i+(glutGet(GLUT_WINDOW_WIDTH)/9),j+(glutGet(GLUT_WINDOW_WIDTH)/20),1,1,0);
				if(j==0)
					glFlush();
			}
		}
	}

//draws mouth

	for(i=0;i<glutGet(GLUT_WINDOW_WIDTH);i++)
	{
		for(j=0;j<glutGet(GLUT_WINDOW_HEIGHT)/2;j++)
		{
			xCheck = x-i;
			yCheck = y-j;
			if ((xCheck*xCheck + yCheck*yCheck) <= ((r/2)*(r/2)))
			{
				setPixel(i,j-(glutGet(GLUT_WINDOW_WIDTH)/20),0,0,0);
				if(j==0)
					glFlush();
			}
		}
	}

	glPointSize(5);

	for(i=0;i<360;i++)
	{
		d2r = i* (M_PI/180);
		setPixel(x+cos(d2r)*r,y+sin(d2r)*r, 0,0,0);
	}


	glPointSize(1);
	glFlush();
}

//Implemented this before I looked and saw that we can only use GL_POINTS. I didn't use this code to draw any of my circles or anything
//void circle (float r, float x, float y, bool filled)
//{
//	int i;
//	float d2r;
//	if (filled)
//	{
//		glBegin(GL_POLYGON);
//		for(i=0;i<360;i++)
//		{
//			d2r = i*(M_PI/180);
//			glVertex2f(cos(d2r)*r,sin(d2r)*r);
//		}
//		glEnd();
//	}
//
//
//	glBegin(GL_LINE_LOOP);
//	for(i=0;i<360;i++)
//	{
//		d2r = i* (M_PI/180);
//		glVertex2f(cos(d2r)*r,sin(d2r)*r);
//	}
//	glEnd();
//	glFlush();
//}

void PixelArt()
{
	glClear(GL_COLOR_BUFFER_BIT);
	float centerX, centerY;
	int i;

	if ((glutGet(GLUT_WINDOW_HEIGHT))%2==0)
	{
		centerY = (glutGet(GLUT_WINDOW_HEIGHT))/2;
	}
	else
	{
		centerY = floor(((glutGet(GLUT_WINDOW_HEIGHT))/2))+1;
	}

	if ((glutGet(GLUT_WINDOW_WIDTH))%2==0)
		{
			centerX = (glutGet(GLUT_WINDOW_WIDTH))/2;
		}
	else
	{
		centerX = floor(((glutGet(GLUT_WINDOW_WIDTH))/2))+1;
	}

	glColor3f(1,1,0);
	pixelCircle((glutGet(GLUT_WINDOW_HEIGHT)/4),centerX,centerY,true);
}

int main (int argc, char ** argv)
{
	glBegin;
	glEnable(GL_LINE_SMOOTH);
	glutInit(&argc, argv); //leave
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //single buffer, rgb color scheme
	glutInitWindowPosition(0,0); //tells where to create the window
	glutInitWindowSize(800,800); //window size
	glutCreateWindow("Emoji"); //title of the window
	init(); //leave for now
	glutDisplayFunc(PixelArt); //runs function to show inside window that just was created
	glutMainLoop(); //
}
