#include <GL/glut.h>
#include <cmath>

const int CIRCLE_SEGMENTS = 50; // Jumlah segmen untuk menggambar lingkaran

float sun_y_position = 80.0f; // Posisi Y matahari
float background_r = 0.53f;   // Komponen merah warna latar belakang
float background_g = 0.81f;   // Komponen hijau warna latar belakang
float background_b = 0.98f;   // Komponen biru warna latar belakang

// Bendera untuk mengontrol animasi siang-malam
bool animateDayNight = false;
// Posisi Y target matahari dan warna latar belakang target
float target_sun_y = 80.0f; // Defaultnya siang (matahari di atas)
float target_bg_r = 0.53f;
float target_bg_g = 0.81f;
float target_bg_b = 0.98f;

// Fungsi untuk menggambar lingkaran
void drawCircle(float cx, float cy, float radius, float r, float g, float b)
{
    glColor3f(r, g, b); // Mengatur warna lingkaran
    glBegin(GL_POLYGON); // Memulai menggambar poligon (lingkaran solid)
    for (int i = 0; i <= CIRCLE_SEGMENTS; i++)
    {
        float theta = 2.0f * M_PI * float(i) / CIRCLE_SEGMENTS; // Sudut untuk setiap segmen
        float x = radius * cosf(theta); // Koordinat X titik pada lingkaran
        float y = radius * sinf(theta); // Koordinat Y titik pada lingkaran
        glVertex2f(x + cx, y + cy);     // Menggambar titik
    }
    glEnd(); // Mengakhiri gambar poligon
}

// Fungsi untuk menggambar persegi panjang
void drawRectangle(float x1, float y1, float x2, float y2, float r, float g, float b)
{
    glColor3f(r, g, b); // Mengatur warna persegi panjang
    glBegin(GL_POLYGON); // Memulai menggambar poligon (persegi panjang solid)
    glVertex2f(x1, y1);  // Sudut kiri bawah
    glVertex2f(x1, y2);  // Sudut kiri atas
    glVertex2f(x2, y2);  // Sudut kanan atas
    glVertex2f(x2, y1);  // Sudut kanan bawah
    glEnd(); // Mengakhiri gambar poligon
}

// Fungsi untuk menggambar tanaman (rumput/tanah)
void drawPlant()
{
    // Warna hijau tua yang lebih realistis untuk rumput/tanah
    drawRectangle(-150.0f, -100.0f, 150.0f, -10.0f, 0.13f, 0.55f, 0.13f);
}

// Fungsi untuk menggambar gunung
void drawMountains()
{
    // Warna gunung yang lebih bervariasi (abu-abu kecoklatan)
    glColor3f(0.5f, 0.45f, 0.4f); // Gunung pertama
    glBegin(GL_POLYGON);
    glVertex2f(-130.0f, -10.0f);
    glVertex2f(-60.0f, 60.0f);
    glVertex2f(10.0f, -10.0f);
    glEnd();

    glColor3f(0.45f, 0.4f, 0.35f); // Gunung kedua (sedikit lebih gelap)
    glBegin(GL_POLYGON);
    glVertex2f(-60.0f, -10.0f);
    glVertex2f(0.0f, 70.0f);
    glVertex2f(60.0f, -10.0f);
    glEnd();

    glColor3f(0.55f, 0.5f, 0.45f); // Gunung ketiga (sedikit lebih terang)
    glBegin(GL_POLYGON);
    glVertex2f(-10.0f, -10.0f);
    glVertex2f(60.0f, 60.0f);
    glVertex2f(130.0f, -10.0f);
    glEnd();
}

// Fungsi untuk menggambar salju di puncak gunung
void drawSnow()
{
    // Salju putih kebiruan (memberi kesan dingin)
    glColor3f(0.95f, 0.98f, 1.0f); // Salju di gunung pertama
    glBegin(GL_POLYGON);
    glVertex2f(-70.0f, 50.0f);
    glVertex2f(-60.0f, 60.0f);
    glVertex2f(-50.0f, 50.0f);
    glVertex2f(-60.0f, 40.0f);
    glEnd();

    glBegin(GL_POLYGON); // Salju di gunung kedua
    glVertex2f(-15.0f, 50.0f);
    glVertex2f(0.0f, 70.0f);
    glVertex2f(15.0f, 50.0f);
    glVertex2f(0.0f, 40.0f);
    glEnd();

    glBegin(GL_POLYGON); // Salju di gunung ketiga
    glVertex2f(50.0f, 50.0f);
    glVertex2f(60.0f, 60.0f);
    glVertex2f(70.0f, 50.0f);
    glVertex2f(60.0f, 40.0f);
    glEnd();
}

// Fungsi untuk menggambar jalan
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

// Fungsi untuk menggambar pohon
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

