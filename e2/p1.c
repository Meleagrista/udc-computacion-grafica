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

int piece_index = 0;
int pieces = 0;
int arm_index = 0;

float anglesX[20] = {0.0f};
float anglesY[20] = {0.0f};
float anglesZ[20] = {0.0f};

int hazPerspectiva = 0;

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    if(hazPerspectiva)
        gluPerspective(60.0f, (GLfloat)width/(GLfloat)height, 1.0f, 20.0f);
    else       
        glOrtho(-12, 12, -12, 12, -10, 15);

    glMatrixMode(GL_MODELVIEW);
 
    ancho = width;
    alto = height;
}

void drawShiftedSphere(GLfloat x, GLfloat y, GLfloat z) {
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(anglesX[pieces + arm_index], 1.0f, 0.0f, 0.0f);
    glRotatef(anglesY[pieces + arm_index], 0.0f, 1.0f, 0.0f);
    glRotatef(anglesZ[pieces + arm_index], 0.0f, 0.0f, 1.0f);
    
    glColor3f(1.0f, 0.0f, 0.0f); // Color rojo
    glutSolidSphere(0.5, 30, 30);
}

void drawSphere(GLboolean vertical, GLfloat direction, GLboolean hand) {
    glMatrixMode(GL_MODELVIEW);

    if(arm_index == 0)
    {
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.0f);
        glRotatef(anglesX[pieces + arm_index], 1.0f, 0.0f, 0.0f);
        glRotatef(anglesY[pieces + arm_index], 0.0f, 1.0f, 0.0f);
        glRotatef(anglesZ[pieces + arm_index], 0.0f, 0.0f, 1.0f);
    }
    else if(arm_index == 1)
    {
        if (vertical)
            glTranslatef(0.0f, -1.5f * direction, 0.0f);
        else
            glTranslatef(1.5f * direction, 0.0f, 0.0f);
    }

    if(hand)
        glColor3f(0.0f, 1.0f, 0.0f); // Color verde
    else
        glColor3f(1.0f, 0.0f, 0.0f); // Color rojo

    glutSolidSphere(0.5, 30, 30);
}

void drawArmCube(GLboolean vertical, GLfloat direction)
{
    glMatrixMode(GL_MODELVIEW);
    
    if(arm_index == 1)
    {
        glRotatef(anglesX[pieces + arm_index], 1.0f, 0.0f, 0.0f);
        glRotatef(anglesY[pieces + arm_index], 0.0f, 1.0f, 0.0f);
        glRotatef(anglesZ[pieces + arm_index], 0.0f, 0.0f, 1.0f);
    }

    if(vertical)
    {
        glTranslatef(0.0f, -1.5f * direction, 0.0f);
        glPushMatrix();
        glScalef(1.0f, 2.0f, 1.0f);
    }
    else
    {
        glTranslatef(1.5f * direction, 0.0f, 0.0f);
        glPushMatrix();
        glScalef(2.0f, 1.0f, 1.0f);
    }

    glColor3f(0.0f, 0.0f, 1.0f); // Color azul

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

    if(vertical)
        glColor3f(0.0f, 1.0f, 0.0f); // Color verde
    else
        glColor3f(0.0f, 0.0f, 1.0f); // Color azul

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

    if(vertical)
        glColor3f(0.0f, 0.0f, 1.0f); // Color azul
    else
        glColor3f(0.0f, 1.0f, 0.0f); // Color verde

    // Cara derecha
    glBegin(GL_QUADS);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glEnd();

    // Cara izquierda
    glBegin(GL_QUADS);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glEnd();

    glPopMatrix();
}

void drawHandCube(GLboolean vertical, GLfloat direction)
{
    glMatrixMode(GL_MODELVIEW);

    if(vertical)
        glTranslatef(0.0f, -1.5f * direction, 0.0f);
    else
        glTranslatef(1.5f * direction, 0.0f, 0.0f);

    glColor3f(0.0f, 1.0f, 1.0f); // Color cian

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

    if(vertical)
        glColor3f(1.0f, 0.0f, 0.0f); // Color rojo

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

    glColor3f(1.0f, 0.0f, 0.0f); // Color verde

    if(vertical)
        glColor3f(0.0f, 1.0f, 1.0f); // Color cian

    // Cara derecha
    glBegin(GL_QUADS);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glEnd();

    // Cara izquierda
    glBegin(GL_QUADS);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glEnd();
}

void drawBodyCube()
{
    glMatrixMode(GL_MODELVIEW);

    pieces = 0;
    
    glTranslatef(0.0f, 0.0f, 0.0f);
    glRotatef(anglesX[pieces], 1.0f, 0.0f, 0.0f);
    glRotatef(anglesY[pieces], 0.0f, 1.0f, 0.0f);
    glRotatef(anglesZ[pieces], 0.0f, 0.0f, 1.0f);

    glPushMatrix();
    glScalef(2.0f, 4.0f, 1.0f);

    glColor3f(0.0f, 1.0f, 1.0f); // Color cian

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

    glColor3f(0.0f, 1.0f, 0.0f); // Color verde

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

    // Cara derecha
    glBegin(GL_QUADS);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glEnd();

    // Cara izquierda
    glBegin(GL_QUADS);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glEnd();

    pieces++;
    glPopMatrix();
}

void drawExtemity(GLboolean vertical, GLfloat direction, GLfloat x, GLfloat y, GLfloat z)
{
    drawShiftedSphere(x, y, z);
    drawArmCube(vertical, direction);
    arm_index++;
    drawSphere(vertical, direction, GL_FALSE);
    drawArmCube(vertical, direction);
    //drawSphere(vertical, direction, GL_TRUE);
    drawHandCube(vertical, direction);
    arm_index = 0;

    glPopMatrix();
    pieces = pieces + 2;
}

void display()
{ 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    drawBodyCube();

    //pieces = 0;

    // Legs
    drawExtemity(GL_TRUE, 1.0, -0.5, -2.5, 0.0);
    drawExtemity(GL_TRUE, 1.0, 0.5, -2.5, 0.0);

    // Arms
    drawExtemity(GL_FALSE, -1.0, -1.5, 1.5, 0.0);
    drawExtemity(GL_FALSE, 1.0, 1.5, 1.5, 0.0);

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
            piece_index++;
            if(piece_index == pieces)
                piece_index = 0;
            break;
        case 'q':
            anglesX[piece_index] += 1.0f;
            break;
        case 'a':
            anglesX[piece_index] -= 1.0f;
            break;
        case 'w':
            anglesY[piece_index] += 1.0f;
            break;
        case 's':
            anglesY[piece_index] -= 1.0f;
            break;
        case 'e':
            anglesZ[piece_index] += 1.0f;
            break;
        case 'd':
            anglesZ[piece_index] -= 1.0f;
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