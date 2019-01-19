///*
// * PixelArt.cpp
// *
// *  Created on: Sep 12, 2017
// *      Author: Jesse
// */
//
#include <string>
#include <iostream>
#include <fstream>
#include <GL/glut.h>
#include <windows.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <math.h>
#include <array>
using namespace std;


class Vector{
private:
	int x,y,z;

public:
	Vector()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	Vector(int a, int b, int c)
	{
		x = a;
		y = b;
		z = c;
	}

	Vector(int a, int b)
	{
		x = a;
		y = b;
		z = 0;
	}

	int getX()
	{
		return x;
	}

	int getY()
	{
		return y;
	}

	int getZ()
	{
		return z;
	}

	void setX(int newVal)
	{
		x = newVal;
	}

	void setY(int newVal)
	{
		y = newVal;
	}

	void setZ(int newVal)
		{
			z = newVal;
		}

	Vector subtract (Vector a)
	{
		Vector temp;

		temp.setX(x-a.getX());
		temp.setY(y-a.getY());
		temp.setZ(z-a.getZ());

		return temp;
	}

	Vector cross (Vector a)
	{
		Vector temp;

		temp.setX((y*a.getZ())-(a.getY()*z));
		temp.setY(-((x*a.getZ())-(a.getZ()*y)));
		temp.setZ((x*a.getY())-(a.getX()*y));
		//cout << x << "*" << a.getY() << "-" << a.getX() << "*" << y << "=" << temp.getZ() << endl;

		return temp;
	}
};


void init(void)
{
	glClearColor(1.0,1.0,1.0,0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,200,0.0,200.0);

}

void drawShape (Vector coords[], int length)
{
	int i;
	glBegin(GL_LINE_LOOP);
	for (i=0;i<length;i++)
	{
		glVertex2i(coords[i].getX(),coords[i].getY());
	}
	glEnd();
	glFlush();
}

void ShapeFromFile()
{
	glClear(GL_COLOR_BUFFER_BIT);

	ifstream file;
	string line;
	bool concave;
	int i,commaIndex, newLineIndex, length, xPos, yPos;
	int loopCount = 1;

	file.open("hw3.txt");
	while (getline(file,line))
		{
			//cout << "Loop " << loopCount << endl;
			concave = false;
			newLineIndex = line.find('\n');
			line = line.substr(0,newLineIndex);
			length = stoi(line);
			Vector vectors [length];
			Vector edgeVectors [length];
			Vector crossedVectors [length];

			//Puts vectors into a new array
			for (i=0;i<length;i++)
			{
				getline(file,line);
				commaIndex = line.find(",");
				newLineIndex = line.find('\n');
				line = line.substr(0,newLineIndex);
				xPos = stoi(line.substr(0,commaIndex));
				yPos = stoi(line.substr(commaIndex+1,newLineIndex));
				vectors[i] = Vector(xPos,yPos);
				//cout << "Vector " << i+1 << ": " << vectors[i].getX() << "," << vectors[i].getY() << endl;
			}

			//Creates edge array
			for (i=0;i<length;i++)
			{
				//For all the normal edges, just subtract and go
				if (i != length-1)
				{
					edgeVectors[i] = vectors[i+1].subtract(vectors[i]);

				}

				//Run if we're making the edge from the last vertex to the origin
				else
				{
					edgeVectors[i] = vectors[0].subtract(vectors[i]);
				}
				//cout << "Edge " << i+1 << ": " << edgeVectors[i].getX() << "," << edgeVectors[i].getY() << endl;

			}

			//Gets the cross product of the edge vectors and puts that into one final array
			for (i=0;i<length;i++)
			{
				//For all the normal edges, just cross and go
				if (i < length-1)
				{
					crossedVectors[i] = edgeVectors[i].cross(edgeVectors[i+1]);
				}

				//Run if we're crossing the edge from the last two vertices to the edge from the last vertex to origin
				else
				{
					crossedVectors[i] = edgeVectors[i].cross(edgeVectors[0]);
				}
				//cout << "Z of CP " << i+1 << ": " << crossedVectors[i].getZ() << endl;

			}

			//Finally, check the z coordinates of the cross product results and set the color based on whether it's concave or convex
			for (i=0;i<length;i++)
			{
				if ((crossedVectors[i].getZ()) < 0)
				{
					concave = true;
					break;
				}
			}

			if(concave)
			{
				glColor3f(1.0,0.0,0.0);
				if (loopCount > 1)
				{
					cout << "*************" << endl;
				}
				cout << "Polygon " << loopCount << " is concave " << endl;
			}
			else
			{
				glColor3f(0.0,0.0,1.0);
				if (loopCount > 1)
				{
					cout << "*************" << endl;
				}
				cout << "Polygon " << loopCount << " is convex " << endl;
			}

			drawShape(vectors,length);
			loopCount += 1;
		}

	file.close();
}

int main (int argc, char ** argv)
{
	glBegin;
	glutInit(&argc, argv); //leave
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //single buffer, rgb color scheme
	glutInitWindowPosition(0,0); //tells where to create the window
	glutInitWindowSize(800,800); //window size
	glutCreateWindow("Shapes"); //title of the window
	init(); //leave for now
	glutDisplayFunc(ShapeFromFile); //runs function to show inside window that just was created
	glutMainLoop(); //
}
