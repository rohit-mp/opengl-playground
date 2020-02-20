#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

#include "transformations.hpp"

#define ROOT2 sqrt(2)

int trans_x = 0, trans_y = 0;
float scale_x = 1, scale_y = 1;
float angle = 0;

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

void update_point(struct point pt, struct point *pt_out) {
    struct point trans_info;
    trans_info.x=trans_x;trans_info.y=trans_y;
    struct point scale_info;
    scale_info.x=scale_x;scale_info.y=scale_y;
    my_translate(pt,trans_info,pt_out);
    pt=*pt_out;
    my_scale(pt, scale_info, pt_out);
    pt=*pt_out;
    my_rotate(pt,angle,pt_out);
}

void display()
{   
    struct point pt1;
    struct point pt2;
    struct point pt1_out;
    struct point pt2_out;
    glClear(GL_COLOR_BUFFER_BIT);
    pt1.x=10;pt1.y=10;
    pt2.x=100;pt2.y=10;
    update_point(pt1,&pt1_out);
    update_point(pt2,&pt2_out);
    bresenham_line( pt1_out.x,  pt1_out.y,  pt2_out.x,  pt2_out.y);

    glBegin(GL_POLYGON);
    pt1.x=40;pt1.y=40;update_point(pt1,&pt1_out);
    glVertex2i(pt1_out.x, pt1_out.y);
    pt1.x=60;pt1.y=60;update_point(pt1,&pt1_out);
    glVertex2i(pt1_out.x, pt1_out.y);
    pt1.x=40;pt1.y=60;update_point(pt1,&pt1_out);
    glVertex2i(pt1_out.x, pt1_out.y);
    glEnd();
    
    bresenham_circle(scale_x * 10);
    glFlush();
}

void display1() {
    glutPostRedisplay();
}

void keyPressed(unsigned char key, int x, int y) {
    if(key == 'w') {
        trans_y += 10;
    }
    else if(key=='a'){
        trans_x -= 10;
    }
    else if(key=='s'){
        trans_y-=10;
    }
    else if(key=='d'){
        trans_x+=10;
    }
    else if(key=='l'){
        scale_x+=0.1;
    }
    else if(key=='j'){
        scale_x-=0.1;
    }
    else if(key=='i'){
        scale_y+=0.1;
    }
    else if(key=='k'){
        scale_y-=0.1;
    }
    else if(key=='q'){
        angle+=10;
    }
    else if(key=='e'){
        angle-=10;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);                         
    glutInitWindowSize(500, 500);                  
    glutInitWindowPosition(0, 0);                
    glutCreateWindow("Bresenham Circle");  
    glutDisplayFunc(display);
    glutIdleFunc(display1); 
    glutKeyboardFunc(keyPressed);  
    initGL();
    glutMainLoop();                               
    return 0;
}