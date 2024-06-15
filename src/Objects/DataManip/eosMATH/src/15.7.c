#include<stdio.h>
#include <math.h>
#define NRANSI
#include "nr2.h"
int ndatat;
float *xt,*yt,aa,abdevt;

void medfit(float x[], float y[], int ndata, float *a, float *b, float *abdev)
{
	float rofunc(float b);
	int j;
	float bb,b1,b2,del,f,f1,f2,sigb,temp;
	float sx=0.0,sy=0.0,sxy=0.0,sxx=0.0,chisq=0.0;

	ndatat=ndata;
	xt=x;
	yt=y;
	for (j=1;j<=ndata;j++) {
		sx += x[j];
		sy += y[j];
		sxy += x[j]*y[j];
		sxx += x[j]*x[j];
	}
	del=ndata*sxx-sx*sx;
	aa=(sxx*sy-sx*sxy)/del;
	bb=(ndata*sxy-sx*sy)/del;
	for (j=1;j<=ndata;j++)
		chisq += (temp=y[j]-(aa+bb*x[j]),temp*temp);
	sigb=sqrt(chisq/del);
	b1=bb;
	f1=rofunc(b1);
	b2=bb+SIGN(3.0*sigb,f1);
	f2=rofunc(b2);
	while (f1*f2 > 0.0) {
		bb=2.0*b2-b1;
		b1=b2;
		f1=f2;
		b2=bb;
		f2=rofunc(b2);
	}
	sigb=0.01*sigb;
	while (fabs(b2-b1) > sigb) {
		bb=0.5*(b1+b2);
		if (bb == b1 || bb == b2) break;
		f=rofunc(bb);
		if (f*f1 >= 0.0) {
			f1=f;
			b1=bb;
		} else {
			f2=f;
			b2=bb;
		}
	}
	*a=aa;
	*b=bb;
	*abdev=abdevt/ndata;
}
#undef NRANSI
#include <math.h>
#define NRANSI
#include "nr2.h"
#define EPS 1.0e-7

extern int ndatat;
extern float *xt,*yt,aa,abdevt;

float rofunc(float b)
{
	float nrselect(unsigned long k, unsigned long n, float arr[]);
	int j;
	float *arr,d,sum=0.0;

	arr=vector(1,ndatat);
	for (j=1;j<=ndatat;j++) arr[j]=yt[j]-b*xt[j];
	if (ndatat & 1) {
		aa=nrselect((ndatat+1)>>1,ndatat,arr);
	}
	else {
		j=ndatat >> 1;
		aa=0.5*(nrselect(j,ndatat,arr)+nrselect(j+1,ndatat,arr));
	}
	abdevt=0.0;
	for (j=1;j<=ndatat;j++) {
		d=yt[j]-(b*xt[j]+aa);
		abdevt += fabs(d);
		if (yt[j] != 0.0) d /= fabs(yt[j]);
		if (fabs(d) > EPS) sum += (d >= 0.0 ? xt[j] : -xt[j]);
	}
	free_vector(arr,1,ndatat);
	return sum;
}
#undef EPS
#undef NRANSI
