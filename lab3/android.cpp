#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

#define ROOT2 sqrt(2)

int R = 50; float angle = 0.0f, angle_inc=0.0f;
int trans_x = 0;
int clr_scr = 0;

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

void draw_half_symmetry(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glVertex2i(-x, y);
    // glVertex2i(x, -y);
    // glVertex2i(-x, -y);
    glVertex2i(y, x);
    glVertex2i(-y, x);
    // glVertex2i(y, -x);
    // glVertex2i(-y, -x);
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

void bresenham_half_circle(int R) {
    int x = 0, y = R;
    int d = 3 - 2 * R;
    while(y >= x) {
        draw_half_symmetry(x, y);
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

void drawBodyAndHead() {
    bresenham_half_circle(R);
    bresenham_line(-R, 0, R, 0);
    glTranslatef(2*R/5, 2*R/5, 0);
    bresenham_circle(R/10);
    glTranslatef(-2*R/5, -2*R/5, 0);
    glTranslatef(-2*R/5, 2*R/5, 0);
    bresenham_circle(R/10);
    glTranslatef(2*R/5, -2*R/5, 0);

    bresenham_line(-R, -R/5, R, -R/5);
    bresenham_line(-R, -R/5, -R, -2*R);
    bresenham_line(-R, -2*R, R, -2*R);
    bresenham_line(R, -R/5, R, -2*R);

    bresenham_line(-R/2 - R/5, -2*R - R/5, -R/2 + R/5, -2*R - R/5);
    bresenham_line(R/2 - R/5, -2*R - R/5, R/2 + R/5, -2*R - R/5);
    bresenham_line(-R/2 - R/5, -3*R - R/5, -R/2 + R/5, -3*R - R/5);
    bresenham_line(R/2 - R/5, -3*R - R/5, R/2 + R/5, -3*R - R/5);
    bresenham_line(-R/2 - R/5, -2*R - R/5, -R/2 - R/5, -3*R - R/5);
    bresenham_line(-R/2 + R/5, -2*R - R/5, -R/2 + R/5, -3*R - R/5);
    bresenham_line(R/2 + R/5, -2*R - R/5, R/2 + R/5, -3*R - R/5);
    bresenham_line(R/2 - R/5, -2*R - R/5, R/2 - R/5, -3*R - R/5);
}

void drawArms() {
    glPushMatrix();
    glTranslatef(-R -2*R/5, -R/5, 0);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(R +2*R/5, +R/5, 0);
    bresenham_line(-R - R/5, -R/5, -R - 3*R/5, -R/5);
    bresenham_line(-R - R/5, -2*R, -R - 3*R/5, -2*R);
    bresenham_line(-R - R/5, -R/5, -R - R/5, -2*R);
    bresenham_line(-R - 3*R/5, -R/5, -R - 3*R/5, -2*R);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(+R +2*R/5, -R/5, 0);
    glRotatef(-angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(-R -2*R/5, +R/5, 0);
    bresenham_line(R + R/5, -R/5, R + 3*R/5, -R/5);
    bresenham_line(R + R/5, -2*R, R + 3*R/5, -2*R);
    bresenham_line(R + R/5, -R/5, R + R/5, -2*R);
    bresenham_line(R + 3*R/5, -R/5, R + 3*R/5, -2*R);
    glPopMatrix();
}

void display1() {
    glutPostRedisplay();
}

void display()
{   
    glClear(GL_COLOR_BUFFER_BIT);
    if(clr_scr == 0){
        glPushMatrix();
        glTranslatef(trans_x, 0, 0);
        drawBodyAndHead();
        drawArms();
        glTranslatef(-trans_x, 0, 0);
        glPopMatrix();

        angle+=angle_inc;
    }
    glFlush();
}

// void mousePressed(int button, int state, int x, int y) {
//     if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
//         display(x, 500-y);
//     }
//     else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
//         exit(0);
//     }
// }

void keyPressed(unsigned char key, int x, int y) {
    if(key == 'c') {
        clr_scr = 1;
    }
    else if(key == 'i'){
        R += 10;
    }
    else if(key == 'd'){
        R -= 10;
    }
    else if(key == 'r'){
        angle_inc = 0.05f;
    }
    else if(key == 's'){
        angle = 0.0f;
        angle_inc = 0.0f;
    }
    else if(key == 't'){
        trans_x += 10;
    }
    else if(key == 'h'){
        trans_x -= 10;
    }
    else if(key == 'e'){
        exit(0);
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);                         
    glutInitWindowSize(500, 500);                  
    glutInitWindowPosition(0, 0);                
    glutCreateWindow("Bresenham Circle");  
    glutDisplayFunc(display); 
    // glutMouseFunc(mousePressed); 
    glutKeyboardFunc(keyPressed);    
    glutIdleFunc(display1);   
    initGL();
    glutMainLoop();                               
    return 0;
}