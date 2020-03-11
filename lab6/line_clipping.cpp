#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

int X1, X2, Y1, Y2;

int xmin = 200, xmax = 500, ymin = 200, ymax = 500;

void initGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT); 
    glOrtho(0, 700, 0, 700, -1, 1);
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

int check() {
    unsigned int first_code = 0, second_code = 0;
    if(Y1 > ymax) {
        first_code += 8;
    }
    if(Y1 < ymin) {
        first_code += 4;
    }
    if(X1 > xmax) {
        first_code += 2;
    }
    if(X1 < xmin) {
        first_code += 1;
    }

    if(Y2 > ymax) {
        second_code += 8;
    }
    if(Y2 < ymin) {
        second_code += 4;
    }
    if(X2 > xmax) {
        second_code += 2;
    }
    if(X2 < xmin) {
        second_code += 1;
    }
    printf("first code:%d\nsecond code:%d\n", first_code, second_code);
    if((first_code == 0) && (second_code == 0)) {
        printf("visible line\n");
        return 1;
    }
    if((first_code & second_code) != 0) {
        printf(":%d\n", first_code & second_code);
        printf("invisible line\n");
        X1 = X2 = Y1 = Y2 = 0;
        return 0; 
    }
    return 2;
}

int clip_points() {
    // unsigned int first_code = 0, second_code = 0;
    // if(Y1 > ymax) {
    //     first_code += 8;
    // }
    // if(Y1 < ymin) {
    //     first_code += 4;
    // }
    // if(X1 > xmax) {
    //     first_code += 2;
    // }
    // if(X1 < xmin) {
    //     first_code += 1;
    // }

    // if(Y2 > ymax) {
    //     second_code += 8;
    // }
    // if(Y2 < ymin) {
    //     second_code += 4;
    // }
    // if(X2 > xmax) {
    //     second_code += 2;
    // }
    // if(X2 < xmin) {
    //     second_code += 1;
    // }
    // printf("first code:%d\nsecond code:%d\n", first_code, second_code);
    // if((first_code == 0) && (second_code == 0)) {
    //     printf("visible line\n");
    //     return;
    // }
    // if((first_code & second_code) != 0) {
    //     printf(":%d\n", first_code & second_code);
    //     printf("invisible line\n");
    //     X1 = X2 = Y1 = Y2 = 0;
    //     return; 
    // }
    int c = check();
    if(c == 1) return 1;
    if(c == 0) return 0;

    if(Y1 == Y2){
        if(X1 > xmax) {
            X1 = xmax;
        } else if(X1 < xmin) {
            X1 = xmin;
        }
        if(X2 > xmax) {
            X2 = xmax;
        } else if(X2 < xmin) {
            X2 = xmin;
        }
    }
    else if(X1 == X2) {
        if(Y1 > ymax) {
            Y1 = ymax;
        } else if(Y1 < ymin) {
            Y1 = ymin;
        }
        if(Y2 > ymax) {
            Y2 = ymax;
        } else if(Y2 < ymin) {
            Y2 = ymin;
        }
    }
    else{
        // float m = (Y2-Y1)/(X2-X1);
        float m = (float)(Y2-Y1)/(X2-X1);
        printf("--%d,%d %d,%d--\n", X1, Y1, X2, Y2);
        if(Y1 > ymax) {
            Y1 = ymax;
            X1 = X2 + (Y1 - Y2) / m;
        } else if(Y1 < ymin) {
            Y1 = ymin;
            X1 = X2 + (Y1 - Y2) / m;
        }
        printf("--%d,%d %d,%d--\n", X1, Y1, X2, Y2);
        if(X1 > xmax) {
            X1 = xmax;
            Y1 = Y2 + (X1 - X2) * m;
        } else if(X1 < xmin) {
            X1 = xmin;
            Y1 = Y2 + (X1 - X2) * m;
        }
        printf("--%d,%d %d,%d--\n", X1, Y1, X2, Y2);
        if(Y2 > ymax) {
            Y2 = ymax;
            X2 = X1 + (Y2 - Y1) / m;
        } else if(Y2 < ymin) {
            Y2 = ymin;
            X2 = X1 + (Y2 - Y1) / m;
        }
        printf("--%d,%d %d,%d--\n", X1, Y1, X2, Y2);
        if(X2 > xmax) {
            X2 = xmax;
            Y2 = Y1 + (X2 - X1) * m;
        } else if(X2 < xmin) {
            X2 = xmin;
            Y2 = Y1 + (X2 - X1) * m;
        }
        printf("--%d,%d %d,%d--\n", X1, Y1, X2, Y2);
    }
    return check();
}

void display()
{
    bresenham_line(xmin, ymin, xmin, ymax);
    bresenham_line(xmin, ymin, xmax, ymin);
    bresenham_line(xmin, ymax, xmax, ymax);
    bresenham_line(xmax, ymin, xmax, ymax);
   
    glFlush();
}

void idle() {
    printf("Enter X1 Y1 X2 Y2\n");
    scanf("%d%d%d%d", &X1, &Y1, &X2, &Y2);
    glColor3f(1, 0, 0);
    bresenham_line(X1, Y1, X2, Y2);
    if(clip_points() == 1) {
        printf("Clipped to %d,%d %d,%d\n", X1, Y1, X2, Y2);
        glColor3f(0, 1, 0);
        bresenham_line(X1, Y1, X2, Y2);
    }
    glColor3f(1, 1, 1);
    glFlush();
}

int main(int argc, char **argv)
{
    // printf("Enter X1 Y1 X2 Y2\n");
    // scanf("%lf%lf%lf%lf", &X1, &Y1, &X2, &Y2);
    glutInit(&argc, argv);                         
    glutInitWindowSize(700, 700);                  
    glutInitWindowPosition(0, 0);                
    glutCreateWindow("Line Clippng"); 
    glutDisplayFunc(display);        
    glutIdleFunc(idle);              
    initGL();                                      
    glutMainLoop();                               
    return 0;
}