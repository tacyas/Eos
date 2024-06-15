/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcRefCorEstimate ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcRefCorEstimate
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcRefCorEstimate ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "mrcRefUtil.h"


typedef struct {
  double peakavr;
  int area8;
  double armax1;
  double armean1;
  double armax2;
  double armean2;
} mrcRefCorOrientedStat;

typedef struct {
  double peakavr;
  mrcRefDegCoordinate maxphi;
} mrcRefCorUnOrientedStat;

typedef struct {
  double maxd;
  double avrd;
} mrcRefCorOrientedDistanceStat;

/* prototype */
void lmrcRefCorOrientedEstimate(mrcRefCorOrientedStat* stat ,mrcImage* in);
void lmrcRefCorOrientedStatDisp(mrcRefCorOrientedStat* stat);
void lmrcRefCorOrientedAroundPeakGet(double* peak,double* max1,double* sum1,int *area1,double* max2,double* sum2,int* area2 ,int x ,mrcImage* in ,mrcRefCorHeader* header );
void lmrcRefCorOrientedDistanceEstimate(mrcRefCorOrientedDistanceStat* stat ,mrcImage* in);
void lmrcRefCorOrientedDistanceDisp(mrcRefCorOrientedDistanceStat* stat);
void lmrcRefCorUnOrientedEstimate(mrcRefCorUnOrientedStat* stat ,mrcImage* in);
void lmrcRefCorUnOrientedStatDisp(mrcRefCorUnOrientedStat* stat);
void lmrcRefCorUnOrientedEstimate(mrcRefCorUnOrientedStat* stat ,mrcImage* in);
void lmrcRefCorUnOrientedStatDisp(mrcRefCorUnOrientedStat* stat);
void lmrcRefCorUnOrientedReverseEstimate(mrcRefCorUnOrientedStat* stat ,mrcImage* in);
void lmrcRefCorMaxFind(int* ymax ,double* datamax, mrcImage* in ,int x ,int mode);
double lDegreeDistanceEstimate(mrcRefDegCoordinate p1 ,mrcRefDegCoordinate w1 ,mrcRefDegCoordinate a1 ,mrcRefDegCoordinate p2, mrcRefDegCoordinate w2 ,mrcRefDegCoordinate a2);


