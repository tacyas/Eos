#include <stdlib.h>
#include <math.h>
#include "nr2.h"

/* Tolerance passed to brent. */
#define TOL (2.0e-4)
       
/* Variables communicate with f1dim */
static int ncom;
static float* pcom;
static float* xicom;
static float (*nrfunc)(float []);
/*
    void
    linmin(float p[], float xi[], int n, float *fret, float (*func)(float[]))

 Given an n-dimensional point p[1..n] and an n-dimensional direction xi[1..n], 
moves and resets p to where the function func(p) takes on a minimum along the direction xi from p,
and replaces xi by the actual vector displacement that p was moved.
Also returns as fret the value of func at the returned location p.  
This is actually all accomplished by calling the routines mnbrak and brent.
*/

void
linmin(float p[], float xi[], int n, float *fret, float (*func)(float[]))
{
    float brent(float ax, float bx, float cx, float (*f)(float), float tol, float *xmin);
    float f1dim(float x);
    void mnbrak(float *ax, float *bx, float *cx, float *fa, float *fb, float *fc, float (*func)(float));
    int j;
    float xx, xmin, fx, fb, fa, bx, ax;

    ncom = n;
    pcom = vector(1, n);
    xicom = vector(1, n);
    nrfunc = func;
    for(j=1; j<=n; j++) {
        pcom[j] = p[j];
        xicom[j] = xi[j];
    }
    ax = 0.0;
    xx = 1.0;
    mnbrak(&ax, &xx, &bx, &fa, &fx, &fb, f1dim);
    *fret = brent(ax, xx, bx, f1dim, TOL, &xmin);
    for(j=1; j<=n; j++) {
        xi[j] *= xmin;
        p[j] += xi[j];
    }
    free_vector(xicom, 1, n);
    free_vector(pcom, 1, n);
}

float 
f1dim(float x)
{
    int j;
    float f, *xt;

    xt = vector(1, ncom);
    for(j=1; j<=ncom; j++) {
        xt[j] = pcom[j]+x*xicom[j];
    }
    f = (*nrfunc)(xt);
    free_vector(xt, 1, ncom);
    return f;
}






