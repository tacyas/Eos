/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcRefImagepwzCorEstimate ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcRefImagepwzCorEstimate
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcRefImagepwzCorEstimate ver%I%; Date:%D% %Z%";
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
#include "mrcImagefuncmin.h"
#define DAERROR 15
#define DYERROR 3

int ex_y;
mrcImage* ex_in;
mrcRefHeader ex_inheader;

/* prototype */
void lmrcRefImagepwzCorMaxxGet(double* data ,double* maxx ,mrcImage* in);
void lmrcRefImagepwzCorMaxxDisp(double* data ,double* maxx , int size);
void lmrcRefImagepwzCorMaxxdataMrcImageGet(double* data ,mrcImage* in );
void lmrcRefImagepwzCorMaxxdataMrcImageSet(mrcImage* out ,double* data ,mrcImage* in );
void lmrcRefImagepwzCory1MaxFind(double* data ,double* maxx ,mrcImage* in ,int y ,int mode);

double NormalDegree2(double p);

void
main(int argc, char* argv[]) 
{
	long status;
	mrcRefImagepwzCorEstimateInfo info;
/* variables */
	mrcImage in,out;
	double* data;
	double* maxx;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);
	
/* begin */
	mrcFileRead(&in ,info.In ,"in main" ,0);
	if ( ( data = (double *)malloc(sizeof(double)*in.HeaderN.y) ) == NULL ) {
	  fprintf(stderr ,"Enough memoly is not available.");
	  exit(EXIT_FAILURE);
	}
	if ( ( maxx = (double *)malloc(sizeof(double)*in.HeaderN.y) ) == NULL ) {
	  fprintf(stderr ,"Enough memoly is not available.");
	  exit(EXIT_FAILURE);
	}
	
	lmrcRefImagepwzCorMaxxGet(data ,maxx ,&in);
	switch (info.mode){
	case 0:
	    lmrcRefImagepwzCorMaxxDisp(data ,maxx ,in.HeaderN.y); 
	    break;
	case 1:
	    lmrcRefImagepwzCorMaxxdataMrcImageSet(&out ,data ,&in );
	    mrcFileWrite(&out ,info.Out ,"in main" ,0);
    	}
	exit(EXIT_SUCCESS);
}


void
additionalUsage()
{
fprintf(stdout,"----- mode ----- \n");
fprintf(stdout,"0:Output is stdout \n");
fprintf(stdout,"1:Output is mrcfile \n");
}


void lmrcRefImagepwzCorMaxxGet(double* data ,double* maxx ,mrcImage* in)
{
/* variables */
  int y;

/* begin */
  for (y=0 ;y < in->HeaderN.y ;y++){
    lmrcRefImagepwzCory1MaxFind(data ,maxx ,in ,y , 0);
  }
}

void lmrcRefImagepwzCorMaxxDisp(double* data ,double* maxx ,int size)
{
/* variables */
  int y;

/* begin */
  for (y=0 ;y < size ;y++){
    fprintf(stdout ,"%d %g %g \n" ,y,data[y],maxx[y] );
  }
}



void lmrcRefImagepwzCory1MaxFind(double* data ,double* maxx ,mrcImage* in ,int y ,int mode)
{
/* variables */
  int x;
  double tmp,max;

/* begin */
  maxx[y] = 0.0;
  mrcPixelDataGet(in ,0 ,y ,1 ,&max ,mrcPixelRePart ,mrcPixelHowNearest);
  if (mode == 1){
    max = fabs(max);
  }
  for (x=1 ;x < in->HeaderN.x ;x++){
    mrcPixelDataGet(in ,x ,y ,1 ,&tmp ,mrcPixelRePart ,mrcPixelHowNearest);
    if (mode == 1){
      tmp = fabs(tmp);
    }
    if (tmp > max){
      max = tmp;
      maxx[y] = x; 
    }
  }
  data[y]=max;
 
}




void lmrcRefImagepwzCorMaxxdataMrcImageSet(mrcImage* out ,double* data ,mrcImage* in )
{
/* variables */
  int y;
/* initialization */
  out->Header = in->Header;
  out->HeaderN.x = in->HeaderN.y;
  out->HeaderN.y = 2;
  out->HeaderN.z = 1;
  mrcInit(out ,NULL);
  
/* begin */
  for (y=0 ;y < in->HeaderN.y ;y++){
    mrcPixelDataSet(out ,y ,0 ,0 ,data[y] ,mrcPixelRePart);
    mrcPixelDataSet(out ,y ,1 ,0 ,data[y] ,mrcPixelRePart);
  }
  mrcStatDataSet(out,0);
}

void lmrcRefImagepwzCorMaxxdataMrcImageGet(double* data ,mrcImage* in )
{
/* variables */
  int y;
  double tmp;
/* begin */
  for (y=0 ;y < in->HeaderN.x ;y++){
    mrcPixelDataGet(in ,y ,0 ,0 ,&tmp ,mrcPixelRePart ,mrcPixelHowNearest);
    data[y]=tmp;
  }
}

