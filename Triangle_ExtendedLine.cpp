#include <GL/glut.h>
#include <GL/gl.h>
#include <iostream>
#include <vector>

using namespace std;

void getBoudaryPixels(int x0, int y0, int x1, int y1, vector<vector<int>> &boundaryPixels)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    int x, y;
    int temp1 = x1;
    int temp2 = y1;

    if (dx >= dy)
    { // slope |m| <= 1.0;
        int d = abs((2 * dy) - dx);
        int e = 2 * dy;
        int ne = 2 * (dy - dx);

        if (x0 < x1)
        { // x,y takes the value of point appearing on the left.
            x = x0;
            y = y0;
        }
        else
        {
            x = x1;
            y = y1;
            x1 = x0;
            y1 = y0;
        }
        boundaryPixels.push_back({x, y});

        while (x < x1)
        {
            if (d < 0)
                d += e;
            else
            {
                d += ne;
                if (y < y1)
                    y++;
                else
                    y--;
            }
            x++;
            boundaryPixels.push_back({x, y});
        }
    }
    else
    { // slope |m| > 1.0;
        int d = (2 * dx) - dy;
        int s = 2 * dx;
        int es = (dx - dy) * 2;

        if (y0 < y1)
        {
            x = x0;
            y = y0;
        }
        else
        {
            x = x1;
            y = y1;
            x1 = x0;
            y1 = y0;
        }
        boundaryPixels.push_back({x, y});

        while (y < y1)
        {
            if (d <= 0)
                d += s;
            else
            {
                d += es;
                if (x > x1)
                    x--;
                else
                    x++;
            }
            y++;
            boundaryPixels.push_back({x, y});
        }
    }
    x1 = temp1;
    y1 = temp2;
}

vector<vector<int>> getTrianglePixels(GLint x0, GLint y0, GLint x1, GLint y1, GLint x2, GLint y2)
{
    vector<vector<int>> boundaryPixels;

    getBoudaryPixels(x0, y0, x1, y1, boundaryPixels);
    getBoudaryPixels(x1, y1, x2, y2, boundaryPixels);
    getBoudaryPixels(x2, y2, x0, y0, boundaryPixels);

    int xmin = min(x0, min(x1, x2));
    int xmax = max(x0, max(x1, x2));
    int ymin = min(y0, min(y1, y2));
    int ymax = max(y0, max(y1, y2));

    int activePixelsMatrixWidth = xmax - xmin + 1;
    int activePixelsMatrixHeight = ymax - ymin + 1;
    vector<vector<int>> activePixelsMatrix(activePixelsMatrixHeight, vector<int>(activePixelsMatrixWidth, 0));

    // Mark all boundary pixels active
    for (auto vertex : boundaryPixels)
        // Shift origin to the bottom left of triangle
        activePixelsMatrix[vertex[1] - ymin][vertex[0] - xmin] = 1;

    // Marking pixels active row by row within
    // active columns defined by the boundary pixels
    for (int i = 0; i < activePixelsMatrixHeight; i++)
    {
        bool inActiveRange = false;
        for (int j = 0; j < activePixelsMatrixWidth; j++)
        {
            if (activePixelsMatrix[i][j] == 1)
            {
                if (!inActiveRange)
                    inActiveRange = true;
                else
                {
                    inActiveRange = false;
                    break;
                }
            }
            if (inActiveRange)
            {
                activePixelsMatrix[i][j] = 1;

                // Handle cases when no two points are collinear
                if (j == x0 - xmin && i == y0 - ymin)
                {
                    if (abs(y1 - y0) != 0 && abs(y2 - y0) != 0)
                        inActiveRange = false;
                }
                else if (j == x1 - xmin && i == y1 - ymin)
                {
                    if (abs(y0 - y1) != 0 && abs(y2 - y1) != 0)
                        inActiveRange = false;
                }
                else if (j == x2 - xmin && i == y2 - ymin)
                {
                    if (abs(y0 - y2) != 0 && abs(y1 - y2) != 0)
                        inActiveRange = false;
                }
            }
        }
    }
    return activePixelsMatrix;
}

void drawTriangle(GLint x0, GLint y0, GLint x1, GLint y1, GLint x2, GLint y2)
{
    vector<vector<int>> pixelsMatrix = getTrianglePixels(x0, y0, x1, y1, x2, y2);

    int xmin = min(x0, min(x1, x2));
    int ymin = min(y0, min(y1, y2));

    glBegin(GL_POINTS);
    for (int i = 0; i < pixelsMatrix.size(); i++)
    {
        for (int j = 0; j < pixelsMatrix[0].size(); j++)
        {
            if (pixelsMatrix[i][j] == 1)
                // Shift origin from the bottom left of triangle back to origin
                glVertex2i(j + xmin, i + ymin);
        }
    }
    glEnd();
}

void renderTriangle(void)
{
    glClear(GL_COLOR_BUFFER_BIT); // Clear display window.
    glColor3f(1.0, 0.0, 0.0);
    drawTriangle(300, 40, 20, 350, 35, 10);
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
    glutCreateWindow("Triangle Using Extended Line Algorithm"); // create display window
    init();                                                          // execute initialization procedure
    glutDisplayFunc(renderTriangle);                                 // send graphics to display window
    glutMainLoop();                                                  // display everything and wait
    return 0;
}
