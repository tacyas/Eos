#include <stdlib.h>
#include <math.h>
#include "nr2.h"

#define GOLD          (1.618034)
#define GLIMIT        (100.0)
#define TINY          (1.0e-20)
#define SHFT(a,b,c,d) (a)=(b);(b)=(c);(c)=(d);

/* 
 Here GOLD is the default ratio by which successive intervals are magnified;
GLMIT is the maximum magnification allowed for a parabolic-fit step.
*/

void
mnbrak(float* ax, float *bx, float* cx, float* fa, float* fb, float* fc, float (*func)(float))
{
    float ulim, u, r, q, fu, dum;
    
    *fa = (func)(*ax);
    *fb = (func)(*bx);
    if(*fb>*fa) {   /* Switch roles of a and b so that we can go downhill in the direction from a to b. */
        SHFT(dum, *ax, *bx, dum);
        SHFT(dum, *fb, *fa, dum);
    }
    *cx = (*bx) + GOLD*(*bx - *ax); /* First guess for c */
    *fc = (*func)(*cx);
    while(*fb>*fc) {   /* Keep returing here until we bracket */
        /* Compute u by parabolic extrapolation from a, b, c.  
           TINY is used to prevent any possible division by zero */
        r = (*bx - *ax)*(*fb - *fc);
        q = (*bx - *cx)*(*fb - *fa);
        u = (*bx) - ((*bx - *cx)*q - (*bx - *ax)*r)/(2.0*SIGN(FMAX(fabs(q-r), TINY), q-r));
        ulim = (*bx) + GLIMIT*(*cx - *bx);
        if((*bx - u)*(u - *cx) > 0.0) { /* Parabolic u is between b and c: try it. */
            fu = (*func)(u);
            if(fu<*fc) { /* Got a minimum between b and c. */
                *ax = (*bx);
                *bx = u;
                *fa = (*fb);
                *fb = fu;
                return;
            } else if(fu > *fb) { /* Got a minimum between a and u */
                *cx = u;
                *fc = fu;
                return;
            }
            u = (*cx) + GOLD*(*cx - *bx); /* Parabolic fit was no use.  Use default magnification. */
            fu = (*func)(u);
        } else if((*cx - u)*(u - ulim) > 0.0) { /* Parabolic fit is between c and its allowed limit. */
            fu = (*func)(u);
            if(fu < *fc) {
                SHFT(*bx, *cx, u, *cx+GOLD*(*cx - *bx));
                SHFT(*fb, *fc, fu, (*func)(u));
            }
        } else if((u - ulim)*(ulim - *cx) >= 0.0) {
            u = ulim;
            fu = (*func)(u);
        } else {
            u = (*cx) + GOLD*(*cx - *bx);
            fu = (*func)(u);
        }
        SHFT(*ax, *bx, *cx, u); /* Eliminate oldest point and continue. */
        SHFT(*fa, *fb, *fc, fu);
    }
}
