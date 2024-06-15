#define NRANSI
#define TOL 2e-4
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "../inc/mrcImage.h"
#include "Vector.h"
#include "mrcImagefuncmin.h"
#include "nr2.h"
#undef DEBUG
#include "genUtil.h"

#define ITMAX 200

mrcImage* mrcImagePeakFind_in;
int mrcImagePeakFind_mode;

void mrcImagePeakFind(double* maxx ,double* maxy ,double* max ,mrcImage* in ,double ix ,double iy ,int mode )
{
/* variables */
  float* p;
  float** xi;
  int iter;
  float ftol;
  float fc;
  float mrcImagePeakFinddummyfunc(float[] );

/* initialization */
  ftol=1e-7;
  p=vector(1,2);
  xi=matrix(1,2,1,2);
  xi[1][1]=1.0;
  xi[1][2]=0.0;
  xi[2][1]=0.0;
  xi[2][2]=1.0;
  p[1]=ix;
  p[2]=iy;
  mrcImagePeakFind_in=in;  
  mrcImagePeakFind_mode=mode;
/* begin */
  powell(p,xi,2,ftol,&iter,&fc,mrcImagePeakFinddummyfunc );
  if (p[1]<-0.5){
    p[1] += in->HeaderN.x;
  }else if (p[1] > in->HeaderN.x-0.5){
    p[1] -= in->HeaderN.x;
  }
  if (p[2]<-0.5){
    p[2] += in->HeaderN.y;
  }else if (p[2] > in->HeaderN.y-0.5){
    p[2] -= in->HeaderN.y;
  }
  *maxx=p[1];
  *maxy=p[2];
  *max=-fc;
}

float mrcImagePeakFinddummyfunc(float p[])
{
  double data;
  mrcPixelDataGet(mrcImagePeakFind_in ,floor(p[1]+0.5) ,floor(p[2]+0.5) ,0 ,&data ,mrcPixelRePart  ,mrcPixelHowNearest);
  DEBUGPRINT3("%f %f %g  ",p[1],p[2],data);
  if (mrcImagePeakFind_mode){
    return( (float)data);
  }  else {
    return(-(float)data);
  }
}

void powell(float p[], float **xi, int n, float ftol, int *iter, float *fret,float (*func)(float []) )
{
  	void linmin2(float p[], float xi[], int n, float ftol ,float *fret,float (*func)(float []));
	int i,ibig,j;
	float del,fp,fptt,t,*pt,*ptt,*xit;

	DEBUGPRINT("startpow ");
	pt=vector(1,n);
	ptt=vector(1,n);
	xit=vector(1,n);
	DEBUGPRINT("func ");
	*fret=(*func)(p);
	for (j=1;j<=n;j++) pt[j]=p[j];
	for (*iter=1;;++(*iter)) {
		fp=(*fret);
		ibig=0;
		del=0.0;
		for (i=1;i<=n;i++) {
			for (j=1;j<=n;j++) xit[j]=xi[j][i];
			fptt=(*fret);
			linmin2(p,xit,n,ftol ,fret,func );
			if (fabs(fptt-(*fret)) > del) {
				del=fabs(fptt-(*fret));
				ibig=i;
			}
		}
		if (2.0*fabs(fp-(*fret)) <= ftol*(fabs(fp)+fabs(*fret))) {
			free_vector(xit,1,n);
			free_vector(ptt,1,n);
			free_vector(pt,1,n);
			return;
		}
		if (*iter == ITMAX) nrerror("powell exceeding maximum iterations.");
		for (j=1;j<=n;j++) {
			ptt[j]=2.0*p[j]-pt[j];
			xit[j]=p[j]-pt[j];
			pt[j]=p[j];
		}
		fptt=(*func)(ptt);
		if (fptt < fp) {
			t=2.0*(fp-2.0*(*fret)+fptt)*SQR(fp-(*fret)-del)-del*SQR(fp-fptt);
			if (t < 0.0) {
				linmin2(p,xit,n,ftol ,fret,func);
				for (j=1;j<=n;j++) {
					xi[j][ibig]=xi[j][n];
					xi[j][n]=xit[j];
				}
			}
		}
	}
}
#undef ITMAX

int ncom;
float *pcom,*xicom,(*nrfunc)(float []);

void linmin2(float p[], float xi[], int n, float ftol , float *fret, float (*func)(float []))
{
	float brent(float ax, float bx, float cx,
		float (*f)(float), float tol, float *xmin);
	float f1dim(float x);
	void mnbrak(float *ax, float *bx, float *cx, float *fa, float *fb,
		float *fc, float (*func)(float));
	int j;
	float xx,xmin,fx,fb,fa,bx,ax;

	ncom=n;
	pcom=vector(1,n);
	xicom=vector(1,n);
	nrfunc=func;
	for (j=1;j<=n;j++) {
		pcom[j]=p[j];
		xicom[j]=xi[j];
	}
	ax=0.0;
	xx=1.0;

	DEBUGPRINT("\n mnbrak ");
	mnbrak(&ax,&xx,&bx ,&fa,&fx,&fb,f1dim);

	/*	
	DEBUGPRINT6("m  %f %f %f %f %f %f  m ",ax,xx,bx,fa,fx,fb);
	*/
	DEBUGPRINT("brent ");
	*fret=brent(ax,xx,bx,f1dim,ftol,&xmin);
	/*
	DEBUGPRINT4("b %f %f %f %f b ",ax,xx,bx,xmin);
	*/
	for (j=1;j<=n;j++) {
		xi[j] *= xmin;
		p[j] += xi[j];
	}
	free_vector(xicom,1,n);
	free_vector(pcom,1,n);
}
#undef TOL

