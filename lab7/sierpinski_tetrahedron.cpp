/*
 * GL02Primitive.cpp: Vertex, Primitive and Color
 * Draw Simple 2D colored Shapes: quad, triangle and polygon.
 */
#include <GL/glut.h> // GLUT, include glu.h and gl.h
#include <math.h>
#include <unistd.h>
#include <stdio.h>

#include "3d_transformations.hpp"

float X = 0, Y = 0, Z = 0;
int length = 128;
int rec = 3;

/* Initialize OpenGL Graphics */
void initGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClearDepth(1.0f);                   // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   glOrtho(-256, 256, -256, 256, -256, 256);
   // glShadeModel(GL_SMOOTH);   // Enable smooth shading
   // glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

void keyPressed (unsigned char key, int x, int y) {  
    if(key == 'a'){
        yangle += 5;
    }
    else if(key == 's') {
        xangle -= 5;
    }
    else if(key == 'd') {
        yangle -= 5;
    }
    else if(key == 'w') {
        xangle += 5;
    }
    glutPostRedisplay();
}  

void draw(double xx1, double yy1, double zz1, double xx2, double yy2, double zz2, double xx3, double yy3, double zz3, int count) {
    if(count == rec) {
        struct point pt;

        glBegin(GL_TRIANGLES);

        pt = transform(xx1, yy1, zz1);
        glVertex3f(pt.x, pt.y, pt.z);
        pt = transform(xx2, yy2, zz2);
        glVertex3f(pt.x, pt.y, pt.z);
        pt = transform(xx3, yy3, zz3);
        glVertex3f(pt.x, pt.y, pt.z);

        glEnd();
    }
    else {
        draw(xx1, yy1, zz1,
            (xx1+xx2)/2, (yy1+yy2)/2, (zz1+zz2)/2,
            (xx1+xx3)/2, (yy1+yy3)/2, (zz1+zz3)/2,
            count+1);
        draw(xx2, yy2, zz2,
            (xx2+xx3)/2, (yy2+yy3)/2, (zz2+zz3)/2,
            (xx2+xx1)/2, (yy2+yy1)/2, (zz2+zz1)/2,
            count+1);
        draw(xx3, yy3, zz3,
            (xx3+xx1)/2, (yy3+yy1)/2, (zz3+zz1)/2,
            (xx3+xx2)/2, (yy3+yy2)/2, (zz3+zz2)/2,
            count+1);
    }
}

void draw() {
    glColor3f(1, 0, 0);
    draw(-length*cos(30*M_PI/180.0f), -length*sin(30*M_PI/180.0f), length*sin(30*M_PI/180.0f),
    length*cos(30*M_PI/180.0f), -length*sin(30*M_PI/180.0f), length*sin(30*M_PI/180.0f),
    0.0, (double)length, 0.0,
    1);

    glColor3f(0,1,0);
    draw(length*cos(30*M_PI/180.0f), -length*sin(30*M_PI/180.0f), length*sin(30*M_PI/180.0f),
    0.0, -length*sin(30*M_PI/180.0f), (double)-length,
    0.0, (double)length, 0.0,
    1);

    glColor3f(0,0,1);
    draw(0.0, -length*sin(30*M_PI/180.0f), (double)-length,
    -length*cos(30*M_PI/180.0f), -length*sin(30*M_PI/180.0f), length*sin(30*M_PI/180.0f),
    0.0, (double)length, 0.0,
    1);

    glColor3f(1,1,1);
    draw(-length*cos(30*M_PI/180.0f), -length*sin(30*M_PI/180.0f), length*sin(30*M_PI/180.0f),
    0.0, -length*sin(30*M_PI/180.0f), (double)-length,
    length*cos(30*M_PI/180.0f), -length*sin(30*M_PI/180.0f), length*sin(30*M_PI/180.0f),
    1);
}

/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color buffer with current clearing color
    draw();
    glFlush(); // Render now
}

void display1() {
    printf("Enter recursion level:\n");
    scanf("%d", &rec);
    glutPostRedisplay();
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char **argv)
{
    glutInit(&argc, argv);                         // Initialize GLUT
    glutInitWindowSize(512, 512);                  // Set the window's initial width & height
    glutInitWindowPosition(50, 50);                // Position the window's initial top-left corner
    glutCreateWindow("Vertex, Primitive & Color"); // Create window with the given title
    glutDisplayFunc(display);                      // Register callback handler for window re-paint event
    glutIdleFunc(display1);
    glutKeyboardFunc(keyPressed);
    initGL();                                      // Our own OpenGL initialization
    glutMainLoop();                                // Enter the event-processing loop
    return 0;
}