/*
 * GL02Primitive.cpp: Vertex, Primitive and Color
 * Draw Simple 2D colored Shapes: quad, triangle and polygon.
 */
#include <GL/glut.h> // GLUT, include glu.h and gl.h
#include <math.h>

/* Initialize OpenGL Graphics */
void initGL()
{
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
}

/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */
void display()
{
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer with current clearing color

    // Define shapes enclosed within a pair of glBegin and glEnd

    glBegin(GL_QUADS);
    glColor3f(0, 1, 1);
    glVertex2f(-1.0f, 1.0f);
    glVertex2f(-1.0f, 0.4f);
    glVertex2f(1.0f, 0.4f);
    glVertex2f(1.0f, 1.0f);

    glColor3f(0, 1, 0);
    glVertex2f(-1.0f, 0.4f);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, 0.4f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 1);
    glVertex2f(-1.0f, 0.4f);
    glVertex2f(-0.5f, 0.4f);
    glVertex2f(-0.75f, 0.7f);

    glVertex2f(-0.5f, 0.4f);
    glVertex2f(0.0f, 0.4f);
    glVertex2f(-0.25f, 0.7f);

    glVertex2f(0.0f, 0.4f);
    glVertex2f(0.5f, 0.4f);
    glVertex2f(0.25f, 0.7f);

    glVertex2f(0.5f, 0.4f);
    glVertex2f(1.0f, 0.4f);
    glVertex2f(0.75f, 0.7f);
    glEnd();

    float i = 0.0f;
    float PI=3.14287;
    float r = 0.1;
    float x = -0.5f;
    float y = 0.8f;
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1, 0.64, 0);
    glVertex2f(x, y); // Center
    for(i = 0.0f; i <= 360; i+=0.001)
            glVertex2f(r*cos(PI * i / 180.0) + x, r*sin(PI * i / 180.0) + y);
    glEnd();

    glBegin(GL_QUADS);

    glColor3f(1, 0, 0);
    glVertex2f(-0.3f, -0.3f);
    glVertex2f(0.3f, -0.3f);
    glVertex2f(0.3f, 0.3f);
    glVertex2f(-0.3f, 0.3f);

    glColor3f(1, 1, 0);
    glVertex2f(-0.1f, -0.3f);
    glVertex2f(0.1f, -0.3f);
    glVertex2f(0.1f, 0.0f);
    glVertex2f(-0.1f, 0.0f);

    glVertex2f(-0.25f, 0.2f);
    glVertex2f(-0.25f, 0.1f);
    glVertex2f(-0.15f, 0.1f);
    glVertex2f(-0.15f, 0.2f);

    glVertex2f(0.25f, 0.2f);
    glVertex2f(0.25f, 0.1f);
    glVertex2f(0.15f, 0.1f);
    glVertex2f(0.15f, 0.2f);

    glColor3f(1, 0, 1);
    glVertex2f(-0.2f, -0.3f);
    glVertex2f(-0.2f, -0.35f);
    glVertex2f(0.2f, -0.35f);
    glVertex2f(0.2f, -0.3f);

    glVertex2f(-0.15f, -0.35f);
    glVertex2f(-0.15f, -0.4f);
    glVertex2f(0.15f, -0.4f);
    glVertex2f(0.15f, -0.35f);

    glVertex2f(-0.1f, -0.4f);
    glVertex2f(-0.1f, -0.45f);
    glVertex2f(0.1f, -0.45f);
    glVertex2f(0.1f, -0.4f);

    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0, 0, 1);
    glVertex2f(-0.3f, 0.3f);
    glVertex2f(0.3f, 0.3f);
    glVertex2f(0.0f, 0.6f);
    glEnd();

    glFlush(); // Render now
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char **argv)
{
    glutInit(&argc, argv);                         // Initialize GLUT
    glutInitWindowSize(700, 700);                  // Set the window's initial width & height
    glutInitWindowPosition(50, 50);                // Position the window's initial top-left corner
    glutCreateWindow("Vertex, Primitive & Color"); // Create window with the given title
    glutDisplayFunc(display);                      // Register callback handler for window re-paint event
    initGL();                                      // Our own OpenGL initialization
    glutMainLoop();                                // Enter the event-processing loop
    return 0;
}