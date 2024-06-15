/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImage1dShiftAverageByAnnealing ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImage1dShiftAverageByAnnealing
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImage1dShiftAverageByAnnealing ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#include "mrcImage.h"
#include "mrcRefUtil.h"
#include "mrcImagefuncmin.h"
#include "nr2.h"
#define DEBUG
#include "genUtil.h"
#include "Random.h"


/* prototype */
void lmrcImage1dShiftAverageByAnnealing(mrcImage* out ,mrcImage* in ,float* shift ,float* max ,int filenum ,int signum ,int* sigpos ,float* sigval ,double tol ,int range ,double delta ,float* temptr ,int giter ,float eps ,int mode);
float mrcImage1dShiftAveragedummyfunc(float* p);
void lmrcImage1dSignalGet(double* rdata, double* idata, mrcImage* in,int signum,int* sigpos,float* sigval);
void lmrcImage1dShiftAdd(mrcImage* out,mrcImage* in,float* shift,int filenum);
void lextracteddataShift(double* rout ,double* iout ,double* rdata ,double* idata ,int* sigpos ,int signum ,float shift);
void lmrcImageShiftTest(mrcImage* out ,mrcImage* in ,int shift);
void amebsa(float **p, float y[], int ndim, float pb[], float *yb, float ftol,
	    float (*funk)(float []), int *iter, float temptr ,float enlarge ,
	    float reduction );
float ran1(long *idum);
int convergencest(float **p, int ndim);
void lmrcImageAnealingStartxiySet(float** xi,float* y,int dim);
void lmrcImageShiftAllSearchNumplus(float* p,int range,int dim);
void lmrcImage1dShiftAllSearch(float* p,float* fc,int dim ,int range ,float (*funk)(float []) );



/* extern */
mrcImage* ex_in;
double ex_range;
int ex_delta;
int ex_signum;
int ex_filenum;
int* ex_sigpos;
int ex_mode;
double** ex_rdata;
double** ex_idata;
float* ex_shift;
long idum;
float tt;

void
main(int argc, char* argv[]) 
{
	mrcImage1dShiftAverageByAnnealingInfo info;

/* variables */
	mrcImage* in;
	mrcImage out;
	FILE* fpin;
	FILE* fpsig;
	char infile[100][256];
	int filenum,signum,i;
	int sigpos[100];
	float sigval[100];
	float* shift;
	float max;
/* input patameters ,file open */
	DEBUGPRINT("start  ");
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);
	if((fpin=fopen(info.In,"r"))==NULL){
	  fprintf(stderr ,"File can not be opened.\n");
	  exit(1);
	}
	filenum=0;
	while(fscanf(fpin,"%s \n",infile[filenum])!=EOF ){
	  filenum++;
	}
	if ( ( in = (mrcImage *)malloc(sizeof(mrcImage)*filenum) ) == NULL ){
	  fprintf(stderr ,"Enough memoly is not available.");
	  exit(EXIT_FAILURE);
	}
	if ( ( shift = (float *)malloc(sizeof(float)*filenum) ) == NULL ){
	  fprintf(stderr ,"Enough memoly is not available.");
	  exit(EXIT_FAILURE);
	}
	for( i=0 ; i<filenum ;i++){
	  mrcFileRead(&in[i] ,infile[i] ,"in main" ,0);
	}
	if (info.range==0){
	  info.range = in[0].HeaderN.x;
	}
	if((fpsig=fopen(info.Signal,"r"))==NULL){
	  fprintf(stderr ,"File can not be opened.\n");
	  exit(1);
	}
	signum=0;
	while(fscanf(fpsig,"%d %g\n",&sigpos[signum],&sigval[signum])!=EOF ){
	  signum++;
	}
