/*
 * ScanFill.cpp
 *
 *  Created on: Oct 23, 2017
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

class polyEdge
{
private:
	float xMin, xMax;
	float yMin, yMax;
	float dx, dy;
	float slope;

public:
	polyEdge()
	{
		xMin = 0;
		xMax = 0;
		yMin = 0;
		yMax = 0;
		dx = 0;
		dy = 0;
		slope = 0;
	}

	polyEdge(float x1, float y1, float x2, float y2)
	{
//		if (x2 > x1)
//		{
//			xMin = x1;
//			xMax = x2;
//		}
//		else
//		{
//			xMin = x2;
//			xMax = x1;
//		}

		if (y2 > y1)
		{
			yMin = y1;
			yMax = y2;
			xMin = x1;
			xMax = x2;
		}
		else
		{
			yMin = y2;
			yMax = y1;
			xMin = x2;
			xMax = x1;
		}

		dx = (xMax-xMin);
		dy = (yMax-yMin);

		if((dx == 0) || (dy == 0))
			slope = 0;
		else
			slope = dy/dx;
	}

	void setXMin(float x)
	{
		xMin = x;
//		refreshVals();
	}

	void setXMax(float x)
	{
		xMax = x;
//		refreshVals();
	}

	void setYMin(float y)
	{
		yMin = y;
//		refreshVals();
	}

	void setYMax(float y)
	{
		yMax = y;
//		refreshVals();
	}

	float getXMin()
	{
		return xMin;
	}

	float getXMax()
	{
		return xMax;
	}

	float getYMin()
	{
		return yMin;
	}

	float getYMax()
	{
		return yMax;
	}

	float getSlope()
	{
		return slope;
	}

	float getDx()
	{
		return dx;
	}

	float getDy()
	{
		return dy;
	}

//	void refreshVals()
//	{
//		dx = (xMax-xMin);
//		dy = (yMax-yMin);
//		slope = dy/dx;
//	}

};

void print(string text)
{
	cout << text;
}

void print(int text)
{
	cout << text;
}

void print(float text)
{
	cout << text;
}

void printl(string text)
{
	cout << text << endl;
}

void printl(int text)
{
	cout << text << endl;
}

void printl(float text)
{
	cout << text << endl;
}

void init(void)
{
	glClearColor(1.0,1.0,1.0,0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,600,0.0,600.0);

}

void setPixel(float x, float y)
{
	glBegin(GL_POINTS);
		glVertex3f(x,y,0);
	glEnd();
//	glFlush();
}

void lineBres (int x0, int y0, int xEnd, int yEnd)
{
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
		float m = float(yEnd-y0)/float(xEnd-x0);
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

void sort (polyEdge edges[], int length)
{
	for (int i = 0; i < length-1; i++)
	{
		for(int j = 0; j < length-i-1; j++)
		{
			polyEdge tempEdge = polyEdge();
			if((edges[j].getYMin()) > (edges[j+1].getYMin()))
			{
				tempEdge = edges[j];
				edges[j] = edges[j+1];
				edges[j+1] = tempEdge;
			}
			else if (((edges[j].getYMin()) == (edges[j+1].getYMin())) && ((edges[j].getXMin()) > (edges[j+1].getXMin())))
			{
				tempEdge = edges[j];
				edges[j] = edges[j+1];
				edges[j+1] = tempEdge;
			}
			else if ((((edges[j].getXMin()) == (edges[j+1].getXMin())) && ((edges[j].getYMin()) == (edges[j+1].getYMin()))) && ((edges[j].getXMax()) > (edges[j+1].getXMax())))
			{
				tempEdge = edges[j];
				edges[j] = edges[j+1];
				edges[j+1] = tempEdge;
			}
		}
	}
}

void drawLineBresenham ()
{
	glClear(GL_COLOR_BUFFER_BIT);
	//house 1
	glColor3f(0,0,0);
	lineBres(50,50,300,50);
	lineBres(50,50,55,200);
	lineBres(55,200,70,180);
	lineBres(70,180,80,250);
	lineBres(80,250,98,150);
	lineBres(98,150,200,120);
	lineBres(200,120, 205,210);
	lineBres(205,210,220,112);
	lineBres(220,112,250,160);
	lineBres(250,160,300,50);
	glFlush();
}

void lineFill()
{
	polyEdge edges[10];							//Instantiate the array of edges
//	polyEdge activeEdges[10];
	edges[0] = polyEdge(50,50,300,50);
	edges[1] = polyEdge(50,50,55,200);
	edges[2] = polyEdge(55,200,70,180);
	edges[3] = polyEdge(70,180,80,250);
	edges[4] = polyEdge(80,250,98,150);
	edges[5] = polyEdge(98,150,200,120);
	edges[6] = polyEdge(200,120, 205,210);
	edges[7] = polyEdge(205,210,220,112);
	edges[8] = polyEdge(220,112,250,160);
	edges[9] = polyEdge(250,160,300,50);
	int length = *(&edges + 1) - edges;

	float polyMaxY = 0;
	float polyMinY = 10000000;

	//Sort the edges in ascending order of y0, x0, x1
	for (int i = 0; i < length-1; i++)
	{
		for(int j = 0; j < length-i-1; j++)
		{
			polyEdge tempEdge = polyEdge();
			if((edges[j].getYMin()) > (edges[j+1].getYMin()))
			{
				tempEdge = edges[j];
				edges[j] = edges[j+1];
				edges[j+1] = tempEdge;
			}
			else if (((edges[j].getYMin()) == (edges[j+1].getYMin())) && ((edges[j].getXMin()) > (edges[j+1].getXMin())))
			{
				tempEdge = edges[j];
				edges[j] = edges[j+1];
				edges[j+1] = tempEdge;
			}
			else if ((((edges[j].getXMin()) == (edges[j+1].getXMin())) && ((edges[j].getYMin()) == (edges[j+1].getYMin()))) && ((edges[j].getXMax()) > (edges[j+1].getXMax())))
			{
				tempEdge = edges[j];
				edges[j] = edges[j+1];
				edges[j+1] = tempEdge;
			}
		}
	}

	//Draw the outline of the shape*
	drawLineBresenham();

	//Remove any horizontal edges
	int count = 0;
	length = *(&edges + 1) - edges;

	//Finds the number of horizontal edges, and also finds the min/max Y values
	for(int i = 0; i < length; i++)
	{
		if (edges[i].getYMin() < polyMinY)
		{
			polyMinY = edges[i].getYMin();
		}

		if (edges[i].getYMax() > polyMaxY)
		{
			polyMaxY = edges[i].getYMax();
		}

		if (edges[i].getDy() == 0)
		{
			count++;
		}
	}

	polyEdge edges2[length-count];
	count = 0;
	for(int i = 0; i < length; i++)
	{
		if (edges[i].getDy() != 0)
		{
			edges2[count] = edges[i];
			count++;
		}
	}
	length = *(&edges2 + 1) - edges2;

//	printl("After removal of horizontal edges");
//	for(int i = 0; i < length; i++)
//	{
//		print(i+1);
//		print(":");
//		print(edges2[i].getXMin());
//		print(",");
//		print(edges2[i].getYMin());
//		print(",");
//		print(edges2[i].getXMax());
//		print(",");
//		print(edges2[i].getYMax());
//		print(",");
//		print(edges2[i].getDy());
//		print(",");
//		print(edges2[i].getDx());
//		print(",");
//		printl(edges2[i].getSlope());
//	}

	float scanLineY = polyMinY;
	while (scanLineY < polyMaxY)
	{
		//Gets the number of active edges, creates an array with that specific length, and then puts the active edges into it
		int count = 0;
		int numActive = 0;
		for(int i = 0; i < length; i++)
		{
			if ((scanLineY < edges2[i].getYMax()) && (scanLineY >= edges2[i].getYMin()))
				{
					numActive++;
				}
		}

		polyEdge activeEdges[numActive];
		for(int i = 0; i < length; i++)
		{
			if ((scanLineY < edges2[i].getYMax()) && (scanLineY >= edges2[i].getYMin()))
			{
				activeEdges[count] = edges2[i];
				edges2[i].setXMin((float)((edges2[i].getXMin()) + (1/(edges2[i].getSlope()))));
				count++;
			}
		}

		for (int i = 0; i < numActive-1; i++)
		{
			for(int j = 0; j < numActive-i-1; j++)
			{
				polyEdge tempEdge = polyEdge();
				if((activeEdges[j].getXMin()) > (activeEdges[j+1].getXMin()))
				{
					tempEdge = activeEdges[j];
					activeEdges[j] = activeEdges[j+1];
					activeEdges[j+1] = tempEdge;
				}
			}
		}

//		for (int i = 0; i < numActive; i++)
//		{
//			print(i+1);
//			print(":");
//			print(activeEdges[i].getXMin());
//			print(",");
//			print(activeEdges[i].getYMin());
//			print(",");
//			print(activeEdges[i].getXMax());
//			print(",");
//			printl(activeEdges[i].getYMax());
//		}

		for(int i = 0; i < numActive; i+=2)
		{
			float x0 = activeEdges[i].getXMin();
			float x1 = activeEdges[i+1].getXMin();
				print((float)x0);
				print(",");
				print(scanLineY);
				print("---");
				print(x1);
				print(",");
				printl(scanLineY);
				lineBres(x0,scanLineY,x1,scanLineY);
		}
		scanLineY++;
		glFlush();
	}
}

int main (int argc, char ** argv)
{
	glEnable(GL_LINE_SMOOTH);
	glutInit(&argc, argv); //leave
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //single buffer, rgb color scheme
	glutInitWindowPosition(0,0); //tells where to create the window
	glutInitWindowSize(600,600); //window size
	//glutCreateWindow("BuildingDDA"); //title of the window
	glutCreateWindow("FilledPolygon"); //title of the window
	init(); //leave for now
	//glutDisplayFunc(drawLineDDA);
	glutDisplayFunc(lineFill); //runs function to show inside window that just was created
//	glutReshapeFunc(WavingFlag);
	glutMainLoop(); //
}

