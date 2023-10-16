#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/freeglut.h>

// Global variables to store the window dimensions
GLint ancho = 400;
GLint alto = 400;

int frameX;
int frameY;

GLfloat coneAngle[] = {0.0f, 0.0f};
GLfloat objectAngle = 0.0f;
GLfloat armAngle = 0.0f;

GLboolean coneSpin = GL_TRUE;
GLboolean coneSpinReverse = GL_FALSE;
GLfloat coneSpinSpeed = 1.0f;

GLfloat cubeColors[] = {0.949f, 0.937f, 0.694f, 0.886f, 0.874f, 0.549f};

// Variable to control whether to use perspective projection
int hazPerspectiva = 0;

// CUSTOM FUNCTIONS

void drawFourCubes(GLdouble base, GLdouble space)
{
    glTranslatef(0.0f, 0.0f, - base / 2);

    GLfloat size = base / 2.0;  // Divide by 2 to make the size adjustment symmetric.

    for(int i = 0; i < 4; i++)
    {
        glPushMatrix();

        switch(i)
        {
            case 0:
                glTranslatef(space, space, 0.0f);
                break;
            case 1:
                glTranslatef(-space, space, 0.0f);
                break;
            case 2:
                glTranslatef(-space, -space, 0.0f);
                break;
            case 3:
                glTranslatef(space, -space, 0.0f);
                break;            
        }
        
        glColor3f(cubeColors[0], cubeColors[1], cubeColors[2]);

        // Cara frontal
        glBegin(GL_QUADS);
        glVertex3f(-size, -size, size);
        glVertex3f(size, -size, size);
        glVertex3f(size, size, size);
        glVertex3f(-size, size, size);
        glEnd();

        // Cara trasera
        glBegin(GL_QUADS);
        glVertex3f(-size, -size, -size);
        glVertex3f(size, -size, -size);
        glVertex3f(size, size, -size);
        glVertex3f(-size, size, -size);
        glEnd();

        glColor3f(cubeColors[3], cubeColors[4], cubeColors[5]);

        // Cara frontal
        glBegin(GL_QUADS);
        glVertex3f(-size, size, size);
        glVertex3f(size, size, size);
        glVertex3f(size, size, -size);
        glVertex3f(-size, size, -size);
        glEnd();

        // Cara trasera
        glBegin(GL_QUADS);
        glVertex3f(-size, -size, size);
        glVertex3f(size, -size, size);
        glVertex3f(size, -size, -size);
        glVertex3f(-size, -size, -size);
        glEnd();

        glColor3f(cubeColors[3], cubeColors[4], cubeColors[5]);

        // Cara derecha
        glBegin(GL_QUADS);
        glVertex3f(size, -size, size);
        glVertex3f(size, size, size);
        glVertex3f(size, size, -size);
        glVertex3f(size, -size, -size);
        glEnd();

        // Cara izquierda
        glBegin(GL_QUADS);
        glVertex3f(-size, -size, size);
        glVertex3f(-size, size, size);
        glVertex3f(-size, size, -size);
        glVertex3f(-size, -size, -size);
        glEnd();

        glPopMatrix();
    }

}

void drawInverseCone(GLdouble radious, GLdouble height, GLboolean axis)
{
    if(axis)
        glRotatef(coneAngle[1], 0.0f, 0.0f, 1.0f);

    glPushMatrix();
    
    glColor3f(0.678f, 0.847f, 0.706f); // Light Pastel Green

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -0.01f);
    glutSolidCylinder(radious - 0.1, 0.1, 20, 20);
    glPopMatrix();

    glColor3f(0.549f, 0.729f, 0.529f); // Darker Pastel Green

    glutSolidCone(radious, height, 20, 20); // Draw a solid cone

    glPopMatrix();
}

