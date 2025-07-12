#include <GL/glut.h>
#include "Game.h"
#include "Constants.h"

// Objek game global
Game game;

// --- Fungsi Wrapper untuk Callback GLUT ---
void display_wrapper() {
    game.render();
}

void update_wrapper(int value) {
    game.update();
    glutPostRedisplay();
    glutTimerFunc(16, update_wrapper, 0);
}

void mouse_motion_wrapper(int x, int y) {
    game.handleMouse(x, y);
}

void keyboard_wrapper(unsigned char key, int x, int y) {
    game.handleKeyboard(key);
}

void mouse_click_wrapper(int button, int state, int x, int y) {
    game.handleMouseClick(button, state, x, y);
}

void init_gl() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, SCREEN_WIDTH, 0.0, SCREEN_HEIGHT, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

// --- Fungsi Main ---
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Endless Block Breaker");

    init_gl();

    // Daftarkan fungsi wrapper sebagai callback
    glutDisplayFunc(display_wrapper);
    glutPassiveMotionFunc(mouse_motion_wrapper);
    glutKeyboardFunc(keyboard_wrapper);
    glutMouseFunc(mouse_click_wrapper);
    glutTimerFunc(0, update_wrapper, 0);

    glutMainLoop();
    return 0;
}
