#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

#define ROOT2 sqrt(2)

float scale_x = 1, scale_y = 1;

void initGL()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
    gluOrtho2D(-250, 250, -250, 250);
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

void bresenham_circle(int R) {
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
}

void bresenham_line(int X1, int Y1, int X2, int Y2) {
    glBegin(GL_POINTS);
    if(abs(X1-X2) > abs(Y1-Y2)){
        if(X1 > X2){
            int tmp = X1;
            X1 = X2;
            X2 = tmp;
            tmp = Y1;
            Y1 = Y2;
            Y2 = tmp;
        }
        int fraction = 0;
        int fraction_increment = 2 * ((Y1 <= Y2) ? (Y2 - Y1) : (Y1 - Y2));
        int x, y;
        for(x = X1, y = Y1; x <= X2; x++) {
            glVertex2i(x, y);
            fraction += fraction_increment;
            if(fraction >= 1) {
                y += (Y1 <= Y2 ? 1 : -1);
                fraction -= 2 * (X1 <= X2 ? (X2 - X1) : (X1 - X2));
            }
        }
    }
    else{
        if(Y1 > Y2){
            int tmp = X1;
            X1 = X2;
            X2 = tmp;
            tmp = Y1;
            Y1 = Y2;
            Y2 = tmp;
        }
        int fraction = 0;
        int fraction_increment = 2 * ((X1 <= X2) ? (X2 - X1) : (X1 - X2));
        int x, y;
        for(y = Y1, x = X1; y <= Y2; y++) {
            glVertex2i(x, y);
            fraction += fraction_increment;
            if(fraction >= 1) {
                x += (X1 <= X2 ? 1 : -1);
                fraction -= 2 * (Y1 <= Y2 ? (Y2 - Y1) : (Y1 - Y2));
            }
        }
    }
    glEnd();
}

void display()
{   
    glClear(GL_COLOR_BUFFER_BIT);
    bresenham_line(scale_x * 10, scale_y * 10, scale_x * 100, scale_y * 10);

    glBegin(GL_POLYGON);
    glVertex2i(scale_x * 20, scale_y * 20);
    glVertex2i(scale_x * 20, scale_y * 25);
    glVertex2i(scale_x * 25, scale_y * 20);
    glEnd();
    
    bresenham_circle(scale_x * 10);
    glFlush();
    printf("Enter x scale percentage: \n");
    scanf("%f", &scale_x);
    printf("Enter y scale percentage: \n");
    scanf("%f", &scale_y);
    // glFlush();
}

void display1() {
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);                         
    glutInitWindowSize(500, 500);                  
    glutInitWindowPosition(0, 0);                
    glutCreateWindow("Bresenham Circle");  
    glutDisplayFunc(display);
    glutIdleFunc(display1); 
    initGL();
    glutMainLoop();                               
    return 0;
}