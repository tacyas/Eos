#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#undef DEBUG
#include "genUtil.h"
#include "../inc/mrcImage.h"
#include "mrcRefUtil.h"



double 
lbilinearInterpolation(double* image,
                       unsigned long nx, unsigned long ny,
                       double x, double y)
{
    double dat;

    dat = 0.0;
    dat += ((1-(x-(int)x))*(1-(y-(int)y))*image[(int)x   + nx*((int)y  )]);
    dat += ((1-(x-(int)x))*(   y-(int)y) *image[(int)x   + nx*((int)y+1)]);
    dat += (   (x-(int)x) *(1-(y-(int)y))*image[(int)x+1 + nx*((int)y  )]);
    dat += (   (x-(int)x) *(   y-(int)y) *image[(int)x+1 + nx*((int)y+1)]);
    return(dat);
}

double
lcubicConvolutionInterpolation(double* image, 
                                unsigned long nx, unsigned long ny, 
                                double x, double y)
{
    double dat;
    long int xl, yl;
    long int xmin, xmax, ymin, ymax;
    double dx, dy;


    if((int)(x-3.0)<0) {
        xmin = 0;
    } else {
        xmin = (int)(x-3.0);
    }
    if((int)(x+3.0)>nx-1) {
        xmax = nx-1;
    } else {
        xmax = (int)(x+3.0);
    }

    if((int)(y-3.0)<0) {
        ymin = 0;
    } else {
        ymin = (int)(y-3.0);
    }
    if((int)(y+3.0)>ny-1) {
        ymax = ny-1;
    } else {
        ymax = (int)(y+3.0);
    }

    dat = 0.0;
    for(xl=xmin; xl<=xmax; xl++) {
        for(yl=ymin; yl<=ymax; yl++) {
            dx = fabs(x-xl);
            dy = fabs(y-yl);
            if(dx>=2.0||dy>=2.0) {
                dat += 0.0;
            } else if(dx>=1.0&&dy>=1.0) {
                dat += ((4.0-8.0*dx+5.0*dx*dx-dx*dx*dx)
                       *(4.0-8.0*dy+5.0*dy*dy-dy*dy*dy)
                       *(image[xl+yl*nx]));
            } else if(dx>=1.0&&dy<1.0) {
                dat += ((4.0-8.0*dx+5.0*dx*dx-dx*dx*dx)
                       *(1.0-2.0*dy*dy+dy*dy*dy)
                       *(image[xl+yl*nx]));
            } else if(dx<1.0&&dy>=1.0) {
                dat += ((4.0-8.0*dy+5.0*dy*dy-dy*dy*dy)
                       *(1.0-2.0*dx*dx+dx*dx*dx)
                       *(image[xl+yl*nx]));
            } else if(dx<1.0&&dy<1.0) {
                dat += ((1.0-2.0*dx*dx+dx*dx*dx)
                       *(1.0-2.0*dy*dy+dy*dy*dy)
                       *(image[xl+yl*nx]));
            } else {
                fprintf(stderr, "That's stupid!\n!");
            }
        }
    }
    return(dat);
}


double
lpolyNominalInterpolation(double* image, 
                                unsigned long nx, unsigned long ny, 
                                double x, double y)
{
    int m, n;
    static double coefficient[6];
    static double matrix[6][6];
    static double vec[6];

    m = (int)floor(x);
    n = (int)floor(y);
    lpolyInitMatrix(matrix, m, n);
    lpolyInitVector(vec, m, n, image, nx, ny);
    if(lpolySolveMatrix(matrix, vec, coefficient)) {
        return coefficient[0]*x*x + coefficient[1]*x*y
             + coefficient[2]*y*y + coefficient[3]*x
             + coefficient[4]*y   + coefficient[5];
    } else {
        fprintf(stderr, "trace = 0 at (%f, %f)\n", x, y);
        return lbilinearInterpolation(image, nx, ny,x, y);
    }
} 


