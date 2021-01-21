#include <GL/glut.h>
#include <GL/gl.h>
#include <iostream>

using namespace std;

void drawTriangle(GLint x0, GLint y0, GLint x1, GLint y1, GLint x2, GLint y2)
{

    int dx0 = x1 - x0;
    int dx1 = x2 - x1;
    int dx2 = x0 - x2;
    int dy0 = y1 - y0;
    int dy1 = y2 - y1;
    int dy2 = y0 - y2;

    int xmin = min(x0, min(x1, x2));
    int xmax = max(x0, max(x1, x2));
    int ymin = min(y0, min(y1, y2));
    int ymax = max(y0, max(y1, y2));
    int q = xmax - xmin;
    int f0 = ((xmin - x0) * dy0) - ((ymax - y0) * dx0);
    int f1 = ((xmin - x1) * dy1) - ((ymax - y1) * dx1);
    int f2 = ((xmin - x2) * dy2) - ((ymax - y2) * dx2);

    int g0 = ((x0 - x1) * dy1) - ((y0 - y1) * dx1);
    int g1 = ((x1 - x2) * dy2) - ((y1 - y2) * dx2);
    int g2 = ((x2 - x0) * dy0) - ((y2 - y0) * dx0);

    glBegin(GL_POINTS);
    for (int y = ymax; y >= ymin; y--)
    {
        for (int x = xmin; x < xmax; x++)
        {
            float alpha = (float)f1 / g1;
            float beta = (float)f2 / g2;
            float gamma = (float)f0 / g0;
            float diff = 1.0 - (alpha + beta + gamma);
            if ((diff <= 0.00001 && diff >= -0.00001) && 0 <= alpha && alpha <= 1 && 0 <= beta && beta <= 1 && 0 <= gamma && gamma <= 1)
                glVertex2i(x, y);
            f0 += dy0;
            f1 += dy1;
            f2 += dy2;
        }
        f0 -= q * dy0;
        f1 -= q * dy1;
        f2 -= q * dy2;
        f0 += dx0;
        f1 += dx1;
        f2 += dx2;
    }

    glEnd();
}

void renderTriangle(void)
{
    glClear(GL_COLOR_BUFFER_BIT); // Clear display window.
    glColor3f(1.0, 0.0, 0.0);
    drawTriangle(30, 40, 200, 350, 350, 100);
    glFlush();
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0); // set display-window color to black
    glMatrixMode(GL_PROJECTION);      // set projection parameters
    glViewport(10, 30, 500, 500);
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);                                           // initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);                     // set display mode
    glutInitWindowPosition(10, 30);                                  // set top-left display-window position
    glutInitWindowSize(500, 500);                                    // set display-window sidth and height
    glutCreateWindow("Triangle using Barycentric Corrdinates Form"); // create display window
    init();                                                          // execute initialization procedure
    glutDisplayFunc(renderTriangle);                                 // send graphics to display window
    glutMainLoop();                                                  // display everything and wait
    return 0;
}

