/*
 * GL02Primitive.cpp: Vertex, Primitive and Color
 * Draw Simple 2D colored Shapes: quad, triangle and polygon.
 */
#include <GL/glut.h> // GLUT, include glu.h and gl.h
#include <math.h>
#include <unistd.h>

float xangle = 0.0f, yangle = 0.f, zangle = 0.0f;

/* Initialize OpenGL Graphics */
void initGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClearDepth(1.0f);                   // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   // glShadeModel(GL_SMOOTH);   // Enable smooth shading
   // glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

void display1() {
    glutPostRedisplay();
}

void keyPressed (unsigned char key, int x, int y) {  
    if(key == 'a'){
        yangle += 10;
        // glutPostRedisplay();
    }
    else if(key == 's') {
xangle -= 10;
        // glutPostRedisplay();
    }
    else if(key == 'd') {
yangle -= 10;
        // glutPostRedisplay();
    }
    else if(key == 'w') {
xangle += 10;
        // glutPostRedisplay();
    }
    glutPostRedisplay();
}  

/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color buffer with current clearing color
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
    // glTranslatef(0.15f, 0.15f, 0.0f);
    glRotatef(xangle, 1.0f, 0.0f, 0.0f);
    glRotatef(yangle, 0.0f, 1.0f, 0.0f);
    glRotatef(zangle, 0.0f, 0.0f, 1.0f);
    // glTranslatef(-0.15f, -0.15f, 0.0f);
    glBegin(GL_QUADS);

    //front
    glColor3f(0, 0, 1);
    glVertex3f(-0.2f, 0.2f, 0.2f);
    glVertex3f(-0.2f, -0.2f, 0.2f);
    glVertex3f(0.2f, -0.2f, 0.2f);
    glVertex3f(0.2f, 0.2f, 0.2f);
    // glVertex3f(-0.2f, 0.2f, 0.2f);s
    // glVertex3f(0.2f, 0.2f, 0.2f);
    // glVertex3f(0.2f, -0.2f, 0.2f);
    // glVertex3f(-0.2f, -0.2f, 0.2f);

    //right
    glColor3f(0, 1, 0);
    glVertex3f(0.2f, 0.2f, 0.2f);
    glVertex3f(0.2f, -0.2f, 0.2f);
    glVertex3f(0.2f, -0.2f, -0.2f);
    glVertex3f(0.2f, 0.2f, -0.2f);
    
    //back
    glColor3f(0, 0, 1);
    glVertex3f(0.2f, 0.2f, -0.2f);
    glVertex3f(0.2f, -0.2f, -0.2f);
    glVertex3f(-0.2f, -0.2f, -0.2f);
    glVertex3f(-0.2f, 0.2f, -0.2f);
    
    //left
    glColor3f(0, 1, 0);
    glVertex3f(-0.2f, 0.2f, -0.2f);
    glVertex3f(-0.2f, -0.2f, -0.2f);
    glVertex3f(-0.2f, -0.2f, 0.2f);
    glVertex3f(-0.2f, 0.2f, 0.2f);
    
    //top
    glColor3f(1, 0, 0);
    glVertex3f(-0.2f, 0.2f, -0.2f);
    glVertex3f(-0.2f, 0.2f, 0.2f);
    glVertex3f(0.2f, 0.2f, 0.2f);
    glVertex3f(0.2f, 0.2f, -0.2f);

    //down
    glColor3f(1, 0, 0);
    glVertex3f(-0.2f, -0.2f, 0.2f);
    glVertex3f(-0.2f, -0.2f, -0.2f);
    glVertex3f(0.2f, -0.2f, -0.2f);
    glVertex3f(0.2f, -0.2f, 0.2f);

    glEnd();
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
    glutKeyboardFunc(keyPressed);
    initGL();                                      // Our own OpenGL initialization
    glutMainLoop();                                // Enter the event-processing loop
    return 0;
}