#include <GL/glut.h>

// Global variables for camera control
float cameraAngleX = 0.0f;
float cameraAngleY = 0.0f;
float cameraDistance = 5.0f; // Initial distance from the teapot
int lastMouseX, lastMouseY;
int mouseButtonDown = 0; // 0: no button, 1: left, 2: middle, 3: right

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Apply camera transformations based on mouse and keyboard interaction
    glTranslatef(0.0f, 0.0f, -cameraDistance); // Move away from the origin
    glRotatef(cameraAngleX, 1.0f, 0.0f, 0.0f);   // Rotate around X-axis
    glRotatef(cameraAngleY, 0.0f, 1.0f, 0.0f);   // Rotate around Y-axis

    // --- Mengatur Warna Objek (Material) ---
    // Definisikan warna merah
    GLfloat material_ambient[] = { 1.0f, 0.0f, 0.0f, 1.0f };  // Merah
    GLfloat material_diffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f };  // Merah
    GLfloat material_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Refleksi putih
    GLfloat material_shininess = 50.0f; // Kekuatan kilau

    // Terapkan properti material ke objek
    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, material_shininess);

    // Anda bisa juga menggunakan glColor3f jika tidak menggunakan pencahayaan material
    // glColor3f(1.0, 0.0, 0.0); // Warna merah (untuk kawat)

    // Gambar wire teapot dengan ukuran 1.0
    glutWireTeapot(1.0);

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Latar belakang hitam
    glEnable(GL_DEPTH_TEST);

    // --- Mengaktifkan Pencahayaan ---
    glEnable(GL_LIGHTING); // Aktifkan sistem pencahayaan OpenGL
    glEnable(GL_LIGHT0);   // Aktifkan sumber cahaya pertama (GL_LIGHT0)

    // Definisikan properti cahaya
    GLfloat light_position[] = { 1.0f, 1.0f, 1.0f, 0.0f }; // Posisi cahaya (arah tak terbatas)
    GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };  // Cahaya ambien
    GLfloat light_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };  // Cahaya difus
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Cahaya spekular

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    // Mengaktifkan pewarnaan material secara otomatis dari glColor
    // Namun, karena kita menggunakan glMaterialfv, glColor tidak akan terlalu berpengaruh
    // jika GL_COLOR_MATERIAL tidak diaktifkan.
    // glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    // glEnable(GL_COLOR_MATERIAL);
}

// --- Mouse Interaction Functions ---

void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        mouseButtonDown = button;
        lastMouseX = x;
        lastMouseY = y;
    } else {
        mouseButtonDown = 0; // No button pressed
    }
}

void motion(int x, int y) {
    if (mouseButtonDown == GLUT_LEFT_BUTTON) { // Rotate with left mouse button
        cameraAngleY += (x - lastMouseX) * 0.5f;
        cameraAngleX += (y - lastMouseY) * 0.5f;
    }

    lastMouseX = x;
    lastMouseY = y;
    glutPostRedisplay(); // Request a redraw
}

// --- Keyboard Interaction Function ---

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': // Zoom in
        case 'W':
            cameraDistance -= 0.1f;
            if (cameraDistance < 1.0f) cameraDistance = 1.0f; // Prevent going too close
            break;
        case 's': // Zoom out
        case 'S':
            cameraDistance += 0.1f;
            if (cameraDistance > 10.0f) cameraDistance = 10.0f; // Prevent going too far
            break;
        case 'a': // Rotate left
        case 'A':
            cameraAngleY -= 5.0f; // Rotate 5 degrees to the left
            break;
        case 'd': // Rotate right
        case 'D':
            cameraAngleY += 5.0f; // Rotate 5 degrees to the right
            break;
        case 27: // ESC key to exit
            exit(0);
            break;
    }
    glutPostRedisplay(); // Request a redraw
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Wire Teapot - OpenGL (Colored)");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    // Register mouse and keyboard callback functions
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
