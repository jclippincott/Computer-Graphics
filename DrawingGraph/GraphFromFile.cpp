/*
 * GraphFromFile.cpp
 *
 *  Created on: Oct 9, 2017
 *      Author: Jesse
 */

#include <string>
#include <iostream>
#include <fstream>
#include <GL/glut.h>
#include <windows.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <math.h>
#include <array>
#include <cmath>
using namespace std;

void init(void)
{
	glClearColor(1.0,1.0,1.0,0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,800,0.0,800.0);

}

class GraphPiece
{
private:
	float num;
	string label;

public:
	GraphPiece()
	{
		num = 0;
		label = "";
	}

	GraphPiece(int newNum, string newLabel)
	{
		num = newNum;
		label = newLabel;
	}

	string getLabel()
	{
		return label;
	}

	float getNum()
	{
		return num;
	}

	void setLabel(string newLabel)
	{
		label = newLabel;
	}

	void setNum(int newNum)
	{
		num = newNum;
	}
};

void drawBarGraph()
{
	glClear(GL_COLOR_BUFFER_BIT);
	ifstream file;
	string line;
	int spaceIndex, newLineIndex, value, numSections, numTotal, currentIndex;
	float yRatio, fullCycle, currentSectionEnd, sectionTotal;
	string label;


	file.open("hw5.txt");
	getline(file,line);
	numSections = stoi(line);
	//cout << "Loop " << loopCount << endl;
	numTotal = 0;
	newLineIndex = line.find('\n');
	line = line.substr(0,newLineIndex);
	numSections = stoi(line);
	GraphPiece sections [numSections];

	//Puts graph sections into a new array
	for (int i=0;i<numSections;i++)
	{
		getline(file,line);
		spaceIndex = line.find(' ');
		newLineIndex = line.find('\n');
		line = line.substr(0,newLineIndex);
		value = stoi(line.substr(0,spaceIndex));
		label = line.substr(spaceIndex+1,newLineIndex);
		sections[i] = GraphPiece(value,label);
		numTotal += value;
	}

	float width = glutGet(GLUT_WINDOW_WIDTH);
	float height = glutGet(GLUT_WINDOW_HEIGHT);

	float offsetX = width/(numSections);
	yRatio = height*0.8;

	float colorNums[numSections*3];
	sectionTotal = 0;
	currentIndex = 0;
	float textIndices [numSections*2];
	float colorNum1 = rand()/((float)RAND_MAX+1);
	float colorNum2 = rand()/((float)RAND_MAX+1);
	float colorNum3 = rand()/((float)RAND_MAX+1);
	glColor3f(colorNum1, colorNum2, colorNum3);

	for (int i = 0; i < numSections; i++)
	{
		float currentHeight = (sections[i].getNum())*10;
		cout << currentHeight << endl;
		glRectf(20 + (offsetX*i), height * 0.05, 55 + (offsetX*i), currentHeight);
		glRasterPos2i (20 + (offsetX*i),height * 0.025);
		string text = sections[i].getLabel();
		for (int j=0; j<text.size(); j++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,text[j]);
		}
	}
	glFlush();

//	void barChart (void)
//	{
//	GLint month, k;
//	glClear (GL_COLOR_BUFFER_BIT); // Clear display window.
//	glColor3f (1.0, 0.0, 0.0); // Set bar color to red.
//	for (k = 0; k < 12; k++)
//	glRecti (20 + k*50, 165, 40 + k*50, dataValue [k]);
//	glColor3f (0.0, 0.0, 0.0); // Set text color to black.
//	xRaster = 20; // Display chart labels.
//	for (month = 0; month < 12; month++) {
//	glRasterPos2i (xRaster, yRaster);
//	for (k = 3*month; k < 3*month + 3; k++)
//	glutBitmapCharacter (GLUT_BITMAP_HELVETICA_12,
//	label [h]);
//	xRaster += 50;
//	}
	glFlush();
}


