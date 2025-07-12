#include <GL/glut.h>
#include <cmath>

const int CIRCLE_SEGMENTS = 50;

void drawCircle(float cx, float cy, float radius, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i <= CIRCLE_SEGMENTS; i++)
    {
        float theta = 2.0f * M_PI * float(i) / CIRCLE_SEGMENTS;
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void drawRectangle(float x1, float y1, float x2, float y2, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    glVertex2f(x1, y1);
    glVertex2f(x1, y2);
    glVertex2f(x2, y2);
    glVertex2f(x2, y1);
    glEnd();
}

void drawSirine()
{
    drawCircle(0.0f, 35.0f, 5.0f, 1.0f, 0.0f, 0.0f);
}

void drawWheel(float cx, float cy)
{
    drawCircle(cx, cy, 20.0f, 0.2f, 0.2f, 0.2f);
    drawCircle(cx, cy, 13.0f, 0.0f, 0.0f, 0.0f);
}

void drawBody()
{
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-88.0f, -36.0f);
    glVertex2f(-88.0f, 36.0f);
    glVertex2f(16.0f, 36.0f);
    glVertex2f(16.0f, 20.0f);
    glVertex2f(48.0f, 0.0f);
    glVertex2f(88.0f, 0.0f);
    glVertex2f(88.0f, -36.0f);
    glEnd();
}

void drawWindowsAndDoor()
{
    drawRectangle(-64.0f, -4.0f, -40.0f, 24.0f, 0.6f, 0.6f, 0.6f);
    drawRectangle(-32.0f, -4.0f, -8.0f, 24.0f, 0.6f, 0.6f, 0.6f);

    drawRectangle(4.0f, -4.0f, 20.0f, 12.0f, 0.6f, 0.6f, 0.6f);
    drawRectangle(4.0f, -28.0f, 20.0f, -8.0f, 0.6f, 0.6f, 0.6f);
}

void drawExhaust()
{
    drawRectangle(-92.0f, -28.0f, -88.0f, -16.0f, 0.2f, 0.2f, 0.2f);
}

void drawFrontLight()
{
    drawRectangle(88.0f, -32.0f, 90.0f, -16.0f, 1.0f, 1.0f, 0.0f);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawSirine();
    drawWheel(-46.0f, -36.0f);
    drawWheel(36.0f, -38.0f);
    drawBody();
    drawWheel(-50.0f, -40.0f);
    drawWheel(40.0f, -40.0f);
    drawWindowsAndDoor();
    drawExhaust();
    drawFrontLight();

    glFlush();
}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-100, 100, -100, 100);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Mobil Sederhana");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
