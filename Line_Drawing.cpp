/*
Implemented by Itisha Patidar(B17CS026).
Midpoint line drawing algorithm is implemented
in this file.
*/

#include <GL/glut.h>
#include <GL/gl.h>
#include <iostream>

using namespace std;

int pntX0 = rand() % 400 + 10;
int pntX1 = rand() % 400 + 10;
int pntY0 = rand() % 400 + 10;
int pntY1 = rand() % 400 + 10;

void init (void){

  glClearColor (0.0, 0.0, 0.0, 0.0); // set display-window color to black
  glMatrixMode (GL_PROJECTION); // set projection parameters
  glViewport(10,30,500,500);
  gluOrtho2D (0.0, 500.0, 0.0, 500.0);
}


void draw(GLint x, GLint y){

	glColor3f (1.0, 1.0, 1.0);
	glBegin (GL_POINTS);
        glVertex2i (x, y);
	glEnd ();
	glFlush();
}



void midpoint_line(){
	int dx = abs(pntX1 - pntX0);
	int dy = abs(pntY1 - pntY0);

	int x, y;
    int temp1 = pntX1;
    int temp2 = pntY1;

	if (dx >= dy){              // slope |m| <= 1.0;
	    int d = abs((2*dy)-dx);
        int e = 2*dy;
        int ne = 2*(dy-dx);

        if (pntX0 < pntX1){     // x,y takes the value of point appearing on the left.
            x = pntX0;
            y = pntY0;
        }
        else {
            x = pntX1;
            y = pntY1;
            pntX1 = pntX0;
            pntY1 = pntY0;
        }
        draw(x, y);

        while (x < pntX1) {
            if (d < 0)
                d += e;
            else {
                d += ne;
                if (y < pntY1)
                    y++;
                else
                    y--;
            }
            x++;
            draw (x, y);
        }
    }
    else {                          // slope |m| > 1.0;
        int d = (2*dx) - dy;
        int s = 2*dx;
        int es = (dx - dy)*2;

        if (pntY0 < pntY1){
            x = pntX0;
            y = pntY0;
        }
        else {
            x = pntX1;
            y = pntY1;
            pntX1 = pntX0;
            pntY1 = pntY0;
        }
        draw (x, y);

        while (y < pntY1) {
            if (d <= 0)
                d += s;
            else {
                d += es;
                if(x>pntX1)
                    x--;
                else
                    x++;
            }
            y++;
            draw (x, y);
        }
    }
    pntX1 = temp1;
    pntY1 = temp2;
}

void renderLine(void){
    glClear (GL_COLOR_BUFFER_BIT); // Clear display window.
    cout<<"The randomly generated values of points \n"<<"(pntX0,pntY0) is ("<<pntX0<<","<<pntY0<<") \n"<<"(pntX1,pntY1) is ("<<pntX1<<","<<pntY1<<")"<<endl;
    midpoint_line();
    glFlush();
}


int main (int argc, char** argv)
{
	glutInit (&argc, argv); // initialize GLUT
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); // set display mode

	glutInitWindowPosition (10, 30); // set top-left display-window position
	glutInitWindowSize (500, 500); // set display-window sidth and height
	glutCreateWindow ("Solution for Question 1"); // create display window

	init (); // execute initialization procedure
	glutDisplayFunc (renderLine); // send graphics to display window

	glutMainLoop (); // display everything and wait
    return 0;
}

