//gcc p1a.c -o out -lGL -lGLU -lglut
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#define _USE_MATH_DEFINES
#ifndef M_PI
#    define M_PI 3.14159265358979323846
#endif
#define WIDTH 500
#define HEIGTH 500
#define ORIGIN_X 50
#define ORIGIN_Y 50

void init()
{
    glClearColor(0,0,0,0);/*Fijar el color por defecto a negro en el formato (RGBA)*/
}

void whiteTriangle()
{
    /* Triangulo Blanco */
    glColor3f( 1.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLES);
        glVertex3f(-1.0f, 0.0f, 0.0f); //V1
        glVertex3f(1.0f, 0.0f, 0.0f); //V2
        glVertex3f(0.0f, 1.0f, 0.0f); //V3
    glEnd();
}

void blueTriangle()
{
    /* Triángulo Azul */
    glShadeModel(GL_FLAT);
    glBegin(GL_TRIANGLES);
        glColor3f( 1.0f, 0.0f, 0.0f);
        glVertex3f(-1.0f, 0.0f, 0.0f); //V1
        glColor3f( 0.0f, 1.0f, 0.0f);
        glVertex3f(1.0f, 0.0f, 0.0f); //V2
        glColor3f( 0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 1.0f, 0.0f); //V3
    glEnd();
}

void colorTriangle()
{
    /* Triángulo Colores */
    glShadeModel(GL_SMOOTH);
    glBegin(GL_TRIANGLES);
        glColor3f( 1.0f, 0.0f, 0.0f);
        glVertex3f(-1.0f, 0.0f, -1.0f); //V1
        glColor3f( 0.0f, 1.0f, 0.0f);
        glVertex3f(1.0f, 0.0f, -1.0f); //V2
        glColor3f( 0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 1.0f, -1.0f); //V3
    glEnd();
}

void circleWithLines()
{
    /*Círculo con lineas*/
    int i;
    float radius = 1.0f;
    float ang = 0.0f;

    glColor3f( 1.0f, 1.0f, 1.0f);
    for (i = 0; i <360; i = i+3){
        ang = i * M_PI / 180.0f;
    glBegin(GL_LINES);
        glVertex3f(0.0, 0.0, -1.0);
        glVertex3f(cos(ang)*radius, sin(ang)*radius, 0.0); 
    //Hace falta #include <math.h> para usar las funciones de seno y coseno
    //En algunas plataformas hay que añadir previamente #define _USE_MATH_DEFINES
    glEnd();
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT); /*Borrado del FrameBuffer*/ 
    //glMatrixMode(GL_MODELVIEW); /* Activar las modificaciones en los objetos del mundo*/
    //glLoadIdentity();/* Cargar la identidad en la matrix de modeficaciones del mundo*/

    /* Lo que haya que pintar ira aquí*/
    circleWithLines();

    glFlush(); /*Forzar el renderizado*/
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);/*Activar las modificaciones en la camara*/
    glLoadIdentity(); /*Cargar la identidad en la matrix de proyección*/
    glOrtho(-2, 2, -2, 2, -1, 1);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv); /*Cargar el teclado y el ráton*/
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); /*inicializar el Frame Buffer*/
    glutInitWindowSize(WIDTH, HEIGTH); /*Tamaño de la ventana*/ 
    glutInitWindowPosition(ORIGIN_X, ORIGIN_Y); /*Posición del extremo superior-izquierdo de la ventana*/
    glutCreateWindow("Hola Mundo"); /* Crear la ventana*/
    init();
    glutDisplayFunc(display); /*Activar la funcion de pintado*/
    glutReshapeFunc(reshape); /*Activar la funcion de escalado*/
    glutMainLoop(); /*Arrancar el bucle de OpenGL*/
    return 0;
}