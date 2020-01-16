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
   
   glBegin(GL_POINTS);
    if(X1!=X2){
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
            int tmp = Y1;
            Y1 = Y2;
            Y2 = tmp;
        }
        int x = X1, y = Y1;
        while(y <= Y2){
            glVertex2i(x, y);
            y = y + (Y1<=Y2 ? 1 : -1);
        }
    }
    // glBegin(GL_POINTS);
    // if(X1!=X2){
    //     int fraction = 0;
    //     int fraction_increment = 2 * (Y2 - Y1);
    //     int x, y;
    //     for(x = X1, y = Y1; x <= X2; x++) {
    //         glVertex2i(x, y);
    //         fraction += fraction_increment;
    //         if(fraction >= 1) {
    //             y += 1;
    //             fraction -= 2 * (X2 - X1);
    //         }
    //     }
    // }
    // else{
    //     int fraction = 0;
    //     int fraction_increment = 2 * (X2 - X1);
    //     int x, y;
    //     for(x = X1, y = Y1; y <= Y2; y++) {
    //         glVertex2i(x, y);
    //         fraction += fraction_increment;
    //         if(fraction >= 1) {
    //             x += 1;
    //             fraction -= 2 * (Y2 - Y1);
    //         }
    //     }  
    // }
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