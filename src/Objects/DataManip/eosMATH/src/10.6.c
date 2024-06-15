#include <stdlib.h>
#include <math.h>
#include "nr2.h"

#define ITMAX (1000)
#define EPS   (1.0e-10)
/*
 Here ITMAX is the maximum allowd number of iterations, 
while EPS is a small number to rectify the special case of converging to exactly zero
function value.
*/

#define FREEALL free_vector(xi, 1, n); free_vector(h, 1, n); free_vector(g, 1, n);

/*
void frprmn(float p[], 
            int n, 
            float ftol, 
            int *iter, 
            float* fret, 
            float (*func)(float[]), 
            void (*dfunc)(float[], float []))
 Given a starting pint p[1..n], Fletcher-Reeves-Polak-Ribiere minimization 
is performed on a function funct, using its gradient as calculated by a routine dfunc.
The convergence tolerance on the function value is input as ftol.
Returned quantities are p (the location of the minimum), 
iter (the number of iterations that are performed), and fret (the minimum value of the
function).  The routein linmin is called to perform line minimizations.

void frprmn()   Polak-Ribiere 
void frprmn2()  Fletcher-Reeeves 
*/

void
frprmn(float p[], int n, float ftol, int *iter, float* fret, 
       float (*func)(float[]), void (*dfunc)(float[], float []))
{
    void linmin(float p[], float xi[], int n, float *fret, float (*func)(float []));
    int j, its;
    float gg, gam, fp, dgg;
    float *g, *h, *xi;

    g = vector(1, n);
    h = vector(1, n);
    xi= vector(1, n);
    fp=(*func)(p);                  /* Initialization */
    (*dfunc)(p, xi);
    for(j=1; j<=n; j++) {
        g[j] = -xi[j];
        xi[j] = h[j] = g[j];
    }
    for(its=1; its<=ITMAX; its++) { /* Loop over iterations */
        *iter=its;
        linmin(p, xi, n, fret, func); 
        if(2.0*fabs(*fret-fp)<=ftol*(fabs(*fret)+fabs(fp)+EPS)) {
            /* This condition is the normal return. */
            FREEALL
            return;
        }
        fp = (*func)(p);
        (*dfunc)(p, xi);
        dgg = gg = 0.0;
        for(j=1; j<=n; j++) {
            gg  += g[j]*g[j];
/*          dgg += xi[j]*xi[j]; */     /* This statement for Fletcher-Reeves */
            dgg += (xi[j]+g[j])*xi[j]; /* This statement for Polak Ribiere */
        }
        if(gg==0.0) {
            /* Unlikely, if gradient is exactly zero then we are already done */
            FREEALL
            return;
        }
        gam = dgg/gg;
        for(j=1; j<=n; j++) {
            g[j] = -xi[j];
            xi[j] = h[j] = g[j] + gam*h[j];
        }
    }
    nrerror("Too many iterations in frprmn");
}

void
frprmn2(float p[], int n, float ftol, int *iter, float* fret, 
       float (*func)(float[]), void (*dfunc)(float[], float []))
{
    void linmin(float p[], float xi[], int n, float *fret, float (*func)(float []));
    int j, its;
    float gg, gam, fp, dgg;
    float *g, *h, *xi;

    g = vector(1, n);
    h = vector(1, n);
    xi= vector(1, n);
    fp=(*func)(p);                  /* Initialization */
    (*dfunc)(p, xi);
    for(j=1; j<=n; j++) {
        g[j] = -xi[j];
        xi[j] = h[j] = g[j];
    }
    for(its=1; its<=ITMAX; its++) { /* Loop over iterations */
        *iter=its;
        linmin(p, xi, n, fret, func); 
        if(2.0*fabs(*fret-fp)<=ftol*(fabs(*fret)+fabs(fp)+EPS)) {
            /* This condition is the normal return. */
            FREEALL
            return;
        }
        fp = (*func)(p);
        (*dfunc)(p, xi);
        dgg = gg = 0.0;
        for(j=1; j<=n; j++) {
            gg  += g[j]*g[j];
            dgg += xi[j]*xi[j];          /* This statement for Fletcher-Reeves */
/*          dgg += (xi[j]+g[j])*xi[j]; *//* This statement for Polak Ribiere */
        }
        if(gg==0.0) {
            /* Unlikely, if gradient is exactly zero then we are already done */
            FREEALL
            return;
        }
        gam = dgg/gg;
        for(j=1; j<=n; j++) {
            g[j] = -xi[j];
            xi[j] = h[j] = g[j] + gam*h[j];
        }
    }
    nrerror("Too many iterations in frprmn");
}
