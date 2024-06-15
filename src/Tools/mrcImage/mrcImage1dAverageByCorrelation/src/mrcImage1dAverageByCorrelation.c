/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImage1dAverageByCorrelation ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImage1dAverageByCorrelation
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImage1dAverageByCorrelation ver%I%; Date:%D% %Z%";
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

/* prototype */
void lmrcImage1dAverageByCorrelation(mrcImage* out ,mrcImage* in ,int* shift ,double* summax ,int num ,double tol ,int range ,int mode);
void mrcImageAddByCorrelation(mrcImage* in1 ,mrcImage* in2 ,int* shift ,double* max ,int num ,int range ,int mode);
void lmrcImage1dmaxFind(double* max ,int* maxx ,mrcImage* in ,int shift ,int range);
int lgetx(int x ,mrcImage* in);

void
main(int argc, char* argv[]) 
{
	long status;
	mrcImage1dAverageByCorrelationInfo info;

/* variables */
	mrcImage* in;
	mrcImage out;
	FILE* fpin;
	char infile[100][256];
	int line,i;
	int* shift;
	double max;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);
	if((fpin=fopen(info.In,"r"))==NULL){
	  fprintf(stderr ,"File can not be opened.\n");
	  exit(1);
	}
	line=0;
	while(fscanf(fpin,"%s \n",infile[line])!=EOF ){
	  line++;
	}
	if ( ( in = (mrcImage *)malloc(sizeof(mrcImage)*line) ) == NULL ){
	  fprintf(stderr ,"Enough memoly is not available.");
	  exit(EXIT_FAILURE);
	}
	if ( ( shift = (int *)malloc(sizeof(int)*line) ) == NULL ){
	  fprintf(stderr ,"Enough memoly is not available.");
	  exit(EXIT_FAILURE);
	}
	
	for( i=0 ; i<line ;i++){
	  mrcFileRead(&in[i] ,infile[i] ,"in main" ,0);
	  shift[i]=0;
	}
	if (info.range==0){
	  info.range = in[0].HeaderN.x;
	}
/* begin */
	lmrcImage1dAverageByCorrelation(&out ,in ,shift ,&max ,line ,1e-6 ,info.range ,0);  
 	mrcFileWrite(&out ,info.Out ,"in main" ,0); 
	fprintf(stdout ,"%f ",max ); 
	for(i=0;i<line;i++){
	  fprintf(stdout ,"%d ",shift[i] );
	}
	fprintf(stdout ,"\n" );
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
}

void lmrcImage1dAverageByCorrelation(mrcImage* out ,mrcImage* in ,int* shift ,double* summax ,int num ,double tol ,int range ,int mode)
{
/* variables */
  int i;
  mrcImage sum,tmp;
  double max,oldsummax;
  mrcImageParaTypeRealCoord to;

/* initialization */
  out->Header = sum.Header = in[0].Header;
  mrcInit(out,NULL);
  mrcInit(&sum,NULL);
  to.x=to.y=to.z=0;

/* begin */
  DEBUGPRINT("start ");

  lmrcImageCopy(&sum,&in[0],to);
  DEBUGPRINT("sum ");
  oldsummax=0;
  for (i=1 ;i<num ;i++){
    DEBUGPRINT1("%d ",i);
    mrcImageAddByCorrelation(&sum ,&in[i] ,shift ,&max ,i ,range ,0);
    oldsummax += max;
  }
  DEBUGPRINT1("%f ",oldsummax);
  for(i=0;i<num;i++){
    DEBUGPRINT1("%d ",shift[i] );
  }

  *summax=0;
  while(fabs(*summax-oldsummax)/oldsummax > tol){
    oldsummax=*summax;
    *summax=0;
    DEBUGPRINT("start ");
    for (i=0 ;i<num ;i++){
      llmrcImageSub(&tmp ,&sum ,&in[i] );
      DEBUGPRINT("add ");
      mrcImageAddByCorrelation(&tmp ,&in[i] ,shift ,&max ,i ,range ,0);
      DEBUGPRINT2("%d max %f  ",i,max); 
      lmrcImageCopy(&sum,&tmp,to);
      mrcImageFree(&tmp,0);
      *summax += max;
    }
    for(i=0;i<num;i++){
      DEBUGPRINT1("%d ",shift[i] );
    }
    DEBUGPRINT1("%f\n",*summax );
  }
  DEBUGPRINT("end \n ");
  lmrcImageCopy(out,&sum,to);
  mrcStatDataSet(out,0);
}


void mrcImageAddByCorrelation(mrcImage* in1 ,mrcImage* in2 ,int* shift ,double* max ,int num ,int range ,int mode)
{
/* variables */
  mrcImage cor,tmp;
  int x;
  mrcImageParaTypeRealCoord tmpshift;

/* begin */
  lmrcImageCorrelation(&cor ,in1 ,in2 ,0);
  lmrcImage1dmaxFind(max,&x,&cor,shift[num] ,range);
  mrcImageFree(&cor,0);
/*  DEBUGPRINT1("s:%d ",x); */
  shift[num] += x;
  tmpshift.x=x;
  tmpshift.y=0;
  tmpshift.z=0;
  lmrcImageShift(&tmp ,in2 ,tmpshift ,mrcPixelHowNearest);
  *in2=tmp;
  llmrcImageAdd(in1 ,in2);
}


void lmrcImage1dmaxFind(double* max ,int* maxx ,mrcImage* in ,int shift ,int range)
{
/* variables */
  int x;
  double data;

/* begin */
  *maxx=0;
  mrcPixelDataGet(in ,0 ,0 ,0 ,max ,mrcPixelRePart ,mrcPixelHowNearest);
  for(x=-shift ;x < -shift+range ;x++){
    mrcPixelDataGet(in ,lgetx(x,in) ,0 ,0 ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
    if (data > *max){
      *max = data;
      *maxx = x;
    }
  }
}

int lgetx(int x ,mrcImage* in)
{
  if (x<0) {
    return(in->HeaderN.x + x);
  } else if (x > in->HeaderN.x){
    return(x-(x/in->HeaderN.x)*in->HeaderN.x );
  } else {
    return(x);
  }
}
  