void drawPieGraph ()
{
	glClear(GL_COLOR_BUFFER_BIT);
	ifstream file;
	string line;
	int spaceIndex, newLineIndex, value, rad, numSections, numTotal, currentIndex;
	float centerX, centerY, fullCycle, currentSectionEnd, sectionTotal;
	string label;

	file.open("hw5.txt");
	getline(file,line);
	numSections = stoi(line);
	//cout << "Loop " << loopCount << endl;
	numTotal = 0;
	newLineIndex = line.find('\n');
	line = line.substr(0,newLineIndex);
	numSections = stoi(line);
	GraphPiece sections [numSections];

	//Puts graph sections into a new array
	for (int i=0;i<numSections;i++)
	{
		getline(file,line);
		spaceIndex = line.find(' ');
		newLineIndex = line.find('\n');
		line = line.substr(0,newLineIndex);
		value = stoi(line.substr(0,spaceIndex));
		label = line.substr(spaceIndex+1,newLineIndex);
		sections[i] = GraphPiece(value,label);
		numTotal += value;
	}


	glBegin(GL_TRIANGLES);
	//Instantiating all of the variable values needed for the triangle drawing
	float colorNums[numSections*3];
	fullCycle = M_PI*2;
	rad = 200;
	sectionTotal = 0;
	currentIndex = 0;
	float textIndices [numSections*2];
	centerX = (glutGet(GLUT_WINDOW_WIDTH)/2);
	centerY = (glutGet(GLUT_WINDOW_HEIGHT)/2);
	float colorNum1 = rand()/((float)RAND_MAX+1);
	float colorNum2 = rand()/((float)RAND_MAX+1);
	float colorNum3 = rand()/((float)RAND_MAX+1);
	glColor3f(colorNum1, colorNum2, colorNum3);

	currentSectionEnd = (((sections[0].getNum())/numTotal)*fullCycle);


	for (float i = 0; i < fullCycle; i += 0.001)
	{
//		cout << i << "," << currentSectionEnd << endl;
		if (i <= currentSectionEnd)
		{
			glVertex2f(centerX,centerY);
			glVertex2f(centerX+(rad*cos(i)),centerY+(rad*sin(i)));
			glVertex2f(centerX+(rad*cos(i+0.001)),centerY+(rad*sin(i+0.001)));
		}
		else
		{
			if (i < numTotal)
			{
				++currentIndex;
//				cout << sectionTotal << " , ";
//				cout << sections[currentIndex].getNum() << " , ";
//				cout << sections[currentIndex].getNum()/numTotal << " , ";
//				cout << (((sections[currentIndex].getNum())/numTotal)*fullCycle) << " , ";
//				cout << sectionTotal + (((sections[currentIndex].getNum())/numTotal)*fullCycle) << endl;
//				cout << currentSectionEnd << ",";
				currentSectionEnd += (((sections[currentIndex].getNum())/numTotal)*fullCycle);
//				cout << currentSectionEnd << endl;

				colorNum1 = rand()/((float)RAND_MAX+1);
				colorNum2 = rand()/((float)RAND_MAX+1);
				colorNum3 = rand()/((float)RAND_MAX+1);
				colorNums[currentIndex*3] = colorNum1;
				colorNums[(currentIndex*3)+1] = colorNum2;
				colorNums[(currentIndex*3)+2] = colorNum3;

				glColor3f(colorNum1, colorNum2, colorNum3);
				glVertex2f(centerX,centerY);
				glVertex2f(centerX+(rad*cos(i)),centerY+(rad*sin(i)));
				glVertex2f(centerX+(rad*cos(i+0.001)),centerY+(rad*sin(i+0.001)));
				textIndices[currentIndex*2] = centerX+((rad+50)*cos(i));
				textIndices[(currentIndex*2)+1] = centerY+((rad+50)*sin(i));


//				string text = "a";
				string text = sections[currentIndex].getLabel();
//				string textArray[sizeof(text)];

			}
			else
			{
				break;
			}
		}

	}
	glEnd();
	glFlush();

	currentIndex = 0;
	currentSectionEnd = (((sections[0].getNum())/numTotal)*fullCycle);


	for (int i = 0; i < numSections; i++)
	{
		string text = sections[currentIndex].getLabel();

		glRasterPos2i (textIndices[currentIndex*2],textIndices[(currentIndex*2)+1]);
		glColor3f(colorNums[currentIndex*3],colorNums[(currentIndex*3)+1],colorNums[(currentIndex*3)+2]);

		for (int j = 0; j<text.size(); j++)
		{
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15,text[j]);
		}
		currentIndex++;
		currentSectionEnd += (((sections[currentIndex].getNum())/numTotal)*fullCycle);

	}
	glFlush();

	file.close();
}

int main (int argc, char ** argv)
{
	glEnable(GL_LINE_SMOOTH);
	glutInit(&argc, argv); //leave
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //single buffer, rgb color scheme
	glutInitWindowPosition(0,0); //tells where to create the window
	glutInitWindowSize(800,800); //window size
	glutCreateWindow("Graph"); //title of the window
	init(); //leave for now
	glutDisplayFunc(drawBarGraph); //runs function to show inside window that just was created
//	glutReshapeFunc(WavingFlag);
	glutMainLoop(); //
}
