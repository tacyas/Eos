#include <math.h>
#include "nr2.h"

float gammp(float a, float x)
{
	float gamser, gammcf, gln;

	if(x<0.0 || a<=0.0) nrerror("Invalid arguments in routine gammp");
	if(x < (a +1.0)) {
		gser(&gamser, a, x, &gln);
		return gamser;
	} else {
		gcf(&gammcf, a, x, &gln);
		return 1.0 - gammcf;
	}
}

float gammq(float a, float x)
{
	float gamser, gammcf, gln;

	if(x<0.0 || a<=0.0) nrerror("Invalid arguments in routine gammq");
	if(x < (a +1.0)) {
		gser(&gamser, a, x, &gln);
		return 1.0 - gamser;
	} else {
		gcf(&gammcf, a, x, &gln);
		return gammcf;
	}
}

#define ITMAX (100)
#define EPS   (3.0e-7)
#define FPMIN (1.0e-30)

void gser(float* gamser, float a, float x, float* gln)
{
	int n;
	float sum, del, ap;

	*gln = gammln(a);
	if(x<=0.0) {
		if(x<0.0) nrerror("x less than 0 in routine gser");
		*gamser = 0.0;
		return; 
	} else {
		ap = a;
		del = sum = 1.0/a;
		for(n=1; n<=ITMAX; n++) {
			++ap;
			del *= x/ap;
			sum += del;
			if(fabs(del) < fabs(sum)*EPS) {
				*gamser = sum*exp(-x+a*log(x) - (*gln));
				return;
			}
		}	
		nrerror("a too large, ITMAX too small in routine gser");
		return;
	}
}

void gcf(float* gammcf, float a, float x, float* gln)
{
	float an, b, c, d, del, h;
	int i;

	*gln = gammln(a);
	b = x+1.0-a;
	c = 1.0/FPMIN; 
	d = 1.0/b;
	h = d;
	for(i=1; i<=ITMAX; i++) {
		an = -i*(i-a);
		b += 2.0;
		d = an*d + b;
		if(fabs(d) < FPMIN) d = FPMIN;
		c = b + an/c;
		if(fabs(c) < FPMIN) c = FPMIN;
		d = 1.0/d;
		del = d*c;
		h *= del;
		if(fabs(del-1.0)<EPS) break;
	}
	if(i>ITMAX) nrerror("a too large, ITMAX too small in gcf");
	*gammcf=exp(-x+a*log(x)-(*gln))*h;
}

float erff(float x)
{
	return x < 0.0 ? -gammp(0.5,x*x): gammp(0.5,x*x);
}

float erffc(float x)
{
	return x<0.0 ? 1.0+gammp(0.5,x*x) : gammq(0.5,x*x); 
}

float erfcc(float x)
{
	float t, z, ans;

	z = fabs(x);
	t = 1.0/(1.0+0.5*z);
	ans = t*exp(-z*z-1.26551223+t*(1.00002368+t*(0.37409196+t*(0.09678418+
	      t*(-0.18628806+t*(0.27886807+t*(-1.13520398+t*(1.48851587+
		  t*(-0.82215223+t*0.17087277)))))))));
	return x >= 0.0 ? ans : 2.0-ans;

}
