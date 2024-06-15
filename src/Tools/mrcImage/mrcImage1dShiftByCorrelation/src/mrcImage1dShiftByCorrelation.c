/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImage1dShiftByCorrelation ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImage1dShiftByCorrelation
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImage1dShiftByCorrelation ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "mrcRefUtil.h"
#include "nr2.h"
#define DEBUG
#include "genUtil.h"

/* prototype */
void lmrcImage1dShiftByCorrelation(float* shift ,float* data,mrcImage* in,mrcImage* ref,int* sigpos ,float* sigval ,int signum ,int range ,float delta ,int mode);
void lmrcImage1dSignalGet(double* rdata, double* idata, mrcImage* in,int signum,int* sigpos,float* sigval);
void lextracteddataShift(double* rout ,double* iout ,double* rdata ,double* idata ,int* sigpos ,int signum ,float shift);
double lmrcImage1dCorrelation(double* inrdata ,double* inidata ,double* refrdata ,double* refidata ,int signum ,int mode);

/* extern */
int ex_N;

int
main(int argc, char* argv[]) 
{
	mrcImage1dShiftByCorrelationInfo info;

/* variables */
	mrcImage in;
	mrcImage ref;
	FILE* fpin;
	FILE* fpsig;
	int filenum,signum;
	int sigpos[100];
	float sigval[100];
	float shift;
	float data;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);
	if((fpin=fopen(info.In,"r"))==NULL){
	  fprintf(stderr ,"File can not be opened.\n");
	  exit(1);
	}
	filenum=0;
	DEBUGPRINT("start1 \n");
	if((fpsig=fopen(info.Signal,"r"))==NULL){
	  fprintf(stderr ,"File can not be opened.\n");
	  exit(1);
	}
	signum=0;
	while(fscanf(fpsig,"%d %g\n",&sigpos[signum],&sigval[signum])!=EOF ){
	  signum++;
	}

	mrcFileRead(&ref ,info.Ref ,"in main" ,0);
	mrcFileRead(&in ,info.In ,"in main" ,0);

	if (info.range==0){
	  info.range = in.HeaderN.x;
	}
/* begin */
	if (info.normalize){
	  lmrcImageZ1Normalization(&in,0);
	  lmrcImageZ1Normalization(&ref,0);
	}
	lmrcImage1dShiftByCorrelation(&shift,&data,&in,&ref,sigpos,sigval,signum,info.range,info.delta,info.mode);
	fprintf(stdout,"%s %s %f %g\n",info.In ,info.Ref ,shift,data);

	return EXIT_SUCCESS;
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "-----  mode -----\n");
	fprintf(stderr, "0:Phase residual\n");
	fprintf(stderr, "1:Normal correlation\n");
}

void lmrcImage1dShiftByCorrelation(float* shift ,float* data,mrcImage* in,mrcImage* ref,int* sigpos ,float* sigval ,int signum ,int range ,float delta ,int mode)
{
/* variables */
  double* inrdata;
  double* inidata;
  double* refrdata;
  double* refidata;
  double* rtemp;
  double* itemp;
  double c;
  int i;

/* initialization */
  DEBUGPRINT("corstart\n");
  if ( ( inrdata = (double*)malloc(sizeof(double)*signum) ) == NULL ){
    fprintf(stderr ,"Enough memoly is not available.");
    exit(EXIT_FAILURE);
  }
  if ( ( inidata = (double*)malloc(sizeof(double)*signum) ) == NULL ){
    fprintf(stderr ,"Enough memoly is not available.");
    exit(EXIT_FAILURE);
  }
  if ( ( refrdata = (double*)malloc(sizeof(double)*signum) ) == NULL ){
    fprintf(stderr ,"Enough memoly is not available.");
    exit(EXIT_FAILURE);
  }
  if ( ( refidata = (double*)malloc(sizeof(double)*signum) ) == NULL ){
    fprintf(stderr ,"Enough memoly is not available.");
    exit(EXIT_FAILURE);
  }
  if ( ( rtemp = (double*)malloc(sizeof(double)*signum) ) == NULL ){
    fprintf(stderr ,"Enough memoly is not available.");
    exit(EXIT_FAILURE);
  }
  if ( ( itemp = (double*)malloc(sizeof(double)*signum) ) == NULL ){
    fprintf(stderr ,"Enough memoly is not available.");
    exit(EXIT_FAILURE);
  }
  lmrcImage1dSignalGet(inrdata,inidata,in,signum,sigpos,sigval);
  lmrcImage1dSignalGet(refrdata,refidata,ref,signum,sigpos,sigval);
  *data=-1e+10;
  ex_N=in->HeaderN.x;
  for (i=0 ;i<range ;i++){
    lextracteddataShift(rtemp ,itemp ,refrdata ,refidata ,sigpos ,signum ,i*delta );
    c=lmrcImage1dCorrelation(inrdata ,inidata ,rtemp ,itemp ,signum ,mode);
    DEBUGPRINT2("%g %g \n",i*delta,c);
    if (c > *data){
      *data=c;
      *shift=i*delta;
    }
  }
  free(inrdata);
  free(inidata);
  free(refrdata);
  free(refidata);
  free(rtemp);
  free(itemp);
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

/* begin */
  N=ex_N;
  for (s=0 ;s<signum ;s++){
    a=2*PI*sigpos[s]*shift/N;
    co=cos(a);
    si=sin(a);
    rout[s]=co*rdata[s]-si*idata[s];
    iout[s]=co*idata[s]+si*rdata[s];
  }
}

double lmrcImage1dCorrelation(double* inrdata ,double* inidata ,double* refrdata ,double* refidata ,int signum ,int mode)
{
/* variables */
  int s;
  double data,sum,f1,f2,f,dp,nr1,nr2,ni1,ni2,dr,di,d,sum2;

/* begin */
  data=0;
  sum=0;
  switch(mode){
  case 0:
    for (s=0 ;s<signum ;s++){
      f1=inrdata[s]*inrdata[s]+inidata[s]*inidata[s];
      f1=sqrt(f1);
      f2=refrdata[s]*refrdata[s]+refidata[s]*refidata[s];
      f2=sqrt(f2);
      f=f1+f2;
      sum += f;
      nr1=inrdata[s]/f1;
      ni1=inidata[s]/f1;
      nr2=refrdata[s]/f2;
      ni2=refidata[s]/f2;
      dr=nr1-nr2;
      di=ni1-ni2;
      d=sqrt(dr*dr+di*di);
      dp=2*asin(d/2);
      data += f*dp*dp;
    }
    data /= sum;
    data = 0 - sqrt(data);
    break;
  case 1:
    sum=0;
    sum2=0;
    for (s=0 ;s<signum ;s++){
      data+=inrdata[s]*refrdata[s]+inidata[s]*refidata[s];
      sum += inrdata[s]*inrdata[s]+inidata[s]*inidata[s];
      sum2 += refrdata[s]*refrdata[s]+refidata[s]*refidata[s];
    }
    data /= sqrt(sum*sum2);
  }
  return(data);
}

