/*
 * Fractal.cpp
 *
 *  Created on: Aug 31, 2017
 *      Author: Jesse
 */

#include <string>
#include <iostream>
#include <GL/glut.h>
#include <windows.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include "Fractal.h"

using namespace std;

void init(void)
{
	glClearColor(1.0,1.0,1.0,0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,1000,0.0,1000.0);
}

void setPixel(float x, float y)
{
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
	if(y==0)
		{
		glFlush();
		}
}

void fractal (void)
{
//  MANDELBROT SET CODE
//	float rmin = -2.5;
//	float rmax = 2;
//	float imin = -2;
//	float N = 64;
//	float width = glutGet(GLUT_WINDOW_WIDTH);
//	float height = glutGet(GLUT_WINDOW_HEIGHT);
//	int i,j,count;
//	ComplexNum z(rmin,imin);
//	float delta = (rmax - rmin)/width;
//
//	for (i=0, z.setReal(rmin); i<width; i++, z.setReal(z.getReal()+delta))
//	{
//		for (j=0, z.setImag(imin); j<height; j++, z.setImag(z.getImag()+delta))
//		{
//			count=0;
//			ComplexNum x;
//			while ((((x.getReal()*x.getReal()) + (x.getImag()*x.getImag())) <= 4.0) && (count < N))
//			{
//				x.squared();
//				x.setNewVal(x.add(z));
//				count++;
//			}
//
//			if ((pow(x.getReal(),2) + pow(x.getImag(),2)) <= 4.0)
//			{
//				glColor3f(0.0,0.0,0.0);
//			}
//
//			else
//			{
//				float newColor = ((1+ (254*(count/N)))/255);
//				glColor3f(newColor,newColor,newColor);
//			}
//
//			setPixel(i,j);
//			;
//		}
//		;
//	}
//
//   JULIA SET CODE (NON-WORKING RIGHT NOW)
	float vals [19] = {0,-0.74543, 0.11301, -0.835, -0.2321, -0.8, 0.156, -0.79, 0.15, -0.162, 1.04, 0.3, -0.01, -1.476, 0, -0.12, -0.77, 0.28, 0.008};
	float rmin = -1.5;
	float rmax = 1.5;
	float imin = -1.5;
	float width = glutGet(GLUT_WINDOW_WIDTH);
	float height = glutGet(GLUT_WINDOW_HEIGHT);
	float N = 128;
	int i,j,count;
	ComplexNum z(rmin,imin);

	int currentSet = 7;
	currentSet *= 2;
	//To change which Julia set displays, set the value of currentSet between 1 and 9
	ComplexNum y(vals[currentSet-1],vals[currentSet]);

	float delta = (rmax - rmin)/width;

	for (i=0, z.setReal(rmin); i<width; i++, z.setReal(z.getReal()+delta))
	{
		for (j=0, z.setImag(imin); j<height; j++, z.setImag(z.getImag()+delta))
		{
			count=0;
			ComplexNum x(z.getReal(),z.getImag());
			while ((((x.getReal()*x.getReal()) + (x.getImag()*x.getImag())) <= 4.0) && (count < N))
			{
				x.squared();
				x.setNewVal(x.add(y));
				count++;
			}

			if ((pow(x.getReal(),2) + pow(x.getImag(),2)) <= 4.0)
			{
				glColor3f(0.0,0.0,0.0);
			}

			else
			{
				float newColor = ((1+ (254*(count/N)))/255);
				glColor3f(newColor,newColor,newColor);
			}

			setPixel(i,j);
			;
		}
		;
	}
}

int main (int argc, char ** argv)
{
	glBegin;
	glutInit(&argc, argv); //leave
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //single buffer, rgb color scheme
	glutInitWindowPosition(0,0); //tells where to create the window
	glutInitWindowSize(1000,1000); //window size
	glutCreateWindow("Fractal"); //title of the window
	init(); //leave for now
	glutDisplayFunc(fractal); //runs function to show inside window that just was created
	glutMainLoop(); //
}


//Original Pseudocode, ignore this
//int i,j,count
//float delta = (Re.max - Re.min)/width
//for i=0, z.real = Re.min; i< width; i++, z.real += delta do
//	for j = 0, z.imag = Im.min; j < height; j++, z.imag += delta do
//		count = 0
//		complex number x = 0
//		while x.real^2 + x.imag^2 <= 4.0 && count < N do
//			compute x = x^2 + z
//			count++
//		end while
//		if x.real^2 + x.imag^2 <= then
//			setColor(0)
//		else
//			setColor(1 + 254 * count/N)
//		end if
//		setPixel(i,j)
//	end for
//end for
