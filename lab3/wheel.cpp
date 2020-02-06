#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

#define ROOT2 sqrt(2)

int R = 50;

void initGL()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
    gluOrtho2D(0, 500, 0, 500);
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

void display(int X1, int Y1)
{   
    // glClear(GL_COLOR_BUFFER_BIT);
    
    glPushMatrix();
    glTranslatef(X1, Y1, 0);
    // glRotatef(-angle, 0.0f, 0.0f, 1.0f);
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

    // angle += 0.01;

    glFlush();
}

void mousePressed(int button, int state, int x, int y) {
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        display(x, 500-y);
    }
    else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        exit(0);
    }
}

void keyPressed(unsigned char key, int x, int y) {
    if(key == 'c') {
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();
    }
    else if(key == 'i'){
        R += 20;
    }
    else if(key == 'd'){
        R -= 20;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);                         
    glutInitWindowSize(500, 500);                  
    glutInitWindowPosition(0, 0);                
    glutCreateWindow("Bresenham Circle");  
    // glutDisplayFunc(display); 
    glutMouseFunc(mousePressed); 
    glutKeyboardFunc(keyPressed);       
    initGL();
    glutMainLoop();                               
    return 0;
}

/*
left - draw
right - exit
i - increase
d - decrease
c - clear screen
*/