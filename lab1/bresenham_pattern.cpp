#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

// double X1, X2, Y1, Y2;

void initGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glOrtho(0, 700, 0, 700, -1, 1);
}

void bresenham(int X1, int Y1, int X2, int Y2) {
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
    bresenham(100, 100, 500, 100);
    bresenham(100, 500, 500, 500);
    bresenham(100, 100, 100, 500);
    bresenham(500, 100, 500, 500);
    bresenham(300, 100, 500, 300);
    bresenham(500, 300, 300, 500);
    bresenham(300, 500, 100, 300);
    bresenham(100, 300, 300, 100);
    bresenham(200, 200, 200, 400);
    bresenham(200, 400, 400, 400);
    bresenham(400, 200, 400, 400);
    bresenham(200, 200, 400, 200);
    glFlush();
}

int main(int argc, char **argv)
{
    // printf("Enter X1 Y1 X2 Y2\n");
    // scanf("%lf%lf%lf%lf", &X1, &Y1, &X2, &Y2);
    glutInit(&argc, argv);                         
    glutInitWindowSize(700, 700);                  
    glutInitWindowPosition(0, 0);                
    glutCreateWindow("DDA line drawing algo"); 
    glutDisplayFunc(display);                      
    initGL();                                      
    glutMainLoop();                               
    return 0;
}