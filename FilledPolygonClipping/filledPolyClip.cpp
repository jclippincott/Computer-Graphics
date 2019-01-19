/*
 * filledPolyClip.cpp
 *
 *  Created on: Nov 16, 2017
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

void init(void)
{
	glClearColor(1.0,1.0,1.0,0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,200,0,200);
}

class wcPt2D
{
	private:
	GLfloat x, y;
	public:
	/* Default Constructor: initialize position as (0.0, 0.0). */
	wcPt2D()
	{
	x = y = 0.0;
	}

	wcPt2D(GLfloat newX, GLfloat newY)
	{
		x = newX;
		y = newY;
	}

	void setCoords (GLfloat xCoord, GLfloat yCoord) {
	x = xCoord;
	y = yCoord;
	}
	GLfloat getx ( ) const {
	return x;
	}
	GLfloat gety ( ) const {
	return y;
	}
	void setY(GLfloat newY)
	{
		y = newY;
	}
	void setX(GLfloat newX)
	{
		x = newX;
	}

};

typedef enum { Left, Right, Bottom, Top } Boundary;
const GLint nClip = 4;

GLint inside (wcPt2D p, Boundary b, wcPt2D wMin, wcPt2D wMax)
{
	switch (b) {
	case Left: if (p.getx() < wMin.getx()) return (false); break;
	case Right: if (p.getx() > wMax.getx()) return (false); break;
	case Bottom: if (p.gety() < wMin.gety()) return (false); break;
	case Top: if (p.gety() > wMax.gety()) return (false); break;
	}
	return (true);
}
GLint cross (wcPt2D p1, wcPt2D p2, Boundary winEdge, wcPt2D wMin, wcPt2D wMax)
{
	if (inside (p1, winEdge, wMin, wMax) == inside (p2, winEdge, wMin, wMax))
		return (false);
	else return (true);
}

wcPt2D intersect (wcPt2D p1, wcPt2D p2, Boundary winEdge, wcPt2D wMin, wcPt2D wMax)
{
	wcPt2D iPt;
	GLfloat m;

	if (p1.getx() != p2.getx()) m = (p1.gety() - p2.gety()) / (p1.getx() - p2.getx());
	switch (winEdge) {

	case Left:
		iPt.setX(wMin.getx());
		iPt.setY(p2.gety() + (wMin.getx() - p2.getx()) * m);
		break;
	case Right:
		iPt.setX(wMax.getx());
		iPt.setY(p2.gety() + (wMax.getx() - p2.getx()) * m);
		break;
	case Bottom:
		iPt.setY(wMin.gety());
		if (p1.getx() != p2.getx()) iPt.setX(p2.getx() + (wMin.gety() - p2.gety()) / m);
		else iPt.setX(p2.getx());
		break;
	case Top:
		iPt.setY(wMax.gety());
		if (p1.getx() != p2.getx()) iPt.setX(p2.getx() + (wMax.gety() - p2.gety()) / m);
		else iPt.setX(p2.getx());
		break;
	}
	return (iPt);
}

void clipPoint (wcPt2D p, Boundary winEdge, wcPt2D wMin, wcPt2D wMax,
							wcPt2D * pOut, int * cnt, wcPt2D * first[], wcPt2D * s)
{
	wcPt2D iPt;
	/* If no previous point exists for this clipping boundary,
	* save this point.
	*/
	if (!first[winEdge])
		first[winEdge] = &p;
	else
		/* Previous point exists. If p and previous point cross
		* this clipping boundary, find intersection. Clip against
		* next boundary, if any. If no more clip boundaries, add
		* intersection to output list.
		*/
		if (cross (p, s[winEdge], winEdge, wMin, wMax)) {
			iPt = intersect (p, s[winEdge], winEdge, wMin, wMax);
			if (winEdge < Top)
				clipPoint (iPt, (Boundary)(winEdge + 1), wMin, wMax, pOut, cnt, first, s);
			else {
				pOut[*cnt] = iPt; (*cnt)++;
			}
		}

	/* Save p as most recent point for this clip boundary. */
	s[winEdge] = p;

	/* For all, if point inside, proceed to next boundary, if any. */
	if (inside (p, winEdge, wMin, wMax))
		if (winEdge < Top)
			clipPoint (p, (Boundary)(winEdge + 1), wMin, wMax, pOut, cnt, first, s);
		else {
			pOut[*cnt] = p; (*cnt)++;
		}
}
void closeClip (wcPt2D wMin, wcPt2D wMax, wcPt2D * pOut,
				GLint * cnt, wcPt2D * first [ ], wcPt2D * s)
{
	wcPt2D pt;
	Boundary winEdge;

	for (winEdge = Left; winEdge <= Top; winEdge = (Boundary)((int)winEdge+1)) {
		if (cross (s[winEdge], *first[winEdge], winEdge, wMin, wMax)) {
			pt = intersect (s[winEdge], *first[winEdge], winEdge, wMin, wMax);
			if (winEdge < Top)
				clipPoint (pt, (Boundary)(winEdge + 1), wMin, wMax, pOut, cnt, first, s);
			else {
				pOut[*cnt] = pt; (*cnt)++;
			}
		}
	}
}


GLint polygonClipSuthHodg (wcPt2D wMin, wcPt2D wMax, GLint n, wcPt2D * pIn, wcPt2D * pOut)
{
	/* Parameter "first" holds pointer to first point processed for
	* a boundary; "s" holds most recent point processed for boundary.
	*/
	wcPt2D * first[nClip] = { 0, 0, 0, 0 }, s[nClip];
	GLint k, cnt = 0;

	for (k = 0; k < n; k++)
		clipPoint (pIn[k], Left, wMin, wMax, pOut, &cnt, first, s);

	closeClip (wMin, wMax, pOut, &cnt, first, s);
	return (cnt);
}

void drawClippedStar()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,0,0);

	wcPt2D min {35,10};
	wcPt2D max {75,110};
	wcPt2D inArray[10] {{35,55},{0,10},{55,35},{110,10},{75,55},{110,75},{75,75},{55,110},{35,75},{0,75}};
	wcPt2D outArray[20];

	int numClippedPoints = polygonClipSuthHodg(min,max,10,inArray,outArray);

	glBegin(GL_POLYGON);

	for (int i = 0; i < numClippedPoints; i++)
	{
		glVertex2i(outArray[i].getx(),outArray[i].gety());
	}

	glEnd();
	glFlush();
}

int main (int argc, char ** argv)
{
	glEnable(GL_LINE_SMOOTH);
	glutInit(&argc, argv); //leave
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //single buffer, rgb color scheme
	glutInitWindowPosition(200,200); //tells where to create the window
	glViewport(0,0,200,200);
	glutInitWindowSize(300,300); //window size
	glutCreateWindow("Clipped Star"); //title of the window
	init(); //leave for now
	glutDisplayFunc(drawClippedStar);
	glutMainLoop(); //
}
