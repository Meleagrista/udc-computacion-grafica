#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/freeglut.h>

GLint ancho = 400;
GLint alto = 400;

int frameX;
int frameY;

GLfloat objectAngleY = 0.0f;
GLfloat objectAngleX = 0.0f;

GLfloat armAngle = 0.0f;
GLboolean armSpin = GL_TRUE;
GLboolean armSpinReverse = GL_FALSE;
GLfloat armSpinSpeed = 1.0f;

GLfloat cubeColors[] = {0.949f, 0.937f, 0.694f, 0.886f, 0.874f, 0.549f};

int hazPerspectiva = 0;

// CUSTOM FUNCTIONS

void drawFourCubes(GLdouble base, GLdouble space)
{
    glTranslatef(0.0f, 0.0f, -base / 2);

    GLfloat size = base / 2.0;

    for (int i = 0; i < 4; i++)
    {
        glPushMatrix();

        switch (i)
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

        glColor3f(cubeColors[3], cubeColors[4], cubeColors[5]); // Colores para cara superior

        glBegin(GL_QUADS);
        glVertex3f(-size, -size, size);
        glVertex3f(size, -size, size);
        glVertex3f(size, size, size);
        glVertex3f(-size, size, size);
        glEnd();

        glBegin(GL_QUADS);
        glVertex3f(-size, -size, -size);
        glVertex3f(size, -size, -size);
        glVertex3f(size, size, -size);
        glVertex3f(-size, size, -size);
        glEnd();

        glColor3f(cubeColors[0], cubeColors[1], cubeColors[2]); // Colores para caras laterales

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

        //glColor3f(cubeColors[3], cubeColors[4], cubeColors[5]);

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

void drawSquareBase(GLdouble base, GLdouble height)
{
    GLfloat size = base / 2.0;

    glPushMatrix();

    glScalef(1.0f, height, 1.0f);

    glColor3f(0.6f, 0.6f, 0.6f); // Color para caras laterales

    glBegin(GL_QUADS);
    glVertex3f(-size, -size, size);
    glVertex3f(size, -size, size);
    glVertex3f(size, size, size);
    glVertex3f(-size, size, size);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-size, -size, -size);
    glVertex3f(size, -size, -size);
    glVertex3f(size, size, -size);
    glVertex3f(-size, size, -size);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(size, -size, size);
    glVertex3f(size, size, size);
    glVertex3f(size, size, -size);
    glVertex3f(size, -size, -size);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-size, -size, size);
    glVertex3f(-size, size, size);
    glVertex3f(-size, size, -size);
    glVertex3f(-size, -size, -size);
    glEnd();

    glColor3f(0.8f, 0.8f, 0.8f); // Color para caras superior e inferior

    glBegin(GL_QUADS);
    glVertex3f(-size, size, size);
    glVertex3f(size, size, size);
    glVertex3f(size, size, -size);
    glVertex3f(-size, size, -size);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-size, -size, size);
    glVertex3f(size, -size, size);
    glVertex3f(size, -size, -size);
    glVertex3f(-size, -size, -size);
    glEnd();

    glPopMatrix();
}

void drawArm(GLdouble base, GLdouble length, GLboolean axis)
{
    if (axis)
        glRotatef(armAngle, 0.0f, 0.0f, 1.0f);

    GLfloat size = base / 2.0;

    glPushMatrix();

    glTranslatef(0.0f, (length * base) / 2, 0.0f);
    glScalef(1.0f, length, 1.0f);

    // Naranja claro
    glColor3f(1.0f, 0.7f, 0.2f);

    glBegin(GL_QUADS);
    glVertex3f(-size, -size, size);
    glVertex3f(size, -size, size);
    glVertex3f(size, size, size);
    glVertex3f(-size, size, size);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-size, -size, -size);
    glVertex3f(size, -size, -size);
    glVertex3f(size, size, -size);
    glVertex3f(-size, size, -size);
    glEnd();

    // Naranja oscuro
    glColor3f(0.9f, 0.6f, 0.1f);

    glBegin(GL_QUADS);
    glVertex3f(-size, size, size);
    glVertex3f(size, size, size);
    glVertex3f(size, size, -size);
    glVertex3f(-size, size, -size);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-size, -size, size);
    glVertex3f(size, -size, size);
    glVertex3f(size, -size, -size);
    glVertex3f(-size, -size, -size);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(size, -size, size);
    glVertex3f(size, size, size);
    glVertex3f(size, size, -size);
    glVertex3f(size, -size, -size);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-size, -size, size);
    glVertex3f(-size, size, size);
    glVertex3f(-size, size, -size);
    glVertex3f(-size, -size, -size);
    glEnd();

    glPopMatrix();
}