/* begin */
	DEBUGPRINT1("%d \n",signum);
	lRandShuffle();
	idum=-rand();
	ex_mode=info.mode2;
	lmrcImage1dShiftAverageByAnnealing(&out ,in ,shift ,&max ,filenum ,signum ,sigpos ,sigval ,info.tol ,info.range,info.delta ,&info.temperature ,info.iter ,info.eps ,info.mode); 
	/*	lmrcImageShiftTest(&out,&in[0],1);  */
	mrcFileWrite(&out ,info.Out ,"in main" ,0);
	fprintf(stdout,"result  ");
	for (i=1 ;i<filenum ;i++){
	  fprintf(stdout,"%d %g ",i,shift[i]);
	}
	fprintf(stdout," %g \n",max);
      	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- mode -----\n");
	fprintf(stderr, "0:All search \n");
	fprintf(stderr, "1:annealing method \n");
	fprintf(stderr, "2:mode 1 and refine by powel.\n");
	fprintf(stderr, "3:mode 1 and refine by annealing.\n");
	fprintf(stderr, "----- mode2 -----\n");
	fprintf(stderr, "0:by amplitude \n");
	fprintf(stderr, "1:by power \n");
	fprintf(stderr, "2:by amplitude using only phase \n");
	fprintf(stderr, "3:by power using only phase \n");
	fprintf(stderr, "4:by amplitude using S/sqrt(S) \n");
	fprintf(stderr, "5:by power using only  S/sqrt(S) \n");
}

void lmrcImageShiftTest(mrcImage* out ,mrcImage* in ,int shift)
{
  mrcImage tmpft,tmpftout;
  int X,N;
  double rdata,idata,a,co,si,rout,iout;

  N=in->HeaderN.x;
  lmrcImageFFT(&tmpft ,in ,0);
  tmpftout.Header=tmpft.Header;
  mrcInit(&tmpftout,0);
  for (X=0 ;X<=in->HeaderN.x/2 ;X++){
    mrcPixelDataGet(&tmpft ,X ,0 ,0 ,&rdata, mrcPixelRePart, mrcPixelHowNearest);
    mrcPixelDataGet(&tmpft ,X ,0 ,0 ,&idata, mrcPixelImPart, mrcPixelHowNearest);
    a=2*PI*X*shift/N;
    co=cos(a);
    si=sin(a);
    rout=co*rdata-si*idata;
    iout=co*idata+si*rdata;
    mrcPixelDataSet(&tmpftout ,X ,0 ,0 ,rout, mrcPixelRePart);
    mrcPixelDataSet(&tmpftout ,X ,0 ,0 ,iout, mrcPixelImPart);
  }
  mrcStatDataSet(&tmpftout ,0);
  lmrcImageFFT(out,&tmpftout,0);
}


