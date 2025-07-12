#include <GL/freeglut.h>

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(6.0f);

    glBegin(GL_POINTS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(25.0f, 25.0f,0.0);
    glVertex3f(25.0f, 75.0f,0.0);
    glVertex3f(75.0f, 25.0f,0.0);
    glVertex3f(75.0f, 75.0f,0.0);
    glEnd();
    glFlush();
}

void init()
{
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    gluOrtho2D(0, 100, 0, 100);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Kuis Grafika 1");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
