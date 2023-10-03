#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

GLint ancho = 400;
GLint alto = 400;

/* Idealmente... 
 * 1. Tendría que guardar cada pieza o mas bien grupo de piezas: esfera + cubo como instancias de una clase.
 * 2. Añadir a dicho 'prefab' las variables que la afectan, en este caso los angulos.
 * 3. Crear una agrupación mayor donde meter todos los componentes y donde poder seleccionarlos.
 */

int arm = 0;
int arm_num = 2;
int arm_now = 0;

float anglesX[] = {0.0f, 0.0f};
float anglesY[] = {0.0f, 0.0f};
float anglesZ[] = {0.0f, 0.0f};

int hazPerspectiva = 0;

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    if(hazPerspectiva)
        gluPerspective(60.0f, (GLfloat)width/(GLfloat)height, 1.0f, 20.0f);
    else       
        glOrtho(-6, 6, -6, 6, -10, 15);

    glMatrixMode(GL_MODELVIEW);
 
    ancho = width;
    alto = height;
}

void drawSphere() {
    glMatrixMode(GL_MODELVIEW);

    if(arm_now == 0)
    {
        glTranslatef(0.0f, 0.0f, 0.0f);
        glRotatef(anglesX[0], 1.0f, 0.0f, 0.0f);
        glRotatef(anglesY[0], 0.0f, 1.0f, 0.0f);
        glRotatef(anglesZ[0], 0.0f, 0.0f, 1.0f);
    }
    else if(arm_now == 1)
    {
        glTranslatef(1.5f, 0.0f, 0.0f);
    }
    
    glColor3f(1.0f, 0.0f, 0.0f); // Color rojo
    glutSolidSphere(0.5, 30, 30);
}

void drawCube()
{
    glMatrixMode(GL_MODELVIEW);
    
    if(arm_now == 1)
    {
        glRotatef(anglesX[1], 1.0f, 0.0f, 0.0f);
        glRotatef(anglesY[1], 0.0f, 1.0f, 0.0f);
        glRotatef(anglesZ[1], 0.0f, 0.0f, 1.0f);
    }

    glTranslatef(1.5f, 0.0f, 0.0f);
    glPushMatrix();
    glScalef(2.0f, 1.0f, 1.0f);

    glColor3f(0.0f, 0.0f, 1.0f); // Color rojo

    // Cara frontal
    glBegin(GL_QUADS);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glEnd();

    // Cara trasera
    glBegin(GL_QUADS);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glEnd();

    // Cara superior
    glBegin(GL_QUADS);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glEnd();

    // Cara fondo
    glBegin(GL_QUADS);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glEnd();

    glColor3f(0.0f, 1.0f, 0.0f); // Color verde

    // Cara derecha
    glBegin(GL_QUADS);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glEnd();

    glColor3f(0.0f, 1.0f, 0.0f); // Color verde

    // Cara izquierda
    glBegin(GL_QUADS);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glEnd();

    glPopMatrix();
}

void display()
{ 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    arm_now = 0; //Creamos el primer set.
    drawSphere();
    drawCube();

    arm_now = 1; //Creamos el segundo set.
    drawSphere();
    drawCube();
 
    glFlush();
    glutSwapBuffers();
}

void init()
{
    glClearColor(0,0,0,0);
    glEnable(GL_DEPTH_TEST);
    ancho = 400;
    alto = 400;
}

void idle()
{
    display();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) 
    {
        case '1':
            arm++;
            if(arm == arm_num)
                arm = 0;
            break;
        case 'q':
            anglesX[arm] += 1.0f;
            break;
        case 'a':
            anglesX[arm] -= 1.0f;
            break;
        case 'w':
            anglesY[arm] += 1.0f;
            break;
        case 's':
            anglesY[arm] -= 1.0f;
            break;
        case 'e':
            anglesZ[arm] += 1.0f;
            break;
        case 'd':
            anglesZ[arm] -= 1.0f;
            break;
    }

    glutPostRedisplay();
}
 
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB| GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(ancho, alto);
    glutCreateWindow("Brazo robotico");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}