void lmrcImage1dShiftAverageByAnnealing(mrcImage* out ,mrcImage* in ,float* shift ,float* max ,int filenum ,int signum ,int* sigpos ,float* sigval ,double tol ,int range ,double delta ,float* temptr ,int giter ,float eps ,int mode)
{
/* variables */
  double** rdata;
  double** idata;
  float* p;
  float** xi;
  float* pb;
  float* y;
  int iter;
  int i,j;
  float fc;
  float fcold;
  float mrcImage1dShiftAveragedummyfunc(float[] );
  float starttemptr;

/* initialization */
  DEBUGPRINT("init ");
  if ( ( rdata = (double** )malloc(sizeof(double*)*filenum) ) == NULL ){
    fprintf(stderr ,"Enough memoly is not available.");
    exit(EXIT_FAILURE);
  }
  if ( ( idata = (double** )malloc(sizeof(double*)*filenum) ) == NULL ){
    fprintf(stderr ,"Enough memoly is not available.");
    exit(EXIT_FAILURE);
  }
  for (i=0 ;i<filenum ;i++){
    if ( ( rdata[i] = (double*)malloc(sizeof(double)*signum) ) == NULL ){
      fprintf(stderr ,"Enough memoly is not available.");
      exit(EXIT_FAILURE);
    }
    if ( ( idata[i] = (double*)malloc(sizeof(double)*signum) ) == NULL ){

      fprintf(stderr ,"Enough memoly is not available.");
      exit(EXIT_FAILURE);
    }
  }
  for (i=0 ;i<filenum ;i++){
    lmrcImage1dSignalGet(rdata[i],idata[i],&in[i],signum,sigpos,sigval);
  }
  ex_in = in;
  ex_range = range;
  ex_delta = delta;
  ex_signum = signum;
  ex_sigpos = sigpos;
  ex_filenum = filenum;
  ex_rdata = rdata;
  ex_idata = idata;
  ex_shift = shift;
  starttemptr=*temptr;

/* begin */
  if (!mode){
    p=vector(1,filenum-1);
    lmrcImage1dShiftAllSearch(p,&fc,filenum-1 ,range ,mrcImage1dShiftAveragedummyfunc);
    for (i=1 ;i<=filenum-1 ;i++){
      shift[i] = floor(p[i] +0.5 )*delta;
    }

  }else{
    DEBUGPRINT1("mode %d\n",mode);
    xi=matrix(1,filenum,1,filenum-1);
    y=vector(1,filenum);
    pb=vector(1,filenum-1);
    DEBUGPRINT("initial\n");
    for (i=1 ;i<=filenum-1 ;i++){
      xi[filenum][i] = floor(ran1(&idum)*(range-1));
    }    
    lmrcImageAnealingStartxiySet(xi,y,filenum);
    DEBUGPRINT("initial end\n");
    iter=0;
    fc=1e+10;
    fcold=0;
    while (iter<=0){
      iter=giter;
      amebsa(xi,y,filenum-1,pb,&fc,tol,mrcImage1dShiftAveragedummyfunc,&iter,*temptr ,1.1 ,0.9);
      *temptr *= (1-eps);
      if (fcold != fc){
	DEBUGPRINT("amebsa ");
	for (i=1 ;i<=ex_filenum-1 ;i++){
	  DEBUGPRINT2("%d %g ",i,pb[i]);
	}
	DEBUGPRINT2("%g %g\n",fc,*temptr);
	fcold=fc;
      }
    }
    if (mode == 1){
      for (i=1 ;i<=filenum-1 ;i++){
	shift[i] = floor(pb[i] +0.5 )*delta;
      }
    } else if (mode == 2){
      p=vector(1,filenum-1);
      for (i=1 ;i<=filenum-1 ;i++){
	for (j=1 ;j<=filenum-1 ;j++){
	  xi[i][j] = (i==j)?(1.0):(0.0);
	}
	p[i]=pb[i];
      }
      powell(p,xi,filenum-1,tol,&iter,&fc,mrcImage1dShiftAveragedummyfunc );
      DEBUGPRINT("powell end\n");
      for (i=1 ;i<=filenum-1 ;i++){
	shift[i] = floor(p[i] +0.5 )*delta;
      }
    } else if (mode == 3){
      for (i=1 ;i<=filenum-1 ;i++){
	xi[filenum][i] = pb[i];
      }    
      lmrcImageAnealingStartxiySet(xi,y,filenum);
      iter=0;
      fcold=fc;
      *temptr=-fc/10;
      while (iter<=0){
	iter=giter;
	amebsa(xi,y,filenum-1,pb,&fc,tol,mrcImage1dShiftAveragedummyfunc,&iter,*temptr ,1.1 ,0.9);
	*temptr *= (1-eps);
	if (fcold != fc){
	  DEBUGPRINT("amebsa ");
	  for (i=1 ;i<=ex_filenum-1 ;i++){
	    DEBUGPRINT2("%d %g ",i,pb[i]);
	  }
	  DEBUGPRINT2("%g %g\n",fc,*temptr);
	  fcold=fc;
	}
      }
       for (i=1 ;i<=filenum-1 ;i++){
	shift[i] = floor(pb[i] +0.5 )*delta;
      }
    } 
  }
  *max=-fc;
  lmrcImage1dShiftAdd(out,in,shift,filenum);
}

void lmrcImage1dShiftAllSearch(float* p,float* fc,int dim ,int range ,float (*funk)(float []) )
{
  long N;
  long i,j;
  float data;
  float* pb;

  pb=vector(1,dim);
  for (i=1;i<=dim;i++){
    p[i]=0;
  }
  *fc=1e+10;
  N=pow(range,dim);
  DEBUGPRINT1("N=%d \n",N);
  for (i=1;i<=N;i++){
    data=(*funk)(p);
    if (data < *fc){
      *fc=data;
      for (j=1;j<=dim;j++){
	pb[j]=p[j];
      }
    }
    lmrcImageShiftAllSearchNumplus(p,range,dim);
  }
  for (j=1;j<=dim;j++){
    p[j]=pb[j];
  }
}

void lmrcImageShiftAllSearchNumplus(float* p,int range,int dim)
{
  int i;

  i=dim;
  p[i] += 1;
  if (p[i] > range-0.5){
    while (p[i] > range-0.5 ){
      p[i]=0;
      i -= 1;
      p[i] += 1;
      if (i==0) return;
      if (i==1) DEBUGPRINT1("%f ",p[i]);
    }    
  }
}

