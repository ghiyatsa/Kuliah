#include <GL/glut.h>
#include <cmath>

const int CIRCLE_SEGMENTS = 50;

float sun_y_position = 80.0f;
float background_r = 0.53f;
float background_g = 0.81f;
float background_b = 0.98f;

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

void drawPlant()
{
    // Lebih realistis hijau tua untuk rumput/tanah
    drawRectangle(-150.0f, -100.0f, 150.0f, -10.0f, 0.13f, 0.55f, 0.13f);
}

void drawMountains()
{
    // Warna gunung yang lebih bervariasi (abu-abu kecoklatan)
    glColor3f(0.5f, 0.45f, 0.4f);
    glBegin(GL_POLYGON);
    glVertex2f(-130.0f, -10.0f);
    glVertex2f(-60.0f, 60.0f);
    glVertex2f(10.0f, -10.0f);
    glEnd();

    glColor3f(0.45f, 0.4f, 0.35f); // Sedikit lebih gelap
    glBegin(GL_POLYGON);
    glVertex2f(-60.0f, -10.0f);
    glVertex2f(0.0f, 70.0f);
    glVertex2f(60.0f, -10.0f);
    glEnd();

    glColor3f(0.55f, 0.5f, 0.45f); // Sedikit lebih terang
    glBegin(GL_POLYGON);
    glVertex2f(-10.0f, -10.0f);
    glVertex2f(60.0f, 60.0f);
    glVertex2f(130.0f, -10.0f);
    glEnd();
}

void drawSnow()
{
    // Salju putih kebiruan (memberi kesan dingin)
    glColor3f(0.95f, 0.98f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-70.0f, 50.0f);
    glVertex2f(-60.0f, 60.0f);
    glVertex2f(-50.0f, 50.0f);
    glVertex2f(-60.0f, 40.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-15.0f, 50.0f);
    glVertex2f(0.0f, 70.0f);
    glVertex2f(15.0f, 50.0f);
    glVertex2f(0.0f, 40.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(50.0f, 50.0f);
    glVertex2f(60.0f, 60.0f);
    glVertex2f(70.0f, 50.0f);
    glVertex2f(60.0f, 40.0f);
    glEnd();
}

void drawRoad()
{
    // Warna aspal gelap yang lebih realistis
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_POLYGON);
    glVertex2f(-40.0f, -100.0f);
    glVertex2f(-20.0f, -10.0f);
    glVertex2f(10.0f, -10.0f);
    glVertex2f(30.0f, -100.0f);
    glEnd();
}

void drawTree()
{
    // Daun hijau tua yang kaya
    glColor3f(0.0f, 0.4f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-110.0f, -70.0f);
    glVertex2f(-90.0f, -20.0f);
    glVertex2f(-70.0f, -70.0f);
    glEnd();

    // Batang pohon coklat gelap
    drawRectangle(-95.0f, -100.0f, -85.0f, -70.0f, 0.29f, 0.18f, 0.07f);
}

void drawHome()
{
    // Dinding rumah krem/beige yang lebih soft
    glColor3f(0.96f, 0.88f, 0.77f);
    glBegin(GL_POLYGON);
    glVertex2f(60.0f, -70.0f);
    glVertex2f(60.0f, -40.0f);
    glVertex2f(75.0f, -20.0f);
    glVertex2f(90.0f, -40.0f);
    glVertex2f(90.0f, -70.0f);
    glEnd();

    // Sisi kanan rumah sedikit lebih gelap
    drawRectangle(90.0f, -70.0f, 110.0f, -40.0f, 0.9f, 0.82f, 0.7f);

    // Atap merah bata
    glColor3f(0.6f, 0.2f, 0.2f);
    glBegin(GL_POLYGON);
    glVertex2f(90.0f, -40.0f);
    glVertex2f(75.0f, -20.0f);
    glVertex2f(95.0f, -20.0f);
    glVertex2f(110.0f, -40.0f);
    glEnd();

    // Pintu coklat tua
    drawRectangle(70.0f, -70.0f, 80.0f, -55.0f, 0.4f, 0.2f, 0.05f);

    // Jendela biru muda transparan
    drawRectangle(70.0f, -45.0f, 80.0f, -40.0f, 0.5f, 0.8f, 1.0f);

    // Jendela samping biru muda transparan
    drawRectangle(95.0f, -60.0f, 105.0f, -50.0f, 0.5f, 0.8f, 1.0f);
}

void drawBird()
{
    // Burung hitam
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-120.0f, 70.0f);
    glVertex2f(-115.0f, 75.0f);
    glVertex2f(-110.0f, 70.0f);
    glVertex2f(-105.0f, 75.0f);
    glVertex2f(-100.0f, 70.0f);
    glEnd();
}

void drawSun()
{
    // Matahari kuning-oranye yang lebih cerah
    drawCircle(110.0f, sun_y_position, 15.0f, 1.0f, 0.9f, 0.2f);
}

void display()
{
    glClearColor(background_r, background_g, background_b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    drawPlant();
    drawMountains();
    drawSnow();
    drawRoad();
    drawTree();
    drawHome();
    drawBird();
    drawSun();
    glFlush();
}

void update(int value)
{
    float sun_speed = 0.5f;
    float lower_bound = -50.0f;
    float upper_bound = 80.0f;

    static int direction = -1;

    sun_y_position += (direction * sun_speed);

    if (sun_y_position < lower_bound)
    {
        sun_y_position = lower_bound;
        direction = 1;
    }
    else if (sun_y_position > upper_bound)
    {
        sun_y_position = upper_bound;
        direction = -1;
    }

    float normalized_y = (sun_y_position - lower_bound) / (upper_bound - lower_bound);

    // Interpolasi warna langit dari biru gelap (malam) ke biru cerah (siang)
    background_r = 0.05f + (0.53f - 0.05f) * normalized_y;
    background_g = 0.1f + (0.81f - 0.1f) * normalized_y;
    background_b = 0.2f + (0.98f - 0.2f) * normalized_y;

    glutPostRedisplay();
    glutTimerFunc(50, update, 0);
}

void init()
{
    glClearColor(background_r, background_g, background_b, 1.0f);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-150, 150, -100, 100);
    sun_y_position = 80.0f;
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(900, 600);
    glutCreateWindow("Nature Scene with Moving Sun");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}
