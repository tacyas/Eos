#include "nr2.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#define MAXIT 	100
#define EPS 	3.0e-7
#define FPMIN 	1.0e-30

float
betai(float a, float b, float x)
{
	float betacf(float a, float b, float x);

	float bt;

	if(x<0.0 || 1.0<x) nrerror("Bad x in routine betai");
	if(x==0.0 || 1.0==x) {
		bt = 0.0;
	} else {
		bt = exp(gammln(a+b) - gammln(a) - gammln(b) + a*log(x) + b*log(1.0-x));
	}
	if(x<(a+1.0)/(a+b+2.0)) {
		return bt*betacf(a, b, x)/a;
	} else {
		return 1.0 - bt*betacf(b, a, 1.0-x)/b;
	}
}

float
betacf(float a, float b, float x)
{
	int m, m2;
	float aa, c, d, del, h, qab, qam, qap;

	qab = a+b;
	qap = a+1.0;
	qam = a-1.0;
	c = 1.0;
	d = 1.0 - qab*x/qap;
	if(fabs(d) < FPMIN) d=FPMIN;
	d = 1.0/d;
	h = d;
	for(m=1; m<=MAXIT; m++) {
		m2 = 2*m;
		aa=m*(b-m)*x/((qam+m2)*(a+m2));
		d = 1.0 + aa*d;
		if(fabs(d)<FPMIN) d=FPMIN;
		c = 1.0+aa/c;
		if(fabs(c)<FPMIN) c=FPMIN;
		d=1.0/d;
		h *= d*c;
		aa = -(a+m)*(qab+m)*x/((a+m2)*(qap+m2));
		d = 1.0+aa*d;
		if(fabs(d)<FPMIN) d=FPMIN;
		c = 1.0+aa/c;
		if(fabs(c)<FPMIN) c=FPMIN;
		d = 1.0/d;
		del = d*c;
		h *= del;
		if(fabs(del-1.0)<EPS) break;
	}
	if(m>MAXIT) { 
		fprintf(stderr, "%f %f %f in betacf\n", a, b, x);
		nrerror("a or b too big, or MAXIT too small in betacf");
	}
	return h;
}