void lmrcImageAnealingStartxiySet(float** xi,float* y,int dim)
{
  int i,j;

  for (i=1 ;i<=dim-1 ;i++){
    if (xi[dim][i] >= ex_range-0.5){
    xi[dim][i] -= 1;
    }
  }
  for (i=1 ;i<=dim-1 ;i++){
    for (j=1 ;j<=dim-1 ;j++){
      xi[i][j] = (i==j)?(1.0):(0.0) ;
      xi[i][j] += xi[dim][j];
    }
  }    
  for (i=1 ;i<=dim ;i++){
    for (j=1 ;j<=dim-1 ;j++){
      DEBUGPRINT3("%d %d %g\n",i,j,xi[i][j]);
    }
  }
  DEBUGPRINT("read \n");
  for (i=1 ;i<=dim ;i++){
    DEBUGPRINT1("%d  ",i);
    for (j=1 ;j<=dim-1 ;j++){
      DEBUGPRINT3("%d %d %g\n",i,j,xi[i][j]);
    }
    y[i] = mrcImage1dShiftAveragedummyfunc(xi[i] );
  }
}



float mrcImage1dShiftAveragedummyfunc(float* p)
{
/* variables */
  int f,s;
  double mag;
  double* rsum;
  double* isum; 
  double* rtmp;
  double* itmp;
  double d;
  if ( ( rsum = (double *)malloc(sizeof(double)*ex_signum) ) == NULL ){
    fprintf(stderr ,"Enough memoly is not available.");
    exit(EXIT_FAILURE);
  }
  if ( ( isum = (double *)malloc(sizeof(double)*ex_signum) ) == NULL ){
    fprintf(stderr ,"Enough memoly is not available.");
    exit(EXIT_FAILURE);
  }
  if ( ( rtmp = (double *)malloc(sizeof(double)*ex_signum) ) == NULL ){
    fprintf(stderr ,"Enough memoly is not available.");
    exit(EXIT_FAILURE);
  }
  if ( ( itmp = (double *)malloc(sizeof(double)*ex_signum) ) == NULL ){
    fprintf(stderr ,"Enough memoly is not available.");
    exit(EXIT_FAILURE);
  }
  mag = 0.0;

/* begin */
  for (s=0 ;s<ex_signum ;s++){
    switch (ex_mode) {
    case 0:
    case 1:
      /*      DEBUGPRINT3("%d %f %f \n",s,ex_rdata[0][s],ex_idata[0][s]);  */
      rsum[s]=ex_rdata[0][s];
      isum[s]=ex_idata[0][s];
      /*      DEBUGPRINT3("%d %f %f \n",s,rsum[s],isum[s]);   */
      break;
    case 2:
    case 3:
      d=sqrt(ex_rdata[0][s]*ex_rdata[0][s]+ex_idata[0][s]*ex_idata[0][s]);
      rsum[s]=ex_rdata[0][s]/d;
      isum[s]=ex_idata[0][s]/d;
      break;
    case 4:
    case 5:
      d=sqrt(sqrt(ex_rdata[0][s]*ex_rdata[0][s]+ex_idata[0][s]*ex_idata[0][s]));
      rsum[s]=ex_rdata[0][s]/d;
      isum[s]=ex_idata[0][s]/d;
    }
  }
  for (f=1 ;f<ex_filenum ;f++){
    if (p[f]<=-0.5){
      p[f] = 0.0;
    }
    if (p[f]>ex_range-0.5){
      p[f] = ex_range-1;
    }
    ex_shift[f] = floor(p[f]+0.5) * ex_delta;
    lextracteddataShift(rtmp ,itmp ,ex_rdata[f] ,ex_idata[f] ,ex_sigpos ,ex_signum ,ex_shift[f] );
    for (s=0 ;s<ex_signum ;s++){
      switch (ex_mode) {
      case 0:
      case 1:
	rsum[s]+=rtmp[s];
	isum[s]+=itmp[s];
	break;
      case 2:
      case 3:
	d=sqrt(rtmp[s]*rtmp[s]+itmp[s]*itmp[s]);
	rsum[s]+=rtmp[s]/d;
	isum[s]+=itmp[s]/d;
	break;
      case 4:
      case 5:
	d=sqrt(sqrt(rtmp[s]*rtmp[s]+itmp[s]*itmp[s]));
	rsum[s]+=rtmp[s]/d;
	isum[s]+=itmp[s]/d;
      }
    }
  }
  for (s=0 ;s<ex_signum ;s++){
    if (ex_mode%2){
      mag += rsum[s]*rsum[s] + isum[s]*isum[s];
    } else {
      mag += sqrt(rsum[s]*rsum[s] + isum[s]*isum[s]);
    }      
  }

  free(rsum);
  free(isum);
  free(rtmp);
  free(itmp);
  return(-mag);
}


