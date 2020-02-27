/*
 * GL02Primitive.cpp: Vertex, Primitive and Color
 * Draw Simple 2D colored Shapes: quad, triangle and polygon.
 */
#include <GL/glut.h> // GLUT, include glu.h and gl.h
#include <math.h>
#include <unistd.h>
#include <stdio.h>

#include "3d_transformations.hpp"

// float xangle = 0.0f, yangle = 0.f, zangle = 0.0f;
float X = 0, Y = 0, Z = 0;
float depth = 0;

/* Initialize OpenGL Graphics */
void initGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClearDepth(1.0f);                   // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   glOrtho(-200, 200, -200, 200, -400, 400);
   // glShadeModel(GL_SMOOTH);   // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

void display1() {
    glutPostRedisplay();
}

void mousePressed (int button, int state, int x, int y) {
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        tz += 0.1;
    } else if(button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
        tz -= 0.1;
    }
    glutPostRedisplay();
}

void specialKeyPressed(int key, int x, int y) {
    if(key == GLUT_KEY_UP) {
        ty += 0.10;
    } else if(key == GLUT_KEY_DOWN) {
        ty -= 0.10;
    } else if(key == GLUT_KEY_RIGHT) {
        tx += 0.10;
    } else if(key == GLUT_KEY_LEFT) {
        tx -= 0.10;
    }
    glutPostRedisplay();
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
    else if(key == 'q') {
        zangle += 5;
    }
    else if (key == 'e') {  
        zangle -= 5;
    }
    else if(key == 'y'){
        sx += 0.1;
    }
    else if(key == 'u'){
        sy += 0.1;
    }
    else if(key == 'i'){
        sz += 0.1;
    }
    else if(key == 'h'){
        sx -= 0.1;
    }
    else if(key == 'j'){
        sy -= 0.1;
    }
    else if(key == 'k'){
        sz -= 0.1;
    }
    glutPostRedisplay();
}  


/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color buffer with current clearing color
    // glMatrixMode(GL_MODELVIEW);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
    // glTranslatef(0.15f, 0.15f, 0.0f);
    glRotatef(xangle, 1.0f, 0.0f, 0.0f);
    glRotatef(yangle, 0.0f, 1.0f, 0.0f);
    glRotatef(zangle, 0.0f, 0.0f, 1.0f);
    // glTranslatef(-0.15f, -0.15f, 0.0f);
    glTranslatef(0, 0, depth);
    glBegin(GL_QUADS);

    struct point pt;

    //front
    glColor3f(0, 0, 1);

    pt = transform(-0.2f, 0.2f, 0.2f);
    glVertex3f(pt.x, pt.y, pt.z);
    pt = transform(-0.2f, -0.2f, 0.2f);
    glVertex3f(pt.x, pt.y, pt.z);
    pt = transform(0.2f, -0.2f, 0.2f);
    glVertex3f(pt.x, pt.y, pt.z);
    pt = transform(0.2f, 0.2f, 0.2f);
    glVertex3f(pt.x, pt.y, pt.z);

    //right
    glColor3f(0, 1, 0);
    pt = transform(0.2f, 0.2f, 0.2f);
    glVertex3f(pt.x, pt.y, pt.z);
    pt = transform(0.2f, -0.2f, 0.2f);
    glVertex3f(pt.x, pt.y, pt.z);
    pt = transform(0.2f, -0.2f, -0.2f);
    glVertex3f(pt.x, pt.y, pt.z);
    pt = transform(0.2f, 0.2f, -0.2f);
    glVertex3f(pt.x, pt.y, pt.z);
    
    //back
    glColor3f(0, 0, 1);
    pt = transform(0.2f, 0.2f, -0.2f);
    glVertex3f(pt.x, pt.y, pt.z);
    pt = transform(0.2f, -0.2f, -0.2f);
    glVertex3f(pt.x, pt.y, pt.z);
    pt = transform(-0.2f, -0.2f, -0.2f);
    glVertex3f(pt.x, pt.y, pt.z);
    pt = transform(-0.2f, 0.2f, -0.2f);
    glVertex3f(pt.x, pt.y, pt.z);

    //left
    glColor3f(0, 1, 0);
    pt = transform(-0.2f, 0.2f, -0.2f);
    glVertex3f(pt.x, pt.y, pt.z);
    pt = transform(-0.2f, -0.2f, -0.2f);
    glVertex3f(pt.x, pt.y, pt.z);
    pt = transform(-0.2f, -0.2f, 0.2f);
    glVertex3f(pt.x, pt.y, pt.z);
    pt = transform(-0.2f, 0.2f, 0.2f);
    glVertex3f(pt.x, pt.y, pt.z);

    // top
    glColor3f(1, 0, 0);
    pt = transform(-0.2f, 0.2f, -0.2f);
    glVertex3f(pt.x, pt.y, pt.z);
    pt = transform(-0.2f, 0.2f, 0.2f);
    glVertex3f(pt.x, pt.y, pt.z);
    pt = transform(0.2f, 0.2f, 0.2f);
    glVertex3f(pt.x, pt.y, pt.z);
    pt = transform(0.2f, 0.2f, -0.2f);
    glVertex3f(pt.x, pt.y, pt.z);

    //down
    glColor3f(1, 0, 0);
    pt = transform(-0.2f, -0.2f, 0.2f);
    glVertex3f(pt.x, pt.y, pt.z);
    pt = transform(-0.2f, -0.2f, -0.2f);
    glVertex3f(pt.x, pt.y, pt.z);
    pt = transform(0.2f, -0.2f, -0.2f);
    glVertex3f(pt.x, pt.y, pt.z);
    pt = transform(0.2f, -0.2f, 0.2f);
    glVertex3f(pt.x, pt.y, pt.z);

    glEnd();
    // glTranslatef(0, 0, -depth);
    glutSwapBuffers();
    glPopMatrix();

    // angle += 10;

    glFlush(); // Render now
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char **argv)
{
    glutInit(&argc, argv);                         // Initialize GLUT
    glutInitWindowSize(400, 400);                  // Set the window's initial width & height
    glutInitWindowPosition(50, 50);                // Position the window's initial top-left corner
    glutCreateWindow("Vertex, Primitive & Color"); // Create window with the given title
    glutDisplayFunc(display);                      // Register callback handler for window re-paint event
    // glutIdleFunc(display1);
    glutMouseFunc(mousePressed);
    glutKeyboardFunc(keyPressed);
    glutSpecialFunc(specialKeyPressed);
    initGL();                                      // Our own OpenGL initialization
    glutMainLoop();                                // Enter the event-processing loop
    return 0;
}