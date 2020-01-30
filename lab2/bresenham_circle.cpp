#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

int X1 = 10, Y1 = -50, R = 100;

void initGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glOrtho(-200, 200, -200, 200, -1, 1);
}

void draw_symmetry(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glVertex2i(-x, y);
    glVertex2i(x, -y);
    glVertex2i(-x, -y);
    glVertex2i(y, x);
    glVertex2i(-y, x);
    glVertex2i(y, -x);
    glVertex2i(-y, -x);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glTranslatef(X1, Y1, 0);
    int x = 0, y = R;
    int d = 3 - 2 * R;
    while(y >= x) {
        draw_symmetry(x, y);
        x++;
        if(d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else {
            d = d + 4 * x + 6;
        }
    }
    glTranslatef(-X1, -Y1, 0);
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);                         
    glutInitWindowSize(400, 400);                  
    glutInitWindowPosition(0, 0);                
    glutCreateWindow("Bresenham Circle"); 
    glutDisplayFunc(display);                      
    initGL();                                      
    glutMainLoop();                               
    return 0;
}