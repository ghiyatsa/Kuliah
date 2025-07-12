#include <GL/freeglut.h>

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLineWidth(2.0f);

    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(20.0f, 10.0f, 0.0f);
    glColor3f(1.0f, 0.5f, 0.0f);
    glVertex3f(20.0f, 90.0f, 0.0f);

    glColor3f(1.0f, 0.5f, 0.0f);
    glVertex3f(40.0f, 10.0f, 0.0f);
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(40.0f, 90.0f, 0.0f);

    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(60.0f, 10.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(60.0f, 90.0f, 0.0f);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(80.0f, 10.0f, 0.0f);
    glColor3f(0.5f, 0.0f, 1.0f);
    glVertex3f(80.0f, 90.0f, 0.0f);
    glEnd();

    glFlush();
}

void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, 100.0f, 0.0f, 100.0f, -100.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Kuis Grafika 2");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
