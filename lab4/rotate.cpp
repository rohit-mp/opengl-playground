#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

#include "transformations.hpp"

#define ROOT2 sqrt(2)

int angle = 0;

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
    glVertex2i( x,  y);
    glVertex2i( -x,  y);
    glVertex2i( x,  -y);
    glVertex2i( -x,  -y);
    glVertex2i( y,  x);
    glVertex2i( -y,  x);
    glVertex2i( y,  -x);
    glVertex2i( -y,  -x);
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

int rot(int x, int y) {

}

void display()
{   
    glClear(GL_COLOR_BUFFER_BIT);

    struct point pt1;
    struct point pt2;
    pt1.x = 10; pt1.y = 10;
    pt2.x = 100; pt2.y = 10;
    struct point pt1_out;
    struct point pt2_out;
    my_rotate(pt1, angle, &pt1_out);
    my_rotate(pt2, angle, &pt2_out);
    bresenham_line( pt1_out.x, pt1_out.y, pt2_out.x, pt2_out.y);

    glBegin(GL_POLYGON);
    struct point pt;
    pt.x = 40; pt.y = 40;
    struct point pt_out;
    my_rotate(pt, angle, &pt_out);
    glVertex2i(pt_out.x, pt_out.y);
    pt.x = 60; pt.y = 60;
    my_rotate(pt, angle, &pt_out);
    glVertex2i(pt_out.x, pt_out.y);
    pt.x = 40; pt.y = 60;
    my_rotate(pt, angle, &pt_out);
    glVertex2i(pt_out.x, pt_out.y);
    glEnd();
    
    glFlush();
    printf("Enter angle: \n");
    scanf("%d", &angle);
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