void drawFlatCone(GLdouble length, GLdouble size, GLdouble height)
{   
    glPushMatrix();

    glTranslatef(0.0f, 0.0f, - length / 2);

    glColor3f(0.7f, 0.9f, 1.0f); // Azul claro

    glBegin(GL_TRIANGLES);
    glVertex3f(0, height, 0);
    glVertex3f(size, 0, 0);
    glVertex3f(-size, 0, 0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex3f(0, height, length);
    glVertex3f(size, 0, length);
    glVertex3f(-size, 0, length);
    glEnd();

    glColor3f(0.5f, 0.7f, 0.9f); // Azul oscuro

    // Cara inferior
    glBegin(GL_QUADS);
    glVertex3f(size, 0, 0);
    glVertex3f(-size, 0, 0);
    glVertex3f(-size, 0, length);
    glVertex3f(size, 0, length);
    glEnd();

    // Cara laterales
    glBegin(GL_QUADS);
    glVertex3f(0, height, 0);
    glVertex3f(0, height, length);
    glVertex3f(size, 0, length);
    glVertex3f(size, 0, 0);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0, height, 0);
    glVertex3f(0, height, length);
    glVertex3f(-size, 0, length);
    glVertex3f(-size, 0, 0);
    glEnd();

    glPopMatrix();
}

void drawCylinder(GLdouble radious, GLdouble height, GLboolean axis)
{
    // Ajuste para que el giro sea natural
    glTranslatef(0.0f, 0.0f, height / 2); // movimiento del render para ajustar su centro de masa.

    if (axis)
        glRotatef(objectAngleY, 0.0f, 0.0f, 1.0f);
        glRotatef(objectAngleX, 1.0f, 0.0f, 0.0f);

    glTranslatef(0.0f, 0.0f, -height / 2); // reestablecimiento del estado original.

    /* EXPLICACIÓN
     * Aquí no puedo usar un PushMatrix() y PopMatrix() porque necesito que el nuevo angulo se mantenga.
     * El cilcindro se creado sobre el centro de su cara, no sobre el centro de masa.
     * Para corregirlo muevo el punto desde el que se renderiza, aplico la rotación y luego desago el movimiento.
     */

    glColor3f(0.8f, 0.8f, 0.8f); // Gris claro para las caras del cilindro

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -0.01f);
    glutSolidCylinder(radious, 0.1, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, height);
    glutSolidCylinder(radious, 0.1, 20, 20);
    glPopMatrix();

    glColor3f(0.6f, 0.6f, 0.6f); // Gris oscuro para el cuerpo del cilindro

    glutSolidCylinder(radious, height, 20, 20);
}

// INTERFACE FUNCTIONS

void keyboardFunc(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 's':
        armSpin = !armSpin;
        break;
    case 'r':
        armSpinReverse = !armSpinReverse;
        break;
    case 'p':
        hazPerspectiva = 1;
        break;
    case 'o':
        hazPerspectiva = 0;
        break;
    case 'w':
        objectAngleY += 1;
        break;    
    }
    glutPostRedisplay();
}

void armSpinFunc()
{
    int gravity = 2;

    if (armSpinReverse)
        gravity = 1;

    if (armSpin)
    {
        if((int) armAngle % 90 == 0 && abs(armAngle) >= 360)
            armAngle = 0;

        if(abs(armAngle) > 270 || abs(armAngle) < 90)
        {   
            gravity = 1; 
            if (armSpinReverse)
                gravity = 2;
        }
       
        if (armSpinReverse)
            armAngle = armAngle + (armSpinSpeed / gravity);
        else
            armAngle = armAngle - (armSpinSpeed / gravity);
        //printf("%f\n", armAngle);    
    }
}

void mouseRotateFunc(int button, int state, int x, int y)
{
    if (glutGetModifiers() == GLUT_ACTIVE_CTRL)
    {
        if (state == GLUT_DOWN)
            frameX = x;
        if (state == GLUT_UP)
            objectAngleY = objectAngleY + (x - frameX) / 10;
    }
    else
    {
        if (state == GLUT_DOWN)
            frameY = y;
        if (state == GLUT_UP)
            objectAngleX = objectAngleX + (y - frameY) / 10;
    }

    frameY = y;
    frameX = x;        
}

