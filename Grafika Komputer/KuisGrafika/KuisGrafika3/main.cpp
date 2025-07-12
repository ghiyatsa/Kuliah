#include <GL/freeglut.h>

void drawMonitor()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glColor3f(0.2f, 0.2f, 0.8f);
    glBegin(GL_QUADS);
    glVertex3f(-0.5f, 0.6f, 0.0f);
    glVertex3f( 0.5f, 0.6f, 0.0f);
    glVertex3f( 0.5f, 0.0f, 0.0f);
    glVertex3f(-0.5f, 0.0f, 0.0f);
    glEnd();

    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
    glVertex3f(-0.1f, -0.2f, 0.0f);
    glVertex3f( 0.1f, -0.2f, 0.0f);
    glVertex3f( 0.1f,  0.0f, 0.0f);
    glVertex3f(-0.1f,  0.0f, 0.0f);
    glEnd();

    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
    glVertex3f(-0.3f, -0.3f, 0.0f);
    glVertex3f( 0.3f, -0.3f, 0.0f);
    glVertex3f( 0.3f, -0.2f, 0.0f);
    glVertex3f(-0.3f, -0.2f, 0.0f);
    glEnd();

    glutSwapBuffers();
}

void init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Kuis Grafika 3");

    init();
    glutDisplayFunc(drawMonitor);
    glutMainLoop();

    return 0;
}
