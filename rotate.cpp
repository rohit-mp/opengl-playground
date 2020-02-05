/*
 * GL02Primitive.cpp: Vertex, Primitive and Color
 * Draw Simple 2D colored Shapes: quad, triangle and polygon.
 */
#include <GL/glut.h> // GLUT, include glu.h and gl.h
#include <math.h>
#include <unistd.h>

float angle = 1.0f;

/* Initialize OpenGL Graphics */
void initGL()
{
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
}

void display1() {
    glutPostRedisplay();
}

/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */
void display()
{
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer with current clearing color

    glBegin(GL_QUADS);
    glColor3f(1, 0, 0);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.3f, 0.0f);
    glVertex2f(0.3f, 0.3f);
    glVertex2f(0.0f, 0.3f);
    glEnd();

    glPushMatrix();
    glTranslatef(0.15f, 0.15f, 0.0f);
    glRotatef(angle, 1.0f, 0.0f, 1.0f);
    glTranslatef(-0.15f, -0.15f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0, 0, 1);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.3f, 0.0f);
    glVertex2f(0.3f, 0.3f);
    glVertex2f(0.0f, 0.3f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.15f, 0.15f, 0.0f);
    glRotatef(-angle, 1.0f, 0.0f, 1.0f);
    glTranslatef(-0.15f, -0.15f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0, 1, 0);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.3f, 0.0f);
    glVertex2f(0.3f, 0.3f);
    glVertex2f(0.0f, 0.3f);
    glEnd();
    glPopMatrix();

    angle += 0.01;

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
    glutIdleFunc(display1);
    initGL();                                      // Our own OpenGL initialization
    glutMainLoop();                                // Enter the event-processing loop
    return 0;
}