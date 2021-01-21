/*
Implemented by Itisha Patidar(B17CS026)
MidPoint Circle Drawing Algorithm is implemented
in this file. 
*/

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <GL/glut.h>
using namespace std;

int center_x = 0, center_y = 0, r = 100, r_sqrt;

void init (void){

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-500, 500, -500, 500);
}

void draw_pixel (GLint x, GLint y){

	glBegin (GL_POINTS);
    glVertex2i (x, y);
	glEnd ();
	glFlush ();
}

void midpoint_line (int x0, int y0, int x1, int y1){
	int dx = abs (x1 - x0);
	int dy = abs (y1 - y0);
	int x, y;

	if (dx >= dy){              //slope |m| <= 1.0;
        if (x0 < x1) {
            x = x0;
            y = y0;
        }
        else {
            x = x1;
            y = y1;
            x1 = x0;
            y1 = y0;
        }
        int d = abs((2*dy)-dx);
        int e = 2*dy;
        int ne = 2*(dy-dx);
        draw_pixel (x, y);
        while (x < x1) {
            if (d < 0)
                d += e;
            else {
                d += ne;
                if (y < y1)
                    y++;
                else
                    y--;
            }
            x++;
            draw_pixel (x, y);
        }
    }
    else {                          //  slope |m| > 1.0;
         if (y0 < y1) {
            x = x0;
            y = y0;
        }
        else {
            x = x1;
            y = y1;
            x1 = x0;
            y1 = y0;
        }
        int d = (2*dx) - dy;
        int s = 2*dx;
        int es = (dx - dy)*2;
        draw_pixel (x, y);
        while (y < y1) {
            if (d <= 0)
                d += s;
            else {
                d += es;
                if(x>x1)
                    x--;
                else
                    x++;
            }
            y++;
            draw_pixel (x, y);
        }
    }
}

void circle_quad7(int x, int y){
	float d = 1 - r_sqrt;
	float w = 2*r_sqrt + 3;
	float sw = 5;
	draw_pixel(center_x+x,center_y+y);

	while (y >= 0){
		if (d < 0)
		{
			y--;
			d += w;
			w -= 2;
			sw -= 2;
		}
		else
		{
			x--;
			y--;
			d += sw;
			w -= 2;
			sw -= 4;
		}
		draw_pixel(center_x+x,center_y+y);
	}
}

void circle_quad6(int x, int y){

	float d = 1 - r;
	int s = 3;
	int es = 5 - (2*r);
	draw_pixel(center_x+x, center_y+y);

	while (y >= -r*sin(0.610865)){
		if (d <= 0)
		{
			y--;
			d += s;
			s += 2;
			es += 2;
		}
		else
		{
			x++;
			y--;
			d += es;
			s += 2;
			es += 4;
		}
		draw_pixel(center_x+x,center_y+y);
	}
}

void render_arc(void){
	glClear (GL_COLOR_BUFFER_BIT);

    r_sqrt = r/sqrt(2);

	circle_quad7(-r_sqrt,r_sqrt);
    circle_quad6(-r,0);

    midpoint_line(center_x,center_y,center_x-r,center_y+0);
    midpoint_line(center_x,center_y,center_x-r_sqrt,center_y+r_sqrt);
    midpoint_line(center_x,center_y,center_x-r*cos(0.610865),center_y-r*sin(0.610865));

	glFlush ();
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);

	glutInitWindowPosition (100, 100); // set top-left display-window position
	glutInitWindowSize (800, 500);
	glutCreateWindow ("Solution for question 3");

	init ();
	glutDisplayFunc(render_arc);

	glutMainLoop();
	return 0;
}
