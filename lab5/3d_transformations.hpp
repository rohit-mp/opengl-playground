#pragma once

#include <math.h>

float tx = 0, ty = 0, tz = 0;
float sx = 1, sy = 1, sz = 1;
float xangle = 0, yangle=0, zangle=0;

struct point {
    float x, y, z;
};

void mat_mul_vec(float a[4][4], float b[4][1], float result[4][1]) {
    for(int i = 0; i < 4; i++) {
        float res = 0;
        for(int k = 0; k < 4; k++) {
            res += (a[i][k] * b[k][0]);
        }
        result[i][0] = res;
    }
}

void translate(float *x, float *y, float *z) {    
    float m[4][4] = {{1, 0, 0, tx},
                     {0, 1, 0, ty},
                     {0, 0, 1, tz},
                     {0, 0, 0, 0 }};
    
    float v[4][1] = {{*x}, {*y}, {*z}, {1}};

    float output[4][1];
    mat_mul_vec(m, v, output);
    
    *x = output[0][0];
    *y = output[1][0];
    *z = output[2][0];
}

void rotatex(float *x, float *y, float *z) {    
    double theta = xangle * M_PI / 180.0f;

    float m[4][4] = {{1,          0,           0, 0},
                     {0, cos(theta), -sin(theta), 0},
                     {0, sin(theta),  cos(theta), 0},
                     {0,          0,           0, 1}};
    
    float v[4][1] = {{*x}, {*y}, {*z}, {1}};

    float output[4][1];
    mat_mul_vec(m, v, output);
    
    *x = output[0][0];
    *y = output[1][0];
    *z = output[2][0];
}

void rotatey(float *x, float *y, float *z) {    
    double theta = yangle * M_PI / 180.0f;

    float m[4][4] = {{ cos(theta), 0, sin(theta), 0},
                     {          0, 1,          0, 0},
                     {-sin(theta), 0, cos(theta), 0},
                     {          0, 0,          0, 0}};
    
    float v[4][1] = {{*x}, {*y}, {*z}, {1}};

    float output[4][1];
    mat_mul_vec(m, v, output);
    
    *x = output[0][0];
    *y = output[1][0];
    *z = output[2][0];
}

void rotatez(float *x, float *y, float *z) {    
    double theta = zangle * M_PI / 180.0f;

    float m[4][4] = {{cos(theta), -sin(theta), 0, 0},
                     {sin(theta),  cos(theta), 0, 0},
                     {         0,           0, 1, 0},
                     {         0,           0, 0, 0}};
    
    float v[4][1] = {{*x}, {*y}, {*z}, {1}};

    float output[4][1];
    mat_mul_vec(m, v, output);
    
    *x = output[0][0];
    *y = output[1][0];
    *z = output[2][0];
}

void scale(float *x, float *y, float *z) {    
    float m[4][4] = {{sx,  0,  0, 0},
                     { 0, sy,  0, 0},
                     { 0,  0, sz, 0},
                     { 0,  0,  0, 1}};
    
    float v[4][1] = {{*x}, {*y}, {*z}, {1}};

    float output[4][1];
    mat_mul_vec(m, v, output);
    
    *x = output[0][0];
    *y = output[1][0];
    *z = output[2][0];
}

struct point transform(float x, float y, float z) {
    translate(&x, &y, &z);
    scale(&x, &y, &z);
    rotatez(&x, &y, &z);
    rotatey(&x, &y, &z);
    rotatex(&x, &y, &z);
    struct point ret = {x, y, z};
    return ret;
}