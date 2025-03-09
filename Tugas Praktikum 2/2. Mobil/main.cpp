#include <GL/glut.h>
#include <math.h>

void drawRectangle(float x, float y, float width, float height) {
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

	// Lingkaran
void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Langit
    glColor3f(0.5, 0.8, 1.0);
    drawRectangle(-1, 0, 2, 1);

    // Matahari
    glColor3f(1.0, 1.0, 0.0);
    drawCircle(0.7, 0.8, 0.1, 20);

    // Awan
    glColor3f(1.0, 1.0, 1.0);
    drawCircle(-0.3, 0.8, 0.08, 20);
    drawCircle(-0.25, 0.85, 0.08, 20);
    drawCircle(-0.2, 0.8, 0.08, 20);

    drawCircle(0.3, 0.75, 0.08, 20);
    drawCircle(0.35, 0.8, 0.08, 20);
    drawCircle(0.4, 0.75, 0.08, 20);

    // Gedung dan jendela
    glColor3f(0.7, 0.7, 0.7);
    drawRectangle(-0.9, -0.05, 0.3, 0.6);
    drawRectangle(-0.5, 0.05, 0.3, 0.5);
    drawRectangle(0.1, 0.0, 0.4, 0.55);

    glColor3f(0.0, 0.0, 0.0);
    for (float x = -0.85; x <= -0.65; x += 0.1) {
        for (float y = 0.4; y >= 0.1; y -= 0.1) {
            drawRectangle(x, y, 0.05, 0.05);
        }
    }

    for (float x = -0.45; x <= -0.25; x += 0.1) {
        for (float y = 0.45; y >= 0.15; y -= 0.1) {
            drawRectangle(x, y, 0.05, 0.05);
        }
    }

    for (float x = 0.15; x <= 0.35; x += 0.1) {
        for (float y = 0.5; y >= 0.2; y -= 0.1) {
            drawRectangle(x, y, 0.05, 0.05);
        }
    }

    // Pohon
    float treePositions[3][2] = {{-0.6, -0.01}, {0.5, 0.02}, {-0.2, 0.02}};
    for (int i = 0; i < 3; i++) {
        glColor3f(0.5, 0.3, 0.1);
        drawRectangle(treePositions[i][0], treePositions[i][1], 0.05, 0.15);
        glColor3f(0.0, 0.8, 0.0);
        drawCircle(treePositions[i][0] + 0.020, treePositions[i][1] + 0.2, 0.08, 20);
        drawCircle(treePositions[i][0] - 0.03, treePositions[i][1] + 0.17, 0.08, 20);
        drawCircle(treePositions[i][0] + 0.08, treePositions[i][1] + 0.18, 0.08, 20);
    }
    
    // Semak-semak
    glColor3f(0.0, 0.6, 0.0);
    for (float x = -0.9; x <= 0.9; x += 0.3) {
        drawCircle(x, -0.1, 0.07, 20);
        drawCircle(x + 0.1, -0.05, 0.07, 20);
        drawCircle(x + 0.2, -0.1, 0.07, 20);
    }

    // Jalan
    glColor3f(0.3, 0.3, 0.3);
    drawRectangle(-1, -0.4, 2, 0.3);

    // Garis putih putus-putus
    glColor3f(1.0, 1.0, 1.0);
    for (float i = -0.9; i < 1; i += 0.2) {
        drawRectangle(i, -0.25, 0.1, 0.02);
    }

    // Rumput
    glColor3f(0.0, 0.8, 0.0);
    drawRectangle(-1, -1, 2, 0.6);

    // Mobil
    glPushMatrix();
    glTranslatef(-0.3, -0.12, 0);
    glScalef(1.5, 1.5, 1);

    // Badan mobil
    glColor3f(1.0, 0.0, 1.0);
    drawRectangle(-0.2, -0.1, 0.4, 0.1);
    drawRectangle(-0.1, 0.0, 0.2, 0.1);

    // Jendela mobil
    glColor3f(0.3, 0.3, 1.0);
    drawRectangle(-0.08, 0.02, 0.07, 0.06);
    drawRectangle(0.01, 0.02, 0.07, 0.06);

    // Lampu depan
    glColor3f(1.0, 1.0, 0.0);
    drawRectangle(0.19, -0.05, 0.03, 0.02);

    // Gagang pintu
    glColor3f(0.0, 0.0, 0.0);
    drawRectangle(0.02, -0.03, 0.03, 0.005);

    // Roda mobil
    glColor3f(0.0, 0.0, 0.0);
    drawCircle(-0.15, -0.12, 0.05, 20);
    drawCircle(0.15, -0.12, 0.05, 20);
    glColor3f(1.0, 1.0, 1.0);
    drawCircle(-0.15, -0.12, 0.025, 20);
    drawCircle(0.15, -0.12, 0.025, 20);

    glPopMatrix();

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Mobil 2D");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