void 
lpolyInitMatrix(double matrix[6][6], int m, int n)
{
    int  i,j;

    for(i=0; i<6; i++) {
        for(j=0; j<6; j++) {
            matrix[i][j] = 0.0;
        }
    }
    i=m-1;
    for(j=n;j<=n+1;j++) {
        matrix[0][0] += (double)(i*i*i*i);
        matrix[0][1] += (double)(i*i*i*j);
        matrix[0][2] += (double)(i*i*j*j);
        matrix[0][3] += (double)(i*i*i);
        matrix[0][4] += (double)(i*i*j);
        matrix[0][5] += (double)(i*i);
        matrix[1][1] += (double)(i*i*j*j);
        matrix[1][2] += (double)(i*j*j*j);
        matrix[1][3] += (double)(i*i*j);
        matrix[1][4] += (double)(i*j*j);
        matrix[1][5] += (double)(i*j);
        matrix[2][2] += (double)(j*j*j*j);
        matrix[2][3] += (double)(i*j*j);
        matrix[2][4] += (double)(j*j*j);
        matrix[2][5] += (double)(j*j);
        matrix[3][3] += (double)(i*i);
        matrix[3][4] += (double)(i*j);
        matrix[3][5] += (double)i;
        matrix[4][4] += (double)(j*j);
        matrix[4][5] += (double)j;
        matrix[5][5] += 1.0;
    }
    for(i=m;i<=m+1;i++) {
        for(j=n-1;j<=n+2;j++) {
            matrix[0][0] += (double)(i*i*i*i);
            matrix[0][1] += (double)(i*i*i*j);
            matrix[0][2] += (double)(i*i*j*j);
            matrix[0][3] += (double)(i*i*i);
            matrix[0][4] += (double)(i*i*j);
            matrix[0][5] += (double)(i*i);
            matrix[1][1] += (double)(i*i*j*j);
            matrix[1][2] += (double)(i*j*j*j);
            matrix[1][3] += (double)(i*i*j);
            matrix[1][4] += (double)(i*j*j);
            matrix[1][5] += (double)(i*j);
            matrix[2][2] += (double)(j*j*j*j);
            matrix[2][3] += (double)(i*j*j);
            matrix[2][4] += (double)(j*j*j);
            matrix[2][5] += (double)(j*j);
            matrix[3][3] += (double)(i*i);
            matrix[3][4] += (double)(i*j);
            matrix[3][5] += (double)i;
            matrix[4][4] += (double)(j*j);
            matrix[4][5] += (double)j;
            matrix[5][5] += 1.0;
        }
    }
    i=m+2;
    for(j=n;j<=n+1;j++) {
        matrix[0][0] += (double)(i*i*i*i);
        matrix[0][1] += (double)(i*i*i*j);
        matrix[0][2] += (double)(i*i*j*j);
        matrix[0][3] += (double)(i*i*i);
        matrix[0][4] += (double)(i*i*j);
        matrix[0][5] += (double)(i*i);
        matrix[1][1] += (double)(i*i*j*j);
        matrix[1][2] += (double)(i*j*j*j);
        matrix[1][3] += (double)(i*i*j);
        matrix[1][4] += (double)(i*j*j);
        matrix[1][5] += (double)(i*j);
        matrix[2][2] += (double)(j*j*j*j);
        matrix[2][3] += (double)(i*j*j);
        matrix[2][4] += (double)(j*j*j);
        matrix[2][5] += (double)(j*j);
        matrix[3][3] += (double)(i*i);
        matrix[3][4] += (double)(i*j);
        matrix[3][5] += (double)i;
        matrix[4][4] += (double)(j*j);
        matrix[4][5] += (double)j;
        matrix[5][5] += 1.0;
    }
    for(i=1;i<6;i++) {
        for(j=0;j<i;j++) {
            matrix[i][j] = matrix[j][i];
        }
    }
}

void 
lpolyInitVector(double vec[6], int m, int n, double* image, int nx, int ny)
{
    int  i,j;
    int  value;
    int  offset;
    char buf_upper,buf_lower;

    for(i=0;i<6;i++) {
         vec[i] = 0.0;
    }
    i=m-1;
    for(j=n;j<=n+1;j++) {
         value = image[i+j*nx];
         vec[0] += (double)(i*i*value);
         vec[1] += (double)(i*j*value);
         vec[2] += (double)(j*j*value);
         vec[3] += (double)(i*value);
         vec[4] += (double)(j*value);
         vec[5] += (double)(value);
    }
    for(i=m;i<=m+1;i++) {
        for(j=n-1;j<=n+2;j++) {
            value = image[i+j*nx];
            vec[0] += (double)(i*i*value);
            vec[1] += (double)(i*j*value);
            vec[2] += (double)(j*j*value);
            vec[3] += (double)(i*value);
            vec[4] += (double)(j*value);
            vec[5] += (double)(value);
        }
    }
    i=m+2;
    for(j=n;j<=n+1;j++) {
        value = image[i+j*nx];
        vec[0] += (double)(i*i*value);
        vec[1] += (double)(i*j*value);
        vec[2] += (double)(j*j*value);
        vec[3] += (double)(i*value);
        vec[4] += (double)(j*value);
        vec[5] += (double)(value);
    }
}


int 
lpolySolveMatrix(double matrix[6][6], double vec[6], double coefficient[6])
{
    int  i, j, k;

    for(i=0;i<6;i++) {
        if(matrix[i][i]==0) {
            return 0;
        }
        for(j=i+1;j<6;j++) {
             matrix[i][j] /= matrix[i][i];
        }
        vec[i] /= matrix[i][i];
        for(k=0;k<6;k++) {
            if(k!=i) {
                for(j=i+1;j<6;j++) {
                       matrix[k][j] -= matrix[k][i]*matrix[i][j];
                }
                vec[k] -= matrix[k][i]*vec[i];
            }
        }
    }
    for(i=0;i<6;i++) {
        coefficient[i] = vec[i];
    }
    return 1;
}