void drawArm(GLdouble base, GLdouble length, GLboolean axis)
{
    if(axis)
        glRotatef(armAngle, 0.0f, 0.0f, 1.0f);

    glPushMatrix();
    
    glTranslatef(0.0f, (length * base)/2, 0.0f);
    glScalef(1.0f, length, 1.0f);

    GLfloat size = base / 2.0;  // Divide by 2 to make the size adjustment symmetric.

    // Light Gray
    glColor3f(0.8f, 0.8f, 0.8f);

    // Cara frontal
    glBegin(GL_QUADS);
    glVertex3f(-size, -size, size);
    glVertex3f(size, -size, size);
    glVertex3f(size, size, size);
    glVertex3f(-size, size, size);
    glEnd();

    // Cara trasera
    glBegin(GL_QUADS);
    glVertex3f(-size, -size, -size);
    glVertex3f(size, -size, -size);
    glVertex3f(size, size, -size);
    glVertex3f(-size, size, -size);
    glEnd();

    // Light Gray
    glColor3f(0.7f, 0.7f, 0.7f);

    // Cara superior
    glBegin(GL_QUADS);
    glVertex3f(-size, size, size);
    glVertex3f(size, size, size);
    glVertex3f(size, size, -size);
    glVertex3f(-size, size, -size);
    glEnd();

    // Cara fondo
    glBegin(GL_QUADS);
    glVertex3f(-size, -size, size);
    glVertex3f(size, -size, size);
    glVertex3f(size, -size, -size);
    glVertex3f(-size, -size, -size);
    glEnd();

    glColor3f(0.9f, 0.9f, 0.9f);

    // Cara derecha
    glBegin(GL_QUADS);
    glVertex3f(size, -size, size);
    glVertex3f(size, size, size);
    glVertex3f(size, size, -size);
    glVertex3f(size, -size, -size);
    glEnd();

    // Cara izquierda
    glBegin(GL_QUADS);
    glVertex3f(-size, -size, size);
    glVertex3f(-size, size, size);
    glVertex3f(-size, size, -size);
    glVertex3f(-size, -size, -size);
    glEnd();

    glPopMatrix();
}

void drawCone(GLdouble radious, GLdouble height, GLboolean axis)
{
    if(axis)
        glRotatef(coneAngle[0], 0.0f, 0.0f, 1.0f);
    
    // Light Pastel Blue
    glColor3f(0.7f, 0.9f, 1.0f);

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -0.01f);
    glutSolidCylinder(radious - 0.1, 0.1, 20, 20);
    glPopMatrix();

    // Slightly Darker Blue
    glColor3f(0.4f, 0.6f, 0.8f);

    glutSolidCone(radious, height, 20, 20); // Draw a solid cone
}

void drawCylinder(GLdouble radious, GLdouble height, GLboolean axis)
{
    // Adjustment for the center of mass
    glTranslatef(0.0f, 0.0f, height / 2);

    if(axis)
        glRotatef(objectAngle, 1.0f, 0.0f, 0.0f);

    glTranslatef(0.0f, 0.0f, - height / 2);

    // Light Pastel Orange
    glColor3f(1.0f, 0.7f, 0.2f); // Adjust the RGB values to get a pastel orange

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -0.01f);
    glutSolidCylinder(radious, 0.1, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, height);
    glutSolidCylinder(radious, 0.1, 20, 20);
    glPopMatrix();

    // Slightly Darker Orange
    glColor3f(0.9f, 0.6f, 0.1f); // Adjust the RGB values to make it slightly darker

    glutSolidCylinder(radious, height, 20, 20);
}


// INTERFACE AND UTILITY FUNCTIONS

void keyboard(unsigned char key, int x, int y) 
{
    switch (key) 
    {
        case 's':
            coneSpin = !coneSpin;
            break;
        case 'r':
            coneSpinReverse = !coneSpinReverse;
            break; 
        case 'p':
            hazPerspectiva = 1;
            break;
        case 'o':
            hazPerspectiva = 0;
            break;            
    }
    glutPostRedisplay();
}

void spin()
{
    if(coneSpin)
    {
        if(coneSpinReverse)
            coneAngle[0] += coneSpinSpeed;
        else
            coneAngle[0] -= coneSpinSpeed;
        coneAngle[1] += coneSpinSpeed * 2;
    }
}

void rotate(int button, int state, int x, int y) {
    int frameX;
    int frameY;
    
    if(glutGetModifiers() == GLUT_ACTIVE_ALT)
    {
        if(state == GLUT_DOWN)  
            frameY = y; 
        if(state == GLUT_UP)  
            objectAngle += y - frameY;
    }
}

void basculate(int x, int y) {
    int angleLimit = 30;
    int angleChange = x - frameX;

    if ((angleChange > 0 && armAngle < angleLimit) || (angleChange < 0 && armAngle > -angleLimit))
        armAngle += (x - frameX) / 2;

    frameX = x;
    frameY = y;
}

void speed_menu(int id){
    switch( id){
    case 0:
        coneSpinSpeed = 1.0f;
        break;
    case 1:
        coneSpinSpeed = 4.0f;
        break;   
    }
}

