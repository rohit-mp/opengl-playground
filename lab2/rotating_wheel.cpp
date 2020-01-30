#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

#define ROOT2 sqrt(2)

int X1 = 100, Y1 = 100, R = 50;
float angle = 0.0f;

void initGL()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    gluOrtho2D(0, 800, 0, 800);
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

// void bresenham_circle(int X1, int Y1, int R) {
void bresenham_circle(int R) {
    // glTranslatef(X1, Y1, 0);
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
    // glTranslatef(-X1, -Y1, 0);
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

void display1() {
    glutPostRedisplay();
}

void display()
{   
    glClear(GL_COLOR_BUFFER_BIT);
    bresenham_line(0, 50, 800, 50);
    
    glPushMatrix();
    glTranslatef(X1, Y1, 0);
    glRotatef(-angle, 0.0f, 0.0f, 1.0f);
    bresenham_circle(R);
    bresenham_circle(R/5);
    glTranslatef(-X1, -Y1, 0);

    bresenham_line(X1, Y1+R/5, X1, Y1+R);
    bresenham_line(X1, Y1-R/5, X1, Y1-R);
    bresenham_line(X1+R/5, Y1, X1+R, Y1);
    bresenham_line(X1-R/5, Y1, X1-R, Y1);
    bresenham_line(X1+(R/5)/ROOT2, Y1+(R/5)/ROOT2, X1+R/ROOT2, Y1+R/ROOT2);
    bresenham_line(X1+(R/5)/ROOT2, Y1-(R/5)/ROOT2, X1+R/ROOT2, Y1-R/ROOT2);
    bresenham_line(X1-(R/5)/ROOT2, Y1+(R/5)/ROOT2, X1-R/ROOT2, Y1+R/ROOT2);
    bresenham_line(X1-(R/5)/ROOT2, Y1-(R/5)/ROOT2, X1-R/ROOT2, Y1-R/ROOT2);
    glPopMatrix();

    angle += 0.01;

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);                         
    glutInitWindowSize(800, 800);                  
    glutInitWindowPosition(0, 0);                
    glutCreateWindow("Bresenham Circle"); 
    initGL(); 
    glutDisplayFunc(display); 
    glutIdleFunc(display1);                      
                                         
    glutMainLoop();                               
    return 0;
}