// Fungsi untuk menggambar rumah
void drawHome()
{
    // Dinding rumah krem/beige yang lebih lembut
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

// Fungsi untuk menggambar burung
void drawBird()
{
    // Burung hitam
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_STRIP); // Menggambar garis berurutan
    glVertex2f(-120.0f, 70.0f);
    glVertex2f(-115.0f, 75.0f);
    glVertex2f(-110.0f, 70.0f);
    glVertex2f(-105.0f, 75.0f);
    glVertex2f(-100.0f, 70.0f);
    glEnd();
}

// Fungsi untuk menggambar matahari
void drawSun()
{
    // Matahari kuning-oranye yang lebih cerah
    drawCircle(110.0f, sun_y_position, 15.0f, 1.0f, 0.9f, 0.2f);
}

// Fungsi display utama, dipanggil untuk menggambar ulang scene
void display()
{
    glClearColor(background_r, background_g, background_b, 1.0f); // Mengatur warna latar belakang
    glClear(GL_COLOR_BUFFER_BIT); // Membersihkan buffer warna
    drawSun();       // Menggambar matahari
    drawPlant();     // Menggambar tanaman
    drawMountains(); // Menggambar gunung
    drawSnow();      // Menggambar salju
    drawRoad();      // Menggambar jalan
    drawTree();      // Menggambar pohon
    drawHome();      // Menggambar rumah
    drawBird();      // Menggambar burung
    glFlush();       // Memaksa OpenGL untuk mengeksekusi perintah gambar
}

// Fungsi update, dipanggil secara berkala untuk animasi
void update(int value)
{
    if (animateDayNight) // Hanya jika animasi siang-malam diaktifkan
    {
        float sun_speed = 0.5f; // Kecepatan pergerakan matahari
        float lower_bound = -50.0f; // Batas bawah posisi matahari
        float upper_bound = 80.0f;  // Batas atas posisi matahari

        // Gerakkan matahari secara mulus menuju target
        if (sun_y_position < target_sun_y)
        {
            sun_y_position += sun_speed;
            if (sun_y_position > target_sun_y) sun_y_position = target_sun_y; // Pastikan tidak melewati target
        }
        else if (sun_y_position > target_sun_y)
        {
            sun_y_position -= sun_speed;
            if (sun_y_position < target_sun_y) sun_y_position = target_sun_y; // Pastikan tidak melewati target
        }

        // Interpolasi warna latar belakang menuju target
        float color_speed = 0.01f; // Kecepatan perubahan warna
        background_r += (target_bg_r - background_r) * color_speed;
        background_g += (target_bg_g - background_g) * color_speed;
        background_b += (target_bg_b - background_b) * color_speed;

        // Jika sudah sangat dekat dengan target, hentikan animasi
        if (fabs(sun_y_position - target_sun_y) < 0.1f &&
                fabs(background_r - target_bg_r) < 0.01f &&
                fabs(background_g - target_bg_g) < 0.01f &&
                fabs(background_b - target_bg_b) < 0.01f)
        {
            animateDayNight = false; // Hentikan animasi saat target tercapai
        }
    }

    glutPostRedisplay(); // Meminta penggambaran ulang jendela
    glutTimerFunc(50, update, 0); // Memanggil fungsi update lagi setelah 50 ms
}

// Fungsi callback untuk penekanan tombol keyboard
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'N': // Untuk malam
    case 'n':
        target_sun_y = -50.0f; // Matahari turun (malam)
        target_bg_r = 0.05f;   // Langit malam gelap
        target_bg_g = 0.1f;
        target_bg_b = 0.2f;
        animateDayNight = true; // Aktifkan animasi
        break;
    case 'D': // Untuk siang
    case 'd':
        target_sun_y = 80.0f;  // Matahari naik (siang)
        target_bg_r = 0.53f;   // Langit siang cerah
        target_bg_g = 0.81f;
        target_bg_b = 0.98f;
        animateDayNight = true; // Aktifkan animasi
        break;
    }
    glutPostRedisplay(); // Minta penggambaran ulang segera
}

// Fungsi inisialisasi awal OpenGL
void init()
{
    glClearColor(background_r, background_g, background_b, 1.0f); // Mengatur warna latar belakang awal
    glMatrixMode(GL_PROJECTION); // Mengatur mode matriks ke proyeksi
    gluOrtho2D(-150, 150, -100, 100); // Mengatur sistem koordinat 2D
    sun_y_position = 80.0f; // Memulai dengan posisi matahari di atas (siang)
}

// Fungsi utama program
int main(int argc, char** argv)
{
    glutInit(&argc, argv); // Menginisialisasi GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Mengatur mode tampilan
    glutInitWindowSize(900, 600); // Mengatur ukuran jendela
    glutCreateWindow("Scene Alam dengan Siklus Siang-Malam"); // Membuat jendela
    init(); // Panggil fungsi inisialisasi
    glutDisplayFunc(display); // Mendaftarkan fungsi display
    glutKeyboardFunc(keyboard); // Mendaftarkan fungsi callback keyboard
    glutTimerFunc(0, update, 0); // Memulai timer untuk animasi
    glutMainLoop(); // Memasuki loop utama GLUT
    return 0;
}
