#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

double X1, X2, Y1, Y2;

void initGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glOrtho(0, 700, 0, 700, -1, 1);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT); 
    
    double dx = abs(X1-X2);
    double dy = abs(Y1-Y2);
    double steps = dx > dy ? dx : dy;
    double xInc = (X2-X1)/(double)steps;
    double yInc = (Y2-Y1)/(double)steps;
    double x = X1, y = Y1;

    printf("steps: %f\n", steps);
    printf("dx: %f\n", dx);
    printf("dy: %f\n", dy);
    printf("xInc: %f\n", xInc);
    printf("yInc: %f\n", yInc);

    glBegin(GL_POINTS);
    glColor3f(1.0f,0.0f,0.0f);
    glVertex2d(0, 0);
    glVertex2d(0.5, 0.5);
    glVertex2d(10, 10);
    for(double i = 0; i <= steps; i+=1) {
        // printf("Putting point at %lf,%lf\n", floor(x), floor(y));
        glVertex2d(floor(x+0.5), floor(y+0.5));
        // glVertex2d(x, y);
        x += xInc;
        y += yInc;
    }
    glEnd();
    
    glFlush();
}

int main(int argc, char **argv)
{
    printf("Enter X1 Y1 X2 Y2\n");
    scanf("%lf%lf%lf%lf", &X1, &Y1, &X2, &Y2);
    glutInit(&argc, argv);                         
    glutInitWindowSize(700, 700);                  
    glutInitWindowPosition(0, 0);                
    glutCreateWindow("DDA line drawing algo"); 
    glutDisplayFunc(display);                      
    initGL();                                      
    glutMainLoop();                               
    return 0;
}