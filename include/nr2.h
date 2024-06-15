#ifndef NR2_H
#define NR2_H

/* constant begin */
static float maxarg1;
static float maxarg2;
/* constant end */

/* prototype begin */
#define FMAX(a,b) (maxarg1=(a),maxarg2=(b),(maxarg1)>(maxarg2)?(maxarg1):(maxarg2))
#define SIGN(a,b) ((b)>0.0?fabs(a):-fabs(a))

/* Utilities */
extern void nrerror(char error_txt[]);
extern float* vector(long nl, long nh);
extern void free_vector(float* v, long nl, long nh);
extern int* ivector(long nl, long nh);
extern void free_ivector(int* v, long nl, long nh);
extern void nrerror(char error_txt[]);
extern float** matrix(long nrl, long nrh, long ncl, long nch);
extern void free_matrix(float** m, long nrl, long nrh, long ncl, long nch);

/* 2.1.c */
extern void gaussj(float **a, int n, float **b, int m);

/* 2.3.c LU Decomposition and Its Applications */
extern void ludcmp(float** a, int n, int* indx, float* d);
extern void lubksb(float** a, int n, int* indx, float b[]);


/* 6.1 */
extern float gammln(float xx);

/* 6.2.c */
extern float gammp(float a, float x);
extern float gammq(float a, float x);
extern void gser(float* gamser, float a, float x, float* gln);
extern void gcf (float* gammcf, float a, float x, float* gln);
extern float erff(float x);
extern float erffc(float x);

/* 6.4 */
extern float betai(float a, float b, float x);
extern float betacf(float a, float b, float x);


/* 8.2.c Sorting */
extern void sort(unsigned long n, float arr[]);
/* 8.5.c Sorting */
/*
extern float select(unsigned long k, unsigned long n, float arr[]);
*/
extern float nrselect(unsigned long k, unsigned long n, float arr[]);
/*
	11.1.c
*/
extern void jacobi(float** a, int n, float d[], float** v, int* nrot);
extern void eigsrt(float d[], float** v, int n);

/* 13.10.c Wavelet Transforms */
extern void wt1(float a[], unsigned long n, int isign, void (*wtstep)(float[], unsigned long, int));
extern void daub4(float a[], unsigned long n, int isign);
extern void pwtset(int n);
extern void pwt(float a[], unsigned long n, int isign);
extern void wtn(float a[], unsigned long nn[], int ndim, int isign, void (*wtstep)(float[], unsigned long, int));

/* 10.1.c */
extern void mnbrak(float* ax, float *bx, float* cx, float* fa, float* fb, float* fc, float (*func)(float));

/* 10.2.c */
extern float brent(float ax, float bx, float cx, float (*f)(float), float tol, float* xmin);

/* 10.5.c */
extern void linmin(float p[], float xi[], int n, float *fret, float (*func)(float[]));

/* 10.6.c ConjugateGradientMethods */
/*
void frprmn()   Polak-Ribiere 
void frprmn2()  Fletcher-Reeeves 
*/
extern void frprmn(float p[], int n, float ftol, int *iter, float* fret, 
       float (*func)(float[]), void (*dfunc)(float[], float []));
extern void frprmn2(float p[], int n, float ftol, int *iter, float* fret, 
       float (*func)(float[]), void (*dfunc)(float[], float []));
/* 15.2.c */
extern void fit(float x[], float y[], int ndata, float sig[], int mwt, float* a, float* b, float* siga, float* sigb, float* chi2, float* q);

/* 15.5.c */
extern void mrqmin(float x[], float y[], float sig[], int n, float a[], int ia[], int ma, float** covar, float** alpha, float* chisq, void (*func)(float x, float p[], float* y, float dyda[], int na), float *alamda); 

/* 15.7.c */
extern void medfit(float x[], float y[], int ndata, float* a, float* b, float* abdev);
extern float rofunc(float b);

/* prototype end */

#endif /* NR2_H */