void lmrcImage1dSignalGet(double* rdata, double* idata, mrcImage* in,int signum,int* sigpos,float* sigval)
{
/* variables */
  int i;
  mrcImage tmpfft;

/* begin */
  lmrcImageFFT(&tmpfft ,in ,0);
  for (i=0 ;i<signum ;i++){
    mrcPixelDataGet(&tmpfft ,sigpos[i] ,0 ,0 ,&rdata[i], mrcPixelRePart, mrcPixelHowNearest);
    rdata[i] *= sigval[i];
    mrcPixelDataGet(&tmpfft ,sigpos[i] ,0 ,0 ,&idata[i], mrcPixelImPart, mrcPixelHowNearest);
    idata[i] *= sigval[i];
  }
}


void lextracteddataShift(double* rout ,double* iout ,double* rdata ,double* idata ,int* sigpos ,int signum ,float shift)
{
/* variables */
  int s,N;
  double si,co,a;

  N=ex_in[0].HeaderN.x;

/* begin */
  
  for (s=0 ;s<signum ;s++){
    a=2*PI*sigpos[s]*shift/N;
    co=cos(a);
    si=sin(a);
    rout[s]=co*rdata[s]-si*idata[s];
    iout[s]=co*idata[s]+si*rdata[s];
  }
}

void lmrcImage1dShiftAdd(mrcImage* out,mrcImage* in,float* shift,int filenum)
{
/* variables */
  mrcImageParaTypeRealCoord tmpshift;
  int f;
  mrcImage tmp;

/* begin */
  out->Header = in[0].Header;
  mrcInit(out,0);
  tmpshift.x=0;
  tmpshift.y=0;
  tmpshift.z=0;
  lmrcImageShift(out ,&in[0] ,tmpshift ,mrcPixelHowNearest);
  for(f=1 ;f<filenum ;f++){
    tmpshift.x=shift[f];
    tmpshift.y=0;
    tmpshift.z=0;
    lmrcImageShift(&tmp ,&in[f] ,tmpshift ,mrcPixelHowNearest);
    llmrcImageAdd(out,&tmp);
  }
}


#define GET_PSUM \
  for (n=1;n<=ndim;n++) {\
    for (sum=0.0,m=1;m<=mpts;m++) sum += p[m][n];\
    psum[n]=sum;}



void amebsa(float **p, float y[], int ndim, float pb[], float *yb, float ftol,
	    float (*funk)(float []), int *iter, float temptr ,float enlarge ,
	    float reduction )
{
	float amotsa(float **p, float y[], float psum[], int ndim, float pb[],
		float *yb, float (*funk)(float []), int ihi, float *yhi, float fac);
	float ran1(long *idum);
	int i,ihi,ilo,j,m,n,mpts=ndim+1;
	float rtol,sum,swap,yhi,ylo,ynhi,ysave,yt,ytry,*psum;

	psum=vector(1,ndim);
	tt = -temptr;
	GET_PSUM
	for (;;) {
	  ilo=1;
	  ihi=2;
	  ynhi=ylo=y[1]+tt*log(ran1(&idum));
	  yhi=y[2]+tt*log(ran1(&idum));
	  if (ylo > yhi) {
	    ihi=1;
	    ilo=2;
	    ynhi=yhi;
	    yhi=ylo;
	    ylo=ynhi;
	  }
	  for (i=3;i<=mpts;i++) {
	    yt=y[i]+tt*log(ran1(&idum));
	    if (yt <= ylo) {
	      ilo=i;
	      ylo=yt;
	    }
	    if (yt > yhi) {
	      ynhi=yhi;
	      ihi=i;
	      yhi=yt;
	    } else if (yt > ynhi) {
	      ynhi=yt;
	    }
	  }
	  rtol=2.0*fabs(yhi-ylo)/(fabs(yhi)+fabs(ylo)); 
	  if (rtol < ftol || *iter < 0) {      
     /*	  if ( convergencest(p, ndim) || *iter < 0) { */ 
	    swap=y[1];
	    y[1]=y[ilo];
	    y[ilo]=swap;
	    for (n=1;n<=ndim;n++) {
	      swap=p[1][n];
	      p[1][n]=p[ilo][n];
	      p[ilo][n]=swap;
	    }
	    break;
	  }
	  *iter -= 2;
	  ytry=amotsa(p,y,psum,ndim,pb,yb,funk,ihi,&yhi,-1.0);
	  if (ytry <= ylo) {
	    ytry=amotsa(p,y,psum,ndim,pb,yb,funk,ihi,&yhi,enlarge);
	  } else if (ytry >= ynhi) {
	    ysave=yhi;
	    ytry=amotsa(p,y,psum,ndim,pb,yb,funk,ihi,&yhi,reduction);
	    if (ytry >= ysave) {
	      for (i=1;i<=mpts;i++) {
		if (i != ilo) {
		  for (j=1;j<=ndim;j++) {
		    psum[j]=0.5*(p[i][j]+p[ilo][j]);
		    p[i][j]=psum[j];
		  }
		  y[i]=(*funk)(psum);
		}
	      }
	      *iter -= ndim;
	      GET_PSUM
		}
	  } else ++(*iter);
	}
	free_vector(psum,1,ndim);
}
#undef GET_PSUM

