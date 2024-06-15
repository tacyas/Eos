/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% arrayPCA ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : arrayPCA 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%arrayPCA ver%I%; Date:%D% %Z%";
#undef DEBUG
#include "genUtil.h"

#include "../inc/Array.h"
/*
    C*u = lambda^2*u
	where,
                   T	
        C = 1/n X*X
        X = [x1 x2 .. xn ]  
		                  T
		xi = [x y z .... ]
Input:
		xi : vector of elements for one datum.
		x  : vector of xi for all data 
Output:
		C  : Covariace array

		u        : unit vector
		lambda^2 : variance

		u1 and lambda1^2 : The first principal component
		u2 and lambda2^2 : The second principal component

		ave      : average vector for each xi 

*/

#include "nr2.h"
#undef DEBUG
#include "genUtil.h"

void
arrayPCATransform(Array* XX, Array* X, Array* ave, Array* u, int mode)
{
	int i, j, k;
	double sum;

	XX->dim = 2;
	XX->n[0] = X->n[0];
	XX->n[1] = X->n[1];
	arrayInit(XX, "in arrayPACTransform");	

#ifdef DEBUG
	arrayWriteToFile(stderr, u, "u");
	arrayWriteToFile(stderr, X, "X");
#endif
	for(i=0; i<XX->n[1]; i++) {
	for(j=0; j<XX->n[0]; j++) {
		sum = 0;
		for(k=0; k<XX->n[0]; k++) {
			// u0 u0 u0 u0
			// u1 u1 u1 u1
			// ...
			// un un un un
			
			// X0 X0 X0 X0 X0
			// ...
			// Xn Xn Xn Xn Xn
			sum += (arrayDataGet2(*X,k,i)-arrayDataGet1(*ave,k))*arrayDataGet2(*u, k, j);
		}
		arrayDataSet2(*XX, j, i, sum);
		DEBUGPRINT3("%d %d %f\n", j, i, sum);
	}
	}
#ifdef DEBUG
	arrayWriteToFile(stderr, XX, "XX");
#endif
}

void
arrayPCAPrint(FILE* fpt, Array* u, Array* lambda, int mode)
{
	double sum;
	double cum;
	int i, j;

	fprintf(fpt, "# PCA Results\n");
	fprintf(fpt, "Unit vector:\n");  
	arrayWriteToFile(fpt, u, "unit vector"); 
	fprintf(fpt, "Lambda:            ");  
	for(i=0; i<lambda->n[0]; i++) {
		fprintf(fpt, "%15.6e ", arrayDataGet1(*lambda, i));
	}
	fprintf(fpt, "\n");
	fprintf(fpt, "Normalized lambda: ");  
	sum = 0;
	for(i=0; i<lambda->n[0]; i++) {
		sum += arrayDataGet1(*lambda, i);
	}
	for(i=0; i<lambda->n[0]; i++) {
		fprintf(fpt, "%15.6e ", arrayDataGet1(*lambda, i)/sum);
	}
	fprintf(fpt, "\n");
	fprintf(fpt, "Cumulative lambda: ");  
	cum = 0;
	for(i=0; i<lambda->n[0]; i++) {
		cum += arrayDataGet1(*lambda, i)/sum;
		fprintf(fpt, "%15.6e ", cum);
	}
	fprintf(fpt, "\n");
}

void
arrayPCA(Array* u, Array* C, Array* lambda, Array* X, Array* average, int mode)
{
	int i, j, k;
	double ave;
	double s;
	Array TmpX;
	/* for nr */
	float** a;
	float** v;
	float*  d;
	int nrot;
	int n;

	if(2!=X->dim) {
		fprintf(stderr, "This array dimmension (%ld != 2) is not suitable for PCA(Principal Component Analysis).", X->dim);
	}
	TmpX.dim = 2;
	TmpX.n[0] = X->n[0];
	TmpX.n[1] = X->n[1];
	arrayInit(&TmpX, "TmpX in arrayPCA");

	if(0==mode) {
		lambda->dim = 1; 
		lambda->n[0] = X->n[0]; 
		arrayInit(lambda, "lambda in arrayPCA");

		average->dim = 1; 
		average->n[0] = X->n[0]; 
		arrayInit(average, "average in arrayPCA");

		C->dim = 2; 
		C->n[0] = X->n[0]; 
		C->n[1] = X->n[0]; 
		arrayInit(C, "C in arrayPCA");

		u->dim = 2; 
		u->n[0] = X->n[0]; 
		u->n[1] = X->n[0]; 
		arrayInit(u, "u in arrayPCA");
	}
	/* Calc TmpX : subtraction of average */ 
	for(i=0; i<X->n[0]; i++) {
		ave = 0;
		for(j=0; j<X->n[1]; j++) {
			ave += arrayDataGet2(*X, i, j);
		}
		ave /= X->n[1];
		for(j=0; j<X->n[1]; j++) {
			arrayDataSet2(TmpX, i, j, arrayDataGet2(*X,i,j) - ave);
		}
		arrayDataSet1(*average, i, ave); 
	}

	/* Calc C */
	for(i=0; i<X->n[0]; i++) {
	for(j=0; j<X->n[0]; j++) {
		s=0;
		for(k=0; k<X->n[1]; k++) {
			s+=arrayDataGet2(TmpX, i, k)*arrayDataGet2(TmpX, j, k);
		}
		arrayDataSet2(*C, i, j, s);
		DEBUGPRINT3("(%d,%d):=%f\n", i, j, s)
	}
	}

	/* Calc PCA */
	n = X->n[0];
	a = matrix(1, n, 1, n); //
	v = matrix(1, n, 1, n); //
	d = vector(1, n);       //
	for(i=0; i<n; i++) {
	for(j=0; j<n; j++) {
		a[i+1][j+1] = arrayDataGet2(*C, i, j); 
	}
	}
	jacobi(a, n, d, v, &nrot); //
#ifdef DEBUB
	DEBUGPRINT1("nrot for PCA: %d\n", nrot);
#endif
	eigsrt(d, v, n); //

	for(i=0; i<n; i++) {
		arrayDataSet1(*lambda, i, d[i+1]); 
	for(j=0; j<n; j++) {
		arrayDataSet2(*u, i, j, v[i+1][j+1]);
	}
	}

	arrayFree(&TmpX, "TmpX in arrayPCA");
}
