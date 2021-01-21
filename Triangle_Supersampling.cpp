#include <GL/glut.h>
#include <GL/gl.h>
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> downSample(vector<vector<int>> displayMatrixHighRes, GLint rf)
{
    int width = displayMatrixHighRes[0].size() / rf;
    int height = displayMatrixHighRes.size() / rf;
    vector<vector<int>> displayMatrixAveraged(height, vector<int>(width, 0));

    //  Convolution with (rf by rf) grid
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gridValue = 0;
            for (int k = 0; k < rf; k++)
            {
                for (int l = 0; l < rf; l++)
                {
                    gridValue += displayMatrixHighRes[i * rf + k][j * rf + l];
                    displayMatrixAveraged[i][j] = gridValue / (rf * rf);
                }
            }
        }
    }
    return displayMatrixAveraged;
}

vector<vector<int>> getTriangleMatrixFromAlgo(GLint x0, GLint y0, GLint x1, GLint y1, GLint x2, GLint y2, GLint width, GLint height)
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
    int f0 = (xmin - x0) * dy0 - (ymax - y0) * dx0;
    int f1 = (xmin - x1) * dy1 - (ymax - y1) * dx1;
    int f2 = (xmin - x2) * dy2 - (ymax - y2) * dx2;

    int g0 = (x0 - x1) * dy1 - (y0 - y1) * dx1;
    int g1 = (x1 - x2) * dy2 - (y1 - y2) * dx2;
    int g2 = (x2 - x0) * dy0 - (y2 - y0) * dx0;

    vector<vector<int>> displayMatrix(height, vector<int>(width, 0));

    for (int y = ymax; y >= ymin; y--)
    {
        for (int x = xmin; x < xmax; x++)
        {
            float alpha = (float)f1 / g1;
            float beta = (float)f2 / g2;
            float gamma = (float)f0 / g0;
            float diff = 1.0 - (alpha + beta + gamma);
            if ((diff <= 0.00001 && diff >= -0.00001) && 0 <= alpha && alpha <= 1 && 0 <= beta && beta <= 1 && 0 <= gamma && gamma <= 1)
                displayMatrix[height - y][x] = 1;
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

    return displayMatrix;
}

vector<vector<int>> getSupersampledValues(GLint x0, GLint y0, GLint x1, GLint y1, GLint x2, GLint y2, GLint width, GLint height, GLint rf)
{
    // Create Triangle at (rf) times resolution
    vector<vector<int>> displayMatrixHighRes = getTriangleMatrixFromAlgo(
        x0 * rf, y0 * rf, x1 * rf, y1 * rf, x2 * rf, y2 * rf, width * rf, height * rf);
    vector<vector<int>> displayMatrixAveraged = downSample(displayMatrixHighRes, rf);
    return displayMatrixAveraged;
}

void drawTriangle(GLint x0, GLint y0, GLint x1, GLint y1, GLint x2, GLint y2, GLint width, GLint height, GLint resolutionFactor)
{
    // Get Supersampled Averaged pixel values
    vector<vector<int>> displayMatrix = getSupersampledValues(
        x0, y0, x1, y1, x2, y2, width, height, resolutionFactor);
    glBegin(GL_POINTS);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Get the averaged pixel value
            int pixelValue = displayMatrix[i][j];

            // Red Colored Triangle
            float r = 1.0;
            float g = 0.0;
            float b = 0.0;

            // Modify color values based on averaged pixel value
            r *= pixelValue;
            g *= pixelValue;
            b *= pixelValue;

            // Set the color of the pixels
            glColor3f(r, g, b);

            // Draw the vertex
            glVertex2i(j, height - i);
        }
    }
    glEnd();
}

void renderTriangle(void)
{
    glClear(GL_COLOR_BUFFER_BIT); // Clear display window.
    glColor3f(1.0, 0.0, 0.0);
    drawTriangle(30, 40, 200, 350, 350, 100, 500, 500, 4);
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
    glutCreateWindow("Triangle using Super Sampling"); // create display window
    init();                                                          // execute initialization procedure
    glutDisplayFunc(renderTriangle);                                 // send graphics to display window
    glutMainLoop();                                                  // display everything and wait
    return 0;
}
