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
    glClearColor(0.0,0.0,0.0,0.0);
}

void display()
{
    //glClear(GL_COLOR_BUFFER_BIT); 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glColor3f(1.0f, 1.0f, 1.0f);
    /* White Triangle */
    glBegin(GL_TRIANGLES);
      glVertex3f(-1.0f ,-1.0f ,0.0f ); //V1
      glVertex3f(1.0f ,-1.0f , 0.0f ); //V2
      glVertex3f(0.0f ,1.0f , 0.0f ); //V3
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f);
    glPointSize(5.0f); // Increse the point size to see the points easier
    /* Red Dots */
    glBegin(GL_POINTS);
      glVertex3f(0.0f, 0.0f, -2.0f); //Point inside the triangle
      glVertex3f(2.0f, 1.0f, -2.0f); //Point outside the triangle
    glEnd();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 4.0, -2.0, 4.0, -2.0, 4.0); 
    glMatrixMode(GL_MODELVIEW);

}

int main(int argc, char** argv)
{
    glutInit(&argc, argv); 
    
    //glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGTH);  
    glutInitWindowPosition(ORIGIN_X, ORIGIN_Y); 
    glutCreateWindow("Hola Mundo"); 
    init();
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display); 
    glutReshapeFunc(reshape); 
    glutMainLoop(); 
    return 0;
}