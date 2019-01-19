/*
 * ComplexNum.cpp
 *
 *  Created on: Sep 1, 2017
 *      Author: Jesse
 */

#include "ComplexNum.h"
#include <string>
#include <iostream>
#include <GL/glut.h>
#include <windows.h>
#include <GL/glu.h>
#include <GL/gl.h>

using namespace std;

int main (int argc, char ** argv)
{
	ComplexNum x(2,1);
	cout << "" << x.getReal() << "," << x.getImag() << endl;
	ComplexNum y(1,2);
	x.setNewVal(y);
	cout << "" << x.getReal() << "," << x.getImag() << endl;
	x.squared();
	cout << "" << x.getReal() << "," << x.getImag() << endl;
}