// MENU FUNCTIONS

void speed_menu(int id)
{
    switch (id)
    {
    case 0:
        armSpinSpeed = 1.0f;
        break;
    case 1:
        armSpinSpeed = 4.0f;
        break;
    }
}

void color_menu(int id)
{
    switch (id)
    {
    case 0: // Amarillo
        cubeColors[0] = 0.949f;
        cubeColors[1] = 0.937f;
        cubeColors[2] = 0.694f;
        cubeColors[3] = 0.886f;
        cubeColors[4] = 0.874f;
        cubeColors[5] = 0.549f;
        break;
    case 1: // Rojo
        cubeColors[0] = 0.949f;
        cubeColors[1] = 0.788f;
        cubeColors[2] = 0.788f;
        cubeColors[3] = 0.749f;
        cubeColors[4] = 0.396f;
        cubeColors[5] = 0.396f;
        break;
    case 2: // Azul
        cubeColors[0] = 0.6f;
        cubeColors[1] = 0.8f;
        cubeColors[2] = 1.0f;
        cubeColors[3] = 0.5f;
        cubeColors[4] = 0.7f;
        cubeColors[5] = 0.9f;
        break;
    case 3: // Verde
        cubeColors[0] = 0.678f;
        cubeColors[1] = 0.847f;
        cubeColors[2] = 0.706f;
        cubeColors[3] = 0.549f;
        cubeColors[4] = 0.729f;
        cubeColors[5] = 0.529f;
        break;
    }
}

void main_menu(int id)
{
    switch (id)
    {
    case 0:
        exit(-1);
        break;
    }
}

void menuFunc()
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

    if (hazPerspectiva)
        // Set up perspective projection
        gluPerspective(60.0f, (GLfloat)width / (GLfloat)height, 1.0f, 20.0f);
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

    // AJUSTES ANTES DE RENDERIZAR

    armSpinFunc(); // giro automático del brazo.
    glTranslatef(0.0f, -5.0f, 0.0f); // bajamos todo el render para que no sobresalga la noria.

    // RENDERIZADO DEL CILINDRO

    glRotatef(90.0, 1.0f, 0.0f, 0.0f); // corregimos la posición del render.
    drawCylinder(4.0, 1.5, GL_TRUE);

    // RENDERIZADO DEL CONO

    GLfloat cone_length = 1.0f;
    GLfloat cone_height = 7.5f;

    glRotatef(-90.0, 1.0f, 0.0f, 0.0f); // corregimos la posición del render.
    drawFlatCone(cone_length, 3.5, cone_height);

    // RENDERIZADO DEL BRAZO

    GLfloat cube_size = 1.0f;
    GLfloat cube_length = 6.0f;

    glTranslatef(0.0f, cone_height, (cone_length + cube_size) / 2); // corregimos la posición del render.
    glRotatef(-90.0, 0.0f, 0.0f, 1.0f); // en este caso porque escala sobre el eje vertical.

    drawArm(cube_size, cube_length, GL_TRUE);

    // RENDERIZADO DE LA PLATAFORMA

    GLfloat platform_size = 3.0f;
    GLfloat platform_height = 0.5f;

    glRotatef(90.0, 0.0f, 0.0f, 1.0f); // corregimos la posición del render.
    glTranslatef(cube_length * cube_size, 0.0, (platform_size + cube_size) / 2);
    glRotatef(-armAngle, 0.0f, 0.0f, 1.0f); // compensamos por la rotación del brazo.

    drawSquareBase(platform_size, platform_height);

    // RENDERIZADO DE LOS CUBOS

    GLfloat cubes_shape = 0.9f;

    glRotatef(90.0, 1.0f, 0.0f, 0.0f); // corregimos la posición del render.
    glTranslatef(0.0, 0.0, - (platform_size * platform_height) / 2);

    drawFourCubes(cubes_shape, cubes_shape - 0.1f);

    // FINALIZAMOS EL RENDERIZADO

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

    glutMouseFunc(mouseRotateFunc);
    glutKeyboardFunc(keyboardFunc);
    menuFunc();

    glutMainLoop();

    return 0;
}