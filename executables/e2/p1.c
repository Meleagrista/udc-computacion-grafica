#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

/* CONTROLES:
 * 1. Las teclas de la práctica anterior mueven las piezas en los tres ejes.
 * 2. La tecla '1' selecciona la siguiente pieza para más información leer comentarios de la función display().
 * 3. Abrir el menú funciona como se describe en la práctica
 * 4. Hacer click derecho y arrastrar mueve la pieza seleccioanda al soltar el click.
 * 5. Pulsar CTRL selecciona la pierna izquierda, pulsar ALT selecciona la pierna derecha y si no se pulsa ninguna el cuerpo enterio es seleccionado.
 */

GLboolean wired = GL_FALSE;
GLboolean spin = GL_FALSE;
GLfloat spinSpeed = 2.0f;

GLint ancho = 400;
GLint alto = 400;

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

void drawJoint(GLfloat x, GLfloat y, GLfloat z) {
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(anglesX[pieces + arm_index], 1.0f, 0.0f, 0.0f);
    glRotatef(anglesY[pieces + arm_index], 0.0f, 1.0f, 0.0f);
    glRotatef(anglesZ[pieces + arm_index], 0.0f, 0.0f, 1.0f);
    
    glColor3f(1.0f, 0.0f, 0.0f); // Color rojo
    
    if(wired)
        glutWireSphere(0.5, 10, 10);
    else    
        glutSolidSphere(0.5, 30, 30);
}

void drawSphere(GLboolean vertical, GLfloat direction) {
    glMatrixMode(GL_MODELVIEW);

    if(arm_index == 0) //from the previous exercise
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

    glColor3f(1.0f, 0.0f, 0.0f); // Color rojo

    if(wired)
        glutWireSphere(0.5, 10, 10);
    else    
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

    if(wired)
        glutWireCube(1.0f);
    else
    {
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
    }    

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

    if(wired)
        glutWireCube(1.0f);
    else    
    {
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
    glScalef(3.0f, 5.0f, 1.0f);

    glColor3f(0.0f, 1.0f, 1.0f); // Color cian

    if(wired)
        glutWireCube(1.0f);
    else
    {
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
    }

    pieces++;
    glPopMatrix();
}

void drawExtremity(GLboolean vertical, GLfloat direction, GLfloat x, GLfloat y, GLfloat z)
{
    drawJoint(x, y, z); // move the sphere to the shoulder or hip
    drawArmCube(vertical, direction);

    arm_index++; // now the lower part of the extremity

    drawSphere(vertical, direction);
    drawArmCube(vertical, direction);
    drawHandCube(vertical, direction);

    arm_index = 0; // reset for the next extremity

    pieces = pieces + 2; // add the two pieces to the register

    glPopMatrix();
    
}

void display()
{ 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    drawBodyCube(); //piece correconding to p0

    // Draw the legs
    drawExtremity(GL_TRUE, 1.0, -1.0, -2.5, 0.0); //pieces correconding to p1 & p2
    drawExtremity(GL_TRUE, 1.0, 1.0, -2.5, 0.0); //pieces correconding to p3 & p4

    // Draw the arms
    drawExtremity(GL_FALSE, -1.0, -1.5, 2.0, 0.0); //pieces correconding to p5 & p6
    drawExtremity(GL_FALSE, 1.0, 1.5, 2.0, 0.0); //pieces correconding to p7 & p8

    if(spin) // if spin is active spin the lower part of the legs
    {
        anglesZ[2] += spinSpeed;
        anglesZ[4] += spinSpeed;
    }
    
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

void keyboard(unsigned char key, int x, int y) 
{
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

void main_menu(int id){
    switch( id){
    case 0:
        if(spin)
            spin = GL_FALSE;
        else
            spin = GL_TRUE;    
        break;
    case 1:
        exit(-1);
        break;
    }
}

void view_menu(int id){
    switch( id){
    case 0:
        wired = GL_TRUE;
        break;
    case 1:
        wired = GL_FALSE;
        break;
    }
}

void speed_menu(int id){
    switch( id){
    case 0:
        spinSpeed = 1.0f;
        break;
    case 1:
        spinSpeed = 2.0f;
        break;
    case 2:
        spinSpeed = 5.0f;
        break;    
    case 3:
        spinSpeed = 10.0f;
        break;     
    }
}

void CallMenu()
{
    int submenu = glutCreateMenu(view_menu);
    glutAddMenuEntry("Alamabre", 0);
    glutAddMenuEntry("Solidos", 1);

    int submenu2 = glutCreateMenu(speed_menu);
    glutAddMenuEntry("Despacio", 0);
    glutAddMenuEntry("Normal", 1);
    glutAddMenuEntry("Rapido", 2);
    glutAddMenuEntry("Turbo", 3);

    glutCreateMenu(main_menu);
    glutAddSubMenu("Visualizacion", submenu);
    glutAddMenuEntry("Giro automatico", 0);
    glutAddSubMenu("Velocidad de giro", submenu2);
    glutAddMenuEntry("Salir", 1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void ClickNDrag(int button, int state, int x, int y) {
    int selectedPiece = 0;

    if(glutGetModifiers() == GLUT_ACTIVE_CTRL)
        selectedPiece = 1;
    else if(glutGetModifiers() == GLUT_ACTIVE_ALT)
        selectedPiece = 3;

    int frameX;
    int frameY;

    if(state == GLUT_DOWN)  
    {
        frameX = x;
        frameY = y; 
    }  

    if(state == GLUT_UP)  
    {
        anglesZ[selectedPiece] += x - frameX;
        anglesX[selectedPiece] += y - frameY;
    } 
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

    glutMouseFunc(ClickNDrag);

    glutKeyboardFunc(keyboard);

    CallMenu();
    glutMainLoop();

    return 0;
}