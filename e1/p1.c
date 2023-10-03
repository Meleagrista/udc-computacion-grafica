#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

GLint ancho=400;
GLint alto=400;

float angleX = 0.0f; // Ángulo de rotación en el eje X
float angleY = 0.0f; // Ángulo de rotación en el eje Y
float angleZ = 0.0f; // Ángulo de rotación en el eje Z

float angleX2 = 0.0f; // Ángulo de rotación en el eje X
float angleY2 = 0.0f; // Ángulo de rotación en el eje Y
float angleZ2 = 0.0f; // Ángulo de rotación en el eje Z

int hazPerspectiva = 0;

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    if(hazPerspectiva)
        gluPerspective(60.0f, (GLfloat)width/(GLfloat)height, 1.0f, 20.0f);
    else       
        glOrtho(-4,4, -4, 4, 1, 10);

    glMatrixMode(GL_MODELVIEW);
 
    ancho = width;
    alto = height;
}

void drawSphere() {
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    
    glTranslatef(0.0f, -1.0f, -3.0f); // Transladar la escena hacia afuera de la pantalla
    glRotatef(angleX, 1.0f, 0.0f, 0.0f); // Rotación en el eje X
    glRotatef(angleY, 0.0f, 1.0f, 0.0f); // Rotación en el eje Y
    glRotatef(angleZ, 0.0f, 0.0f, 1.0f); // Rotación en el eje Z
    
    glColor3f(1.0f, 0.0f, 0.0f); // Color rojo
    glutSolidSphere(0.5, 30, 30); // Dibuja una esfera de radio 0.5
    
    //glutSwapBuffers();
}

void drawSphereToRight() {
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    
    glTranslatef(1.0f, 0.0f, 0.0f); // Transladar el cubo a la derecha
    
    glColor3f(1.0f, 0.0f, 0.0f); // Color rojo
    glutSolidSphere(0.5, 30, 30); // Dibuja una esfera de radio 0.5
    
    //glutSwapBuffers();
}

void drawCubeToRight(GLboolean secondSquare)
{
    glMatrixMode(GL_MODELVIEW);
    
    if(secondSquare)
    {
        glRotatef(angleX2, 1.0f, 0.0f, 0.0f); // Rotación en el eje X
        glRotatef(angleY2, 0.0f, 1.0f, 0.0f); // Rotación en el eje Y
        glRotatef(angleZ2, 0.0f, 0.0f, 1.0f); // Rotación en el eje Z
    }
    

    glTranslatef(1.0f, 0.0f, 0.0f); // Transladar el cubo a la derecha

    glColor3f(0.0f, 0.0f, 1.0f); // Color rojo (default color)

    // Front face (positive Z face)
    glBegin(GL_QUADS);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glEnd();

    // Back face (negative Z face)
    glBegin(GL_QUADS);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glEnd();

    // Top face (positive Y face)
    glBegin(GL_QUADS);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glEnd();

    // Bottom face (negative Y face)
    glBegin(GL_QUADS);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glEnd();

    glColor3f(0.0f, 1.0f, 0.0f); // Green color for the right face

    // Right face (positive X face)
    glBegin(GL_QUADS);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glEnd();

    glColor3f(0.0f, 1.0f, 0.0f); // Green color for the left face

    // Left face (negative X face) - Set this to green
    glBegin(GL_QUADS);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glEnd();

    //glutSwapBuffers();
}

void display()
{ 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    drawSphere();
    drawCubeToRight(GL_FALSE);
    drawSphereToRight();
    drawCubeToRight(GL_TRUE);
 
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
 
/*void specialKeys(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        angleX += 1.0f;
        break;
    case GLUT_KEY_DOWN:
        angleX -= 1.0f;
        break;
    case GLUT_KEY_LEFT:
        angleY += 1.0f;
        break;
    case GLUT_KEY_RIGHT:
        angleY -= 1.0f;
        break;
    }
    glutPostRedisplay();
}*/

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    // TECLAS SEDUNDO CUBO
    case 'q':
        angleX += 1.0f;
        break;
    case 'a':
        angleX -= 1.0f;
        break;
    case 'w':
        angleY += 1.0f;
        break;
    case 's':
        angleY -= 1.0f;
        break;
    case 'e':
        angleZ += 1.0f;
        break;
    case 'd':
        angleZ -= 1.0f;
        break;
    // TECLAS SEDUNDO CUBO
    case 'u':
        angleX2 += 1.0f;
        break;
    case 'j':
        angleX2 -= 1.0f;
        break;
    case 'i':
        angleY2 += 1.0f;
        break;
    case 'k':
        angleY2 -= 1.0f;
        break;
    case 'o':
        angleZ2 += 1.0f;
        break;
    case 'l':
        angleZ2 -= 1.0f;
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
    glutCreateWindow("Pierna");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}