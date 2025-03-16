#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

// Global variables to store the window dimensions
GLint ancho = 400;
GLint alto = 400;

// Variable to control whether to use perspective projection
int hazPerspectiva = 0;

// Function to handle window resizing
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
        glOrtho(-6, 6, -6, 6, -10, 15);

    glMatrixMode(GL_MODELVIEW);
 
    // Update the global window dimensions
    ancho = width;
    alto = height;
}

// Function to render the scene
void display()
{ 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    // Place your rendering code here
}

// Function to initialize OpenGL settings
void init()
{
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    ancho = 400;
    alto = 400;
}

// Function to continuously update the display
void idle()
{
    display();
}

// Main function
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(ancho, alto);
    glutCreateWindow("Brazo robotico");

    init();

    // Register callback functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    // Start the main loop
    glutMainLoop();

    return 0;
}