/*float f1dim(float x)
{
	int j;
	float f,*xt;

	xt=vector(1,ncom);
	for (j=1;j<=ncom;j++) xt[j]=pcom[j]+x*xicom[j];
	/*
	DEBUGPRINT7("dim %f %f %f %f %f %f %f   ",xt[1],xt[2],x,pcom[1],pcom[2],xicom[1],xicom[2]);
	// 
	f=(*nrfunc)(xt);
	free_vector(xt,1,ncom);
	return f;
}*/

#define ITMAX 500
#define CGOLD 0.3819660
#define ZEPS 1.0e-10
#define SHFT(a,b,c,d) (a)=(b);(b)=(c);(c)=(d);

/*
float brent(float ax, float bx, float cx, float (*f)(float), float tol,
	float *xmin)
{
	int iter;
	float a,b,d,etemp,fu,fv,fw,fx,fa,fb,p,q,r,tol1,tol2,u,v,w,x,xm,tol2a,tol2b;
	float e=0.0;

	a=(ax < cx ? ax : cx);
	b=(ax > cx ? ax : cx);
	x=w=v=bx;
	fw=fv=fx=(*f)(x);
	fa=(*f)(ax);
	fb=(*f)(bx);
	for (iter=1;iter<=ITMAX;iter++) {
		xm=0.5*(a+b);
		tol2a=2.0*(tol*(fabs(fx)+fabs(fa))+ZEPS);
		tol2b=2.0*(tol*(fabs(fx)+fabs(fb))+ZEPS);
		tol2 =2.0*(tol1 =tol*(fabs(x) +ZEPS) );
		if (fabs(fx-fa) <= tol2a && fabs(fx-fb) <= tol2b ) {
			*xmin=x;
			return fx;
		}
		if (fabs(e) > tol1) {
			r=(x-w)*(fx-fv);
			q=(x-v)*(fx-fw);
			p=(x-v)*q-(x-w)*r;
			q=2.0*(q-r);
			if (q > 0.0) p = -p;
			q=fabs(q);
			etemp=e;
			e=d;
			if (fabs(p) >= fabs(0.5*q*etemp) || p <= q*(a-x) || p >= q*(b-x))
				d=CGOLD*(e=(x >= xm ? a-x : b-x));
			else {
				d=p/q;
				u=x+d;
				if (u-a < tol2 || b-u < tol2)
					d=SIGN(tol1,xm-x);
			}
		} else {
			d=CGOLD*(e=(x >= xm ? a-x : b-x));
		}
		u=(fabs(d) >= tol1 ? x+d : x+SIGN(tol1,d));
		fu=(*f)(u);
		if (fu <= fx) {
			if (u >= x) {
			  a=x;
			  fa=fx;
			} else {
			  b=x;
			  fb=fx;
			}
			SHFT(v,w,x,u)
			SHFT(fv,fw,fx,fu)
		} else {
			if (u < x) {
			  a=u;
			  fa=fu;
			} else {
			  b=u;
			  fb=fu;
			}
			if (fu <= fw || w == x) {
				v=w;
				w=u;
				fv=fw;
				fw=fu;
			} else if (fu <= fv || v == x || v == w) {
				v=u;
				fv=fu;
			}
		}
	}
	nrerror("Too many iterations in brent");
	*xmin=x;
	return fx;
}
*/
#undef ITMAX
#undef CGOLD
#undef ZEPS
#undef SHFT

#define GOLD 1.618034
#define GLIMIT 2.0
#define TINY 1.0e-20
#define SHFT(a,b,c,d) (a)=(b);(b)=(c);(c)=(d);
/*
void mnbrak(float *ax, float *bx, float *cx, float *fa, float *fb, float *fc,
	float (*func)(float))
{
	float ulim,u,r,q,fu,dum;

	*fa=(*func)(*ax);
	*fb=(*func)(*bx);
	if (*fb > *fa) {
		SHFT(dum,*ax,*bx,dum)
		SHFT(dum,*fb,*fa,dum)
	}
	*cx=(*bx)+GOLD*(*bx-*ax);
	*fc=(*func)(*cx);
	while (*fb > *fc) {
		r=(*bx-*ax)*(*fb-*fc);
		q=(*bx-*cx)*(*fb-*fa);
		u=(*bx)-((*bx-*cx)*q-(*bx-*ax)*r)/
			(2.0*SIGN(FMAX(fabs(q-r),TINY),q-r));
		ulim=(*bx)+GLIMIT*(*cx-*bx);
		if ((*bx-u)*(u-*cx) > 0.0) {
			DEBUGPRINT("func1 ");
			fu=(*func)(u);
			if (fu < *fc) {
				*ax=(*bx);
				*bx=u;
				*fa=(*fb);
				*fb=fu;
				return;
			} else if (fu > *fb) {
				*cx=u;
				*fc=fu;
				return;
			}
			u=(*cx)+GOLD*(*cx-*bx);
			DEBUGPRINT("func2 ");
			fu=(*func)(u);
		} else if ((*cx-u)*(u-ulim) > 0.0) {
			DEBUGPRINT("func3 ");
			fu=(*func)(u);
			if (fu < *fc) {
				SHFT(*bx,*cx,u,*cx+GOLD*(*cx-*bx))
				SHFT(*fb,*fc,fu,(*func)(u))
			}
		} else {
			u=(*cx)+GOLD*(*cx-*bx);
			fu=(*func)(u);
			DEBUGPRINT("func5 ");
		}
		SHFT(*ax,*bx,*cx,u)
		SHFT(*fa,*fb,*fc,fu)
	}
}
*/
#undef GOLD
#undef GLIMIT
#undef TINY
#undef SHFT

#define NR_END 1
#define FREE_ARG char*




