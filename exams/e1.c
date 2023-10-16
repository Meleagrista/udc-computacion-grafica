#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/freeglut.h>

// Global variables to store the window dimensions
GLint ancho = 400;
GLint alto = 400;

float angleX = 0.0f;
float angleY = 0.0f;
float angleZ = 0.0f;

// Variable to control whether to use perspective projection
int hazPerspectiva = 0;

// CUSTOM FUNCTIONS

void drawCone(GLdouble radious, GLdouble height)
{
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -5.0f); // Translate to position the cone

    glutSolidCone(1.0, 3.0, 20, 20); // Draw a solid cone

    glPopMatrix();
}

void drawCylinder(GLdouble radious, GLdouble height)
{
    //glMatrixMode(GL_MODELVIEW);

    glTranslatef(0.0f, 0.0f, 0.0f);
    glRotatef(90.0, 1.0f, 0.0f, 0.0f);

    // Save the current matrix (for restoring the original position after rotation)
    glPushMatrix();

    // Translate to the center of the cylinder
    glTranslatef(0.0f, 0.0f, height / 2); // Assuming the cylinder's height is 4.0 units

    // Apply rotation transformation (e.g., 45 degrees around the y-axis)
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);
    glRotatef(angleZ, 0.0f, 0.0f, 1.0f);

    // Translate to the corresponding position of the cylinder
    glTranslatef(0.0f, 0.0f, - height / 2); // Assuming the cylinder's height is 4.0 units

    
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

    // Restore the original position
    glPopMatrix();
}

void keyboard(unsigned char key, int x, int y) 
{
    switch (key) 
    {
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
    }
    glutPostRedisplay();
}

// PREDEFINED FUNCTIONS

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
        glOrtho(-12, 12, -12, 12, -20, 30);

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

    drawCylinder(4.0, 2.0);

    glFlush();
    glutSwapBuffers();
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
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(ancho, alto);
    glutCreateWindow("Cylinder example");

    init();

    // Register callback functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    glutKeyboardFunc(keyboard);

    // Start the main loop
    glutMainLoop();

    return 0;
}