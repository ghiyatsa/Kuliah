#include <GL/glut.h>
#include <cmath>
#include <string>

// Constants
const int CIRCLE_SEGMENTS = 50;

// Utility: Draw a circle
void drawCircle(float cx, float cy, float radius, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i <= CIRCLE_SEGMENTS; ++i)
    {
        float theta = 2.0f * M_PI * float(i) / CIRCLE_SEGMENTS;
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

// Utility: Draw a rectangle
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

// Main body of the pickup
void drawMainBody()
{
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-93.0f, -28.0f);
    glVertex2f(-93.0f, 6.0f);
    glVertex2f(-66.0f, 14.0f);
    glVertex2f(-42.0f, 43.0f);
    glVertex2f(5.0f, 43.0f);
    glVertex2f(5.0f, 13.0f);
    glVertex2f(96.0f, 13.0f);
    glVertex2f(96.0f, -28.0f);
    glEnd();
}

// Additional body parts
void drawBodyExtras()
{
    drawRectangle(-2.0f, 43.0f, 5.0f, 50.0f, 0.0f, 1.0f, 0.0f);     // Roof extension
    drawRectangle(90.0f, 13.0f, 96.0f, 17.0f, 0.0f, 1.0f, 0.0f);    // Tail detail
}

// Window section
void drawWindow()
{
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-63.0f, 14.0f);
    glVertex2f(-42.0f, 40.0f);
    glVertex2f(-2.0f, 40.0f);
    glVertex2f(-2.0f, 14.0f);
    glEnd();
}

// Wheel
void drawWheel(float cx, float cy)
{
    drawCircle(cx, cy, 20.0f, 0.2f, 0.2f, 0.2f); // Outer
    drawCircle(cx, cy, 13.0f, 0.0f, 0.0f, 0.0f); // Inner
}

// Exhaust pipe
void drawExhaust()
{
    drawRectangle(96.0f, -18.0f, 100.0f, -24.0f, 0.3f, 0.3f, 0.3f);
}

// Front light
void drawFrontLight()
{
    drawRectangle(-95.0f, -20.0f, -93.0f, -5.0f, 1.0f, 1.0f, 0.0f);
}

// Draw text on screen
void drawText(float x, float y, std::string text)
{
    glRasterPos2f(x, y);
    for (char c : text)
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c);
    }
}

// Draw Cartesian coordinate system
void drawCartesianPlane()
{
    glColor3f(0.0f, 0.0f, 0.0f); // Black

    glBegin(GL_LINES);
    glVertex2f(-120.0f, 0.0f);
    glVertex2f(120.0f, 0.0f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(0.0f, -120.0f);
    glVertex2f(0.0f, 120.0f);
    glEnd();

    for (int x = -100; x <= 100; x += 10)
    {
        glBegin(GL_LINES);
        glVertex2f(x, -2.0f);
        glVertex2f(x, 2.0f);
        glEnd();

        if (x != 0) drawText(x - 5, -10, std::to_string(x));
    }

    for (int y = -100; y <= 100; y += 10)
    {
        glBegin(GL_LINES);
        glVertex2f(-2.0f, y);
        glVertex2f(2.0f, y);
        glEnd();

        if (y != 0) drawText(5, y - 3, std::to_string(y));
    }
}

// Display everything
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawCartesianPlane(); // Coordinate background

    // Wheels
    drawWheel(-39.0f, -24.0f);
    drawWheel(44.0f, -24.0f);

    drawBodyExtras();
    drawMainBody();
    drawWindow();
    drawExhaust();
    drawFrontLight();

    drawWheel(-46.0f, -28.0f);
    drawWheel(48.0f, -28.0f);

    glFlush();
}

void init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-120.0, 120.0, -120.0, 120.0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Mobil Pickup UTS");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
