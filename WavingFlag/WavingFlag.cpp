/*
 * WavingFlag.cpp
 *
 *  Created on: Sep 26, 2017
 *      Author: Jesse
 */

#include <string>
#include <iostream>
#include <GL/glut.h>
#include <windows.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <math.h>

using namespace std;

void init(void)
{
	glClearColor(1.0,1.0,1.0,0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,800,0.0,800.0);

}

void reshape (int width, int height)
{
	float reshapeRatio;
	if (height == 0)
	{
		height = 1;
	}

	reshapeRatio = width/height;
	glLoadIdentity();

	glViewport(0,0,width,height);
	gluPerspective(45,reshapeRatio,1,1000);
}

void setPixel(float x, float y, float a, float b, float c)
{
	glColor3f(a,b,c);
	glBegin(GL_POINTS);
		glVertex3i(x,y,1);
	glEnd();
//	glFlush();
}

void pixelCircle (float r, float x, float y)
{
	int i,j,xCheck,yCheck;
	float d2r;

//draws fill for the circle
	for(i=0;i<glutGet(GLUT_WINDOW_WIDTH);i++)
		{
			for(j=0;j<glutGet(GLUT_WINDOW_HEIGHT);j++)
			{
				xCheck = x-i;
				yCheck = y-j;
				if ((xCheck*xCheck + yCheck*yCheck) <= (r*r))
				{
					setPixel(i,j,1,.91,.067);
				}
			}
		}

	glFlush();
}

void drawLine (int lineWidth, int numVertices, double vertices[], float r, float g, float b)
{
	glLineWidth(lineWidth);
	glColor3f(r,g,b);
	glBegin(GL_LINES);
		for (int i = 0; i < numVertices; i++)
		{
			glVertex3f(vertices[i*2],vertices[(i*2)+1],0);
		}
	glEnd();
	glFlush();
	glLineWidth(1);
}

void drawTriangle (int lineWidth, int numVertices, double vertices[], float r, float g, float b)
{
	glLineWidth(lineWidth);
	glColor3f(r,g,b);
	glBegin(GL_TRIANGLES);
		for (int i = 0; i < numVertices; i++)
		{
			glVertex3f(vertices[i*2],vertices[(i*2)+1],0);
		}
	glEnd();
	glFlush();
	glLineWidth(1);
}

void drawPolygon(int lineWidth, int numVertices, double vertices[], float r, float g, float b)
{
	glLineWidth(lineWidth);
	glColor3f(r,g,b);
	glBegin(GL_POLYGON);
		for (int i = 0; i < numVertices; i++)
		{
			glVertex3f(vertices[i*2],vertices[(i*2)+1],0);
		}
	glEnd();
	glFlush();
	glLineWidth(1);
}

void WavingFlag ()
{
	glClear(GL_COLOR_BUFFER_BIT);

	int height = glutGet(GLUT_WINDOW_HEIGHT);
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int dWidth = width/40;
	int dHeight = height/40;

	double flagpole[4] = {dWidth*3,dHeight,dWidth*3.05,dHeight*36.25};
	double connector1[4] = {dWidth*3.75,dHeight*32,dWidth*5,dHeight*32};
	double connector2[4] = {dWidth*3.75,dHeight*22,dWidth*5,dHeight*22};
	double flag1[6] = {dWidth*5,dHeight*32.1,dWidth*5,dHeight*27,dWidth*10,dHeight*32.1};
	double flag2[16] = {dWidth*5,dHeight*27,dWidth*7,dHeight*30,dWidth*16,dHeight*30,dWidth*14,dHeight*25,dWidth*8,dHeight*22,dWidth*8,dHeight*22,dWidth*5,dHeight*22,dWidth*5,dHeight*27};
	double flag3[8] = {dWidth*8,dHeight*22,dWidth*14,dHeight*25,dWidth*16,dHeight*20.5,dWidth*6.5,dHeight*20.5,};

	//Flagpole
	drawLine(width/18,2,flagpole,0,0,0);

	//Ball on flagpole
	pixelCircle(dHeight,dWidth*3,dHeight*37);

	//Flag connectors
	drawLine(1,2,connector1,0,0,0);
	drawLine(1,2,connector2,0,0,0);

	drawTriangle(1,3,flag1,1,0,0);
	drawPolygon(1,8,flag2,1,0,0);
	drawPolygon(1,4,flag3,1,0,0);

	glColor3f(0.0,0.0,0.0);
	glRasterPos2f(height/2,width/2);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	char * word = "Red Flag!";

	for (int i = 0, length = strlen(word); i < length; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,word[i]);
	}

	glFlush();
}

int main (int argc, char ** argv)
{
	glBegin;
	glEnable(GL_LINE_SMOOTH);
	glutInit(&argc, argv); //leave
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //single buffer, rgb color scheme
	glutInitWindowPosition(0,0); //tells where to create the window
	glutInitWindowSize(800,800); //window size
	glutCreateWindow("Flag"); //title of the window
	init(); //leave for now
	glutDisplayFunc(WavingFlag); //runs function to show inside window that just was created
//	glutReshapeFunc(WavingFlag);
	glutMainLoop(); //
}