void color_menu(int id) {
    switch (id) {
    case 0:
        // Light pastel yellow
        cubeColors[0] = 0.949f;
        cubeColors[1] = 0.937f;
        cubeColors[2] = 0.694f;
        // Darker yellow
        cubeColors[3] = 0.886f;
        cubeColors[4] = 0.874f;
        cubeColors[5] = 0.549f;
        break;
    case 1:
        // Light pastel red
        cubeColors[0] = 0.949f;
        cubeColors[1] = 0.788f;
        cubeColors[2] = 0.788f;
        // Darker red
        cubeColors[3] = 0.749f;
        cubeColors[4] = 0.396f;
        cubeColors[5] = 0.396f;
        break;
    case 2:
        // Light pastel blue
        cubeColors[0] = 0.690f;
        cubeColors[1] = 0.878f;
        cubeColors[2] = 0.902f;
        // Darker blue
        cubeColors[3] = 0.529f;
        cubeColors[4] = 0.725f;
        cubeColors[5] = 0.752f;
        break;
    case 3:
        // Light pastel green
        cubeColors[0] = 0.678f;
        cubeColors[1] = 0.847f;
        cubeColors[2] = 0.706f;
        // Darker green
        cubeColors[3] = 0.549f;
        cubeColors[4] = 0.729f;
        cubeColors[5] = 0.529f;
        break;
    }
}

void main_menu(int id){
    switch( id){
    case 0:
        exit(-1);
        break;
    }
}

void menu()
{
    int submenu = glutCreateMenu(color_menu);
    glutAddMenuEntry("Amarillo", 0);
    glutAddMenuEntry("Rojo", 1);
    glutAddMenuEntry("Azul", 2);
    glutAddMenuEntry("Verde", 3);

    int submenu2 = glutCreateMenu(speed_menu);
    glutAddMenuEntry("Normal", 0);
    glutAddMenuEntry("Rapido", 1);

    glutCreateMenu(main_menu);
    glutAddSubMenu("Colores", submenu);
    glutAddSubMenu("Velocidad", submenu2);
    glutAddMenuEntry("Salir", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


// PREDEFINED FUNCTIONS

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    if(hazPerspectiva)
        // Set up perspective projection
        gluPerspective(60.0f, (GLfloat)width/(GLfloat)height, 1.0f, 20.0f);
    else       
        // Set up orthographic projection
        glOrtho(-12, 12, -12, 12, -20, 30);

    glMatrixMode(GL_MODELVIEW);
 
    ancho = width;
    alto = height;
}

void display()
{ 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    spin();

    float cone_height = 3.0f;

    glRotatef(90.0, 1.0f, 0.0f, 0.0f); // angle correction
    drawCylinder(4.0, 1.5, GL_TRUE);

    glRotatef(180.0f, 1.0f, 0.0f, 0.0f); // angle correction
    drawCone(3.5, cone_height, GL_TRUE);

    float cube_size = 1.0f;
    float cube_length = 6.0f;

    glRotatef(90.0, 1.0f, 0.0f, 0.0f);
    glTranslatef(0.0, cone_height, 0.0f);
    glRotatef(-90.0, 0.0f, 0.0f, 1.0f);
    
    drawArm(cube_size, cube_length, GL_TRUE);

    float small_cone_height = 2.0f;

    glTranslatef(0.0, cube_length * cube_size, 0.0f);
    glRotatef(-armAngle, 0.0f, 0.0f, 1.0f); // balance correction
    glTranslatef(- small_cone_height, 0.0f, 0.0f);
    glRotatef(90.0, 0.0f, 0.0f, 1.0f);
    glRotatef(90.0, 1.0f, 0.0f, 0.0f); // angle correction

    drawInverseCone(2.5f, small_cone_height, GL_TRUE);

    drawFourCubes(1.0f, 1.0f);

    glFlush();
    glutSwapBuffers();
}

void init()
{
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    ancho = 400;
    alto = 400;
}

void idle()
{
    display();
}

// Main function
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(ancho, alto);
    glutCreateWindow("Cylinder example");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    glutMouseFunc(rotate);
    glutPassiveMotionFunc(basculate); //TODO: Arreglar el error.
    glutKeyboardFunc(keyboard);
    menu(); //TODO: Arreglar el error.

    glutMainLoop();

    return 0;
}