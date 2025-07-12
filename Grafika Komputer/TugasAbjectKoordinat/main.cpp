#include <GL/glut.h>
#include <cmath>
#include <string>
#include <sstream>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-400, 400, -300, 300);
}

void drawText(float x, float y, const std::string& text)
{
    glRasterPos2f(x, y);
    for (char c : text)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
}

void drawAxes()
{
    glColor3f(0.0, 0.0, 0.0);

    glBegin(GL_LINES);
    glVertex2f(-400, 0);
    glVertex2f(400, 0);
    glVertex2f(0, -300);
    glVertex2f(0, 300);
    glEnd();

    drawText(380, -15, "X");
    drawText(-15, 280, "Y");

    glColor3f(0.7, 0.7, 0.7);
    glBegin(GL_LINES);
    for (int i = -400; i <= 400; i += 20)
    {
        glVertex2f(i, -5);
        glVertex2f(i, 5);
        if (i % 100 == 0 && i != 0)
        {
            std::ostringstream oss;
            oss << i;
            drawText(i - 10, -20, oss.str());
        }
    }
    for (int i = -300; i <= 300; i += 20)
    {
        glVertex2f(-5, i);
        glVertex2f(5, i);
        if (i % 100 == 0 && i != 0)
        {
            std::ostringstream oss;
            oss << i;
            drawText(-30, i - 5, oss.str());
        }
    }
    glEnd();

    glColor3f(1.0, 0.0, 0.0);
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glVertex2f(0, 0);
    glEnd();
    drawText(5, 5, "(0,0)");
}

void drawShapes()
{
    // Segitiga merah
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(0, 200);
    glVertex2f(-60, 100);
    glVertex2f(60, 100);
    glEnd();

    glColor3f(0.0, 0.0, 0.0);
    drawText(-10, 210, "(0,200)");
    drawText(-90, 100, "(-60,100)");
    drawText(70, 100, "(60,100)");

    // Persegi panjang hijau
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_QUADS);
    glVertex2f(-60, 80);
    glVertex2f(60, 80);
    glVertex2f(60, -80);
    glVertex2f(-60, -80);
    glEnd();

    glColor3f(0.0, 0.0, 0.0);
    drawText(-90, 80, "(-60,80)");
    drawText(70, 80, "(60,80)");
    drawText(70, -90, "(60,-80)");
    drawText(-90, -90, "(-60,-80)");

    // Lingkaran biru
    glColor3f(0.0, 0.0, 1.0);
    const int numSegments = 100;
    const float radius = 60;
    const float centerX = 0;
    const float centerY = -160;
    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments; i++)
    {
        float theta = 2.0f * M_PI * float(i) / float(numSegments);
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        glVertex2f(x + centerX, y + centerY);
    }
    glEnd();

    glColor3f(0.0, 0.0, 0.0);
    drawText(-20, -150, "(0,-160)");
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();
    drawShapes();
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Objek dan Koordinat");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