void
main(int argc, char* argv[]) 
{
	long status;
	mrcRefCorEstimateInfo info;

/* variables */
	mrcImage in;
	mrcRefCorOrientedStat oristat;
	mrcRefCorOrientedDistanceStat dstat;
	mrcRefCorUnOrientedStat unoristat;
/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */
	mrcFileRead(&in ,info.In ,"in main" ,0);
	switch (info.mode){
	case 0:
	  lmrcRefCorOrientedEstimate(&oristat ,&in);
	  lmrcRefCorOrientedStatDisp(&oristat);
	  break;
	case 1:
	  lmrcRefCorOrientedDistanceEstimate(&dstat ,&in);
	  lmrcRefCorOrientedDistanceDisp(&dstat);
	  break;
	case 2:
	  lmrcRefCorUnOrientedEstimate(&unoristat ,&in);
	  lmrcRefCorUnOrientedStatDisp(&unoristat);
	  break;
	case 3:
	  lmrcRefCorUnOrientedReverseEstimate(&unoristat ,&in);
	  lmrcRefCorUnOrientedStatDisp(&unoristat);
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
}

void lmrcRefCorOrientedEstimate(mrcRefCorOrientedStat* stat ,mrcImage* in)
{
/* variables */
  mrcRefCorHeader header;

  double peaksum,peak,peak8,arsum1,arsum2,tmpmax1,tmpmax2,tmpsum1,tmpsum2,data;
  int x,y,area1,area2,areasum1,areasum2;

/* initialization */
  lmrcRefCorHeaderGet(&header ,in);
  peaksum = 0.0;
  stat->area8 = 0;
  areasum1 = 0;
  areasum2 = 0;
  arsum1 = 0.0;
  arsum2 = 0.0;
  stat->armax1 = 0.0;
  stat->armax2 = 0.0;

/* begin */
  for (x=0 ;x < in->HeaderN.x ;x++){ 
    lmrcRefCorOrientedAroundPeakGet(&peak,&tmpmax1,&tmpsum1,&area1,&tmpmax2,&tmpsum2,&area2 ,x ,in ,&header );
    areasum1 += area1;
    areasum2 += area2;
    DEBUGPRINT4("%d %d %d %d ",areasum1 ,areasum2 ,area1,area2);
    arsum1 += tmpsum1;
    arsum2 += tmpsum2;
    stat->armax1 = MAX(stat->armax1 ,tmpmax1);
    stat->armax2 = MAX(stat->armax2 ,tmpmax2);
    DEBUGPRINT2("%f %f \n",stat->armax1 ,stat->armax2);
    peaksum += peak;
    peak8 = fabs(peak*0.8);
    for (y=0 ;y < in->HeaderN.y ;y++){
      mrcPixelDataGet(in ,x ,y ,1 ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
      if (fabs(data) > peak8) {
	stat->area8 ++ ;
      }
    }
  }
  stat->peakavr = peaksum / in->HeaderN.x;
  stat->armean1 = arsum1 / areasum1 ;
  stat->armean2 = arsum2 / areasum2 ;
}


void lmrcRefCorOrientedStatDisp(mrcRefCorOrientedStat* stat)
{
  printf("%f %d %f %f %f %f \n",stat->peakavr,stat->area8,stat->armax1,stat->armax2 ,stat->armean1 ,stat->armean2 );
}


void lmrcRefCorOrientedAroundPeakGet(double* peak,double* max1,double* sum1,int *area1,double* max2,double* sum2,int* area2 ,int x ,mrcImage* in ,mrcRefCorHeader* header )
{
/* variables */
  mrcRefDegCoordinate p2,w2,a2,p1,w1,a1,dp,dw,da;
  double data,d;

/* Initialization */
  dp = (header->wp)?(header->dp):0;
  dw = (header->ww)?(header->dw):0;
  da = (header->wa)?(header->da):0;
  *area1 = *area2 = 0;
  *sum1 = *sum2 = *max1 = *max2 = 0.0;  

/* begin */
  lmrcRefCorrelationGetRefxCordinate(&p1,&w1,&a1,x ,in ,header );
  /* When wa = 0 , da = 1 */
  for (a2 = a1 - da*2 ;a2 <= a1 + da*2 ;a2 += header->da){
    for (p2 = p1 - dp*2 ;p2 <= p1 + dp*2 ;p2 += header->dp){
      for (w2 = w1 - dw*2 ;w2 <= w1 + dw*2 ;w2 += header->dw){
	if (p2 > header->ip + header->wp || p2 < header->ip - header->wp ||
	    w2 > header->iw+header->ww || w2 < header->iw-header ->ww ||
	    a2 > header->ia+header->wa || a2 < header->ia-header ->wa ){
	  continue;
	}
	data = lmrcRefCorrelationGet(in ,p1 ,w1 ,a1 ,p2 ,w2, a2 ,header);
	data = fabs(data);
	d = SQR( (a2-a1)/header->da ) + SQR( (p2-p1)/header->dp ) + SQR( (w2-w1)/header->dw );
	if (d > 3) {
	  *area2 += 1;
	  *sum2 += data;
	  *max2 = MAX(*max2 ,data);
	} else if (d == 0) {
	  *peak = data ;
	} else {
	  *area1 += 1;
	  *sum1 += data;
	  *max1 = MAX(*max1 ,data);
	}
/*	DEBUGPRINT7("%f %f %f %d %d %f %f \n ",a2 ,p2 ,w2 ,*area1 ,*area2 ,*sum1 ,*sum2);  */
      }
    }
  }
  *sum1 /= *peak;
  *sum2 /= *peak;
  *max1 /= *peak;
  *max2 /= *peak;
  DEBUGPRINT6("%f %f %f %f %f %f \n",p1,*peak,*sum1,*sum2,*max1,*max2);
}
	  
	
void lmrcRefCorOrientedDistanceEstimate(mrcRefCorOrientedDistanceStat* stat ,mrcImage* in)
{
/* variables */
  mrcRefCorHeader header;
  mrcRefDegCoordinate p1,w1,a1,p2,w2,a2;
  int x,y;
  double data,d,dsum;
  
/* initialization */
  lmrcRefCorHeaderGet(&header ,in);
  stat->maxd = 0;
  dsum=0;

/* begin */
  for (x=0 ;x<in->HeaderN.x ;x++){
    lmrcRefCorrelationGetRefxCordinate(&p1,&w1,&a1,x,in,&header);
    lmrcRefCorMaxFind(&y,&data,in,x,1);
    lmrcRefCorrelationGetRefyCordinate(&p2,&w2,&a2,y,in,&header); 
    DEBUGPRINT2("%f %f ",p1,p2);
    d=lDegreeDistanceEstimate(p1,w1,a1,p2,w2,a2);
    DEBUGPRINT1("%f \n",d);
    dsum += d*d;
    stat->maxd = MAX(stat->maxd,d);
  }
  stat->avrd = sqrt(dsum / in->HeaderN.x);
}

void lmrcRefCorOrientedDistanceDisp(mrcRefCorOrientedDistanceStat* stat)
{
  printf("%f %f \n",stat->avrd,stat->maxd );
}

void lmrcRefCorUnOrientedEstimate(mrcRefCorUnOrientedStat* stat ,mrcImage* in)
{
/* variables */
  mrcRefCorHeader header;
  double sum,maxsum,data;
  int x,flag,dataN;
  mrcRefDegCoordinate dp,p1,p2,w,a,maxp;
/* initialization */
  lmrcRefCorHeaderGet(&header ,in);
  maxsum=0.0;
  maxp=0;

/* begin */
  flag = (header.wp == 180)?(-header.dp):(0);
  for (dp = -header.wp ;dp <= header.ip+header.wp+flag ;dp += header.dp){
    sum = 0.0;
    dataN = 0;
    for (x=0 ;x<in->HeaderN.x ;x++){
      lmrcRefCorrelationGetRefxCordinate(&p1,&w,&a,x,in,&header);
      p2 = p1+dp;
      p2 = NormalDegree(p2);
/*      DEBUGPRINT2("%f %f ",p1,p2) */;
      data = lmrcRefCorrelationGet(in ,p1 ,w ,a ,p2 ,w ,a ,&header);
      if (data != -2){
	dataN += 1;
	sum += data;
      }
      DEBUGPRINT4("%f %f %d %f   ",p1,p2,dataN,data);
    }
/*    DEBUGPRINT6("%f %f %f %f %d %f \n",dp,maxp,sum,maxsum,dataN,data);  */
    sum /= dataN;
    if (maxsum < sum){
      maxsum = sum;
      maxp = dp;
    }
  }
  stat->maxphi = maxp;
  stat->peakavr = maxsum;
}

void lmrcRefCorUnOrientedReverseEstimate(mrcRefCorUnOrientedStat* stat ,mrcImage* in)
{
/* variables */
  mrcRefCorHeader header;
  double sum,maxsum;
  int x,flag;
  mrcRefDegCoordinate dp,p1,p2,w,a,maxp;
/* initialization */
  lmrcRefCorHeaderGet(&header ,in);
  maxsum=0.0;
  maxp=0;

/* begin */
  flag = (header.wp == 180)?(-header.dp):(0);
  for (dp = -header.wp ;dp <= header.ip+header.wp+flag ;dp += header.dp){
    sum = 0.0;
    for (x=0 ;x<in->HeaderN.x ;x++){
      lmrcRefCorrelationGetRefxCordinate(&p1,&w,&a,x,in,&header);
      p2 = -p1+dp;
      p2 = NormalDegree(p2);
/*      DEBUGPRINT2("%f %f ",p1,p2) */;
      sum += lmrcRefCorrelationGet(in ,p1 ,w ,a ,p2 ,w ,a ,&header);
    }
    DEBUGPRINT4("%f %f %f %f \n",dp,maxp,sum,maxsum);  
    if (maxsum < sum){
      maxsum = sum;
      maxp = dp;
    }
  }
  stat->maxphi = maxp;
  stat->peakavr = maxsum / in->HeaderN.x;
}

void lmrcRefCorUnOrientedStatDisp(mrcRefCorUnOrientedStat* stat)
{
  printf("%f %f \n",stat->peakavr,stat->maxphi );
}


void lmrcRefCorMaxFind(int* ymax ,double* datamax, mrcImage* in ,int x ,int mode)
{
/* variables */
  int y;
  double data;

/* begin */
  mrcPixelDataGet(in ,x ,0 ,1 ,datamax ,mrcPixelRePart ,mrcPixelHowNearest);
  *ymax = 0;
  if (mode == 1){
    *datamax = fabs(*datamax);
  }
  for (y=1 ;y < in->HeaderN.y ;y++){
    mrcPixelDataGet(in ,x ,y ,1 ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
    if (mode == 1){
      data = fabs(data);
    }
    if (*datamax < data){
      *datamax = data;
      *ymax = y;
    }
  }
}


double lDegreeDistanceEstimate(mrcRefDegCoordinate p1 ,mrcRefDegCoordinate w1 ,mrcRefDegCoordinate a1 ,mrcRefDegCoordinate p2, mrcRefDegCoordinate w2 ,mrcRefDegCoordinate a2)
{
  double d;
  mrcRefDegCoordinate dp,da,dw;

  dp=NormalDegree(p1-p2);
  da=NormalDegree(a1-a2);
  dw=NormalDegree(w1-w2);
  d=sqrt( SQR((double)dp) +SQR((double)dw) +SQR((double)da) );
  return(d);
}

