#include <math.h>
#include <stdio.h>
#include <GL/glut.h>

double rx = 0.0;
double ry = 0.0;
float l[] = { 0.0, 80.0, 0.0 }; // koordinat sumber cahaya
float n[] = { 0.0, -40.0, 0.0 };
float e[] = { 0.0, -60.0, 0.0 };

void help();

// Fungsi untuk menggambar torus
void draw()
{
    glutSolidTorus(10.0, 20.0, 30, 30);
}

//membuat proyeksi bayangan
void glShadowProjection(float * l, float * e, float * n)
{
    float d, c;
    float mat[16];
    d = n[0]*l[0] + n[1]*l[1] + n[2]*l[2];
    c = e[0]*n[0] + e[1]*n[1] + e[2]*n[2] - d;
    
    mat[0] = l[0]*n[0]+c;
    mat[4] = n[1]*l[0];
    mat[8] = n[2]*l[0];
    mat[12] = -l[0]*c-l[0]*d;
    mat[1] = n[0]*l[1];
    mat[5] = l[1]*n[1]+c;
    mat[9] = n[2]*l[1];
    mat[13] = -l[1]*c-l[1]*d;
    mat[2] = n[0]*l[2];
    mat[6] = n[1]*l[2];
    mat[10] = l[2]*n[2]+c;
    mat[14] = -l[2]*c-l[2]*d;
    mat[3] = n[0];
    mat[7] = n[1];
    mat[11] = n[2];
    mat[15] = -d;
    glMultMatrixf(mat);
}

void render()
{
    glClearColor(1.0, 0.75, 0.8, 0.0); // Latar belakang pink muda
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLightfv(GL_LIGHT0, GL_POSITION, l);
    glDisable(GL_CULL_FACE);
    glDisable(GL_LIGHTING);
    glColor3f(1.0,1.0,0.0);
    glBegin(GL_POINTS);
    glVertex3f(l[0],l[1],l[2]);
    glEnd();
    glColor3f(0.8,0.8,0.8);
    glBegin(GL_QUADS);
    glNormal3f(0.0,1.0,0.0);
    glVertex3f(-1300.0,e[1]-0.1, 1300.0);
    glVertex3f( 1300.0,e[1]-0.1, 1300.0);
    glVertex3f( 1300.0,e[1]-0.1,-1300.0);
    glVertex3f(-1300.0,e[1]-0.1,-1300.0);
    glEnd();
    
    glPushMatrix();
    glRotatef(ry,0,1,0);
    glRotatef(rx,1,0,0);
    glEnable(GL_LIGHTING);
    glColor3f(1.0, 0.1, 1.0); // Warna magenta
    draw();
    glPopMatrix();
    
    glPushMatrix();
    glShadowProjection(l,e,n);
    glRotatef(ry,0,1,0);
    glRotatef(rx,1,0,0);
    glDisable(GL_LIGHTING);
    glColor3f(0.4,0.4,0.4);
    draw();
    glPopMatrix();
    
    glutSwapBuffers();
}

void idle() {
    rx += 0.2;
    ry += 0.2;
    glutPostRedisplay();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(300, 30);
    glutCreateWindow("Proyeksi Bayangan Torus");
    glutReshapeWindow(400, 400);
    glutDisplayFunc(render);
    glutIdleFunc(idle);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, 1.0, 1.0, 400.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -150.0);
    glutMainLoop();
    return 0;
}
