#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
 
#define WIDTH 400
#define HEIGTH 400
#define ORIGIN_X 100
#define ORIGIN_Y 100
 
void init()
{
    glClearColor(0.0,0.0,0.0, 0.0);
}

void displayTriangle()
{
/* Triangulo Blanco */
    glColor3f( 1.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLES);
        glVertex3f(-1.0f, 0.0f, 0.0f); //V1
        glVertex3f(1.0f, 0.0f, 0.0f); //V2
        glVertex3f(0.0f, 1.0f, 0.0f); //V3
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
	
    /* Lo que haya que pintar ira aquí*/
    displayTriangle();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, 0.0, 1.0, -1.0, 2.0);
    //gluPerspective(60.0f, (GLfloat)WIDTH/(GLfloat)HEIGTH, 0.0f, 2.0f);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
 glutInitWindowSize(WIDTH, HEIGTH);
 glutInitWindowPosition(ORIGIN_X, ORIGIN_Y);
 glutCreateWindow("Hola Mundo");
 init();
 glutDisplayFunc(display);
 glutReshapeFunc(reshape);
 glutMainLoop();
 return 0;
}