/* For search min of function of mrcImage. */


#ifndef MRC_IMAGEFUNCMIN_H
#define MRC_IMAGEFUNCMIN_H

/* macros */

/* prototype begin */

void mrcImagePeakFind(double* maxx ,double* maxy ,double* max ,mrcImage* in ,double ix ,double iy ,int mode );
float mrcImagePeakFinddummyfunc(float p[]);

void powell(float p[], float **xi, int n, float ftol, int *iter, float *fret,float (*func)(float [] ) );
void linmin2(float p[], float xi[], int n, float ftol, float *fret, float (*func)(float []  ) );
float f1dim(float x );
float brent(float ax, float bx, float cx, float (*f)(float ), float tol,float *xmin);
void mnbrak(float *ax, float *bx, float *cx, float *fa, float *fb, float *fc,float (*func)(float ));

/* prototype end */

# endif /* MRC_IMAGEFUNCMIN_H1 */

