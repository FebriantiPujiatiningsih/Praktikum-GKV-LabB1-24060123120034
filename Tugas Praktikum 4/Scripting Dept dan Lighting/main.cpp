#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

// Variabel untuk kontrol kamera
float angle = 0.0, deltaAngle = 0.0, ratio;
float x = 0.0f, y = 1.75f, z = 15.0f; // Posisi awal kamera
float lx = 0.0f, ly = 0.0f, lz = -1.0f;
int deltaMove = 0, h, w;

// Fungsi untuk menangani perubahan ukuran jendela
void Reshape(int w1, int h1) {
    if (h1 == 0) h1 = 1;
    w = w1;
    h = h1;
    ratio = 1.0f * w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45, ratio, 0.1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
}

// Fungsi untuk mengubah orientasi kamera (tengok kiri/kanan)
void orientMe(float ang) {
    lx = sin(ang);
    lz = -cos(ang);
    glLoadIdentity();
    gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
}

// Fungsi untuk menggerakkan kamera maju/mundur
void moveMeFlat(int i) {
    x += i * (lx) * 0.1;
    z += i * (lz) * 0.1;
    glLoadIdentity();
    gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
}

// Fungsi untuk menggambar grid lantai
void Grid() {
    const float Z_MIN = -50, Z_MAX = 50;
    const float X_MIN = -50, X_MAX = 50;
    const float gap = 1.5;
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_LINES);
    for (double i = Z_MIN; i < Z_MAX; i += gap) {
        glVertex3f(i, 0, Z_MIN);
        glVertex3f(i, 0, Z_MAX);
    }
    for (double i = X_MIN; i < X_MAX; i += gap) {
        glVertex3f(X_MIN, 0, i);
        glVertex3f(X_MAX, 0, i);
    }
    glEnd();
}

// Fungsi untuk menggambar kubus kayu
void KotakKayu() {
    glPushMatrix();
    glTranslatef(0, 0, 3);
    glBegin(GL_QUADS);
    glVertex3f(-3.0f, -3.0f, 0.0f);
    glVertex3f(3.0f, -3.0f, 0.0f);
    glVertex3f(3.0f, 3.0f, 0.0f);
    glVertex3f(-3.0f, 3.0f, 0.0f);
    glEnd();
    glPopMatrix();
}

// Fungsi utama untuk menampilkan objek 3D
void display() {
    if (deltaMove) moveMeFlat(deltaMove);
    if (deltaAngle) {
        angle += deltaAngle;
        orientMe(angle);
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Grid();
    KotakKayu();
    glutSwapBuffers();
    glFlush();
}

// Fungsi untuk menangani input keyboard saat tombol ditekan
void pressKey(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT: deltaAngle = -0.01f; break;
        case GLUT_KEY_RIGHT: deltaAngle = 0.01f; break;
        case GLUT_KEY_UP: deltaMove = 1; break;
        case GLUT_KEY_DOWN: deltaMove = -1; break;
    }
}

// Fungsi untuk menangani input keyboard saat tombol dilepas
void releaseKey(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT: if (deltaAngle < 0.0f) deltaAngle = 0.0f; break;
        case GLUT_KEY_RIGHT: if (deltaAngle > 0.0f) deltaAngle = 0.0f; break;
        case GLUT_KEY_UP: if (deltaMove > 0) deltaMove = 0; break;
        case GLUT_KEY_DOWN: if (deltaMove < 0) deltaMove = 0; break;
    }
}

// Pengaturan pencahayaan
void lighting() {
    const GLfloat light_position[] = { 0.0f, 20.0f, 10.0f, 1.0f };
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

// Inisialisasi OpenGL
void init(void) {
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("3D Lighting");
    glutIgnoreKeyRepeat(1);
    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(Reshape);
    lighting();
    init();
    glutMainLoop();
    return 0;
}