float amotsa(float **p, float y[], float psum[], int ndim, float pb[],
	float *yb, float (*funk)(float []), int ihi, float *yhi, float fac)
{
	float ran1(long *idum);
	int j;
	float fac1,fac2,yflu,ytry,*ptry;

	ptry=vector(1,ndim);
	fac1=(1.0-fac)/ndim;
	fac2=fac1-fac;
	for (j=1;j<=ndim;j++)
		ptry[j]=psum[j]*fac1-p[ihi][j]*fac2;
	ytry=(*funk)(ptry);
	if (ytry <= *yb) {
		for (j=1;j<=ndim;j++) pb[j]=ptry[j];
		*yb=ytry;
	}
	yflu=ytry-tt*log(ran1(&idum));
	if (yflu < *yhi) {
		y[ihi]=ytry;
		*yhi=yflu;
		for (j=1;j<=ndim;j++) {
			psum[j] += ptry[j]-p[ihi][j];
			p[ihi][j]=ptry[j];
		}
	}
	free_vector(ptry,1,ndim); 	
	return yflu;
}


#define IA 16807
#define IM 2147483647
#define AM (1.0/IM)
#define IQ 127773
#define IR 2836
#define NTAB 32
#define NDIV (1+(IM-1)/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)

float ran1(long *idum)
{
	int j;
	long k;
	static long iy=0;
	static long iv[NTAB];
	float temp;

	if (*idum <= 0 || !iy) {
		if (-(*idum) < 1) *idum=1;
		else *idum = -(*idum);
		for (j=NTAB+7;j>=0;j--) {
			k=(*idum)/IQ;
			*idum=IA*(*idum-k*IQ)-IR*k;
			if (*idum < 0) *idum += IM;
			if (j < NTAB) iv[j] = *idum;
		}
		iy=iv[0];
	}
	k=(*idum)/IQ;
	*idum=IA*(*idum-k*IQ)-IR*k;
	if (*idum < 0) *idum += IM;
	j=iy/NDIV;
	iy=iv[j];
	iv[j] = *idum;
	if ((temp=AM*iy) > RNMX) return RNMX;
	else return temp;
}
#undef IA
#undef IM
#undef AM
#undef IQ
#undef IR
#undef NTAB
#undef NDIV
#undef EPS
#undef RNMX

int convergencest(float **p, int ndim)
{
  int n,m,flag;
  float* pi;
  
  flag=0;
  pi=vector(1,ndim);
  for (m=1;m<=ndim ;m++){
    pi[m]=floor(p[1][m]+0.5);
    DEBUGPRINT1("%f ",pi[m] );
  }
  DEBUGPRINT("\n" );
  for (n=2;n<=ndim+1 ;n++){
    for (m=1;m<=ndim ;m++){
      if (pi[m] != floor(p[n][m]+0.5) ) {
	DEBUGPRINT1("%f ",floor(p[n][m]+0.5) );
	flag=1;
	break;
      }
    }
    if (flag) break;
  }
  free_vector(pi,1,ndim);
  return(flag);
}

    
