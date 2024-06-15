/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageFilteringbyFile ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageFilteringbyFile
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageFilteringbyFile ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"

/* prototypes */
void lmrcImageFilteringbyFile(mrcImage* out ,mrcImage* in ,double** filterval ,int mode);
double lmrcImageFilteringbyArray(double X ,double Y ,double Z ,double** filterval ,int mode);
void lmrcImageMakeFilterFromFile(mrcImage* out ,mrcImage* in ,double** filterval ,int mode);

void
main(int argc, char* argv[]) 
{
	mrcImageFilteringbyFileInfo info;

/* variables */
	mrcImage in;
	mrcImage out;
	FILE* fpfilter;
	double** filterval;
	int filternum,i;
	double dummy;

/* input patameters ,file open */
	DEBUGPRINT("Program Start\n");
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);
	mrcFileRead(&in ,info.In ,"in main" ,0);
	if((fpfilter=fopen(info.Filter,"r"))==NULL){
	  fprintf(stderr ,"File can not be opened.\n");
	  exit(1);
	}
	filternum=0;
	while(fscanf(fpfilter,"%lf %lf \n",&dummy,&dummy )!=EOF ){
	  filternum++;
	}
	if ( ( filterval = (double** )malloc(sizeof(double*)*(filternum+1)) ) == NULL ){
	  fprintf(stderr ,"Enough memoly is not available.");
	  exit(EXIT_FAILURE);
	}
	for (i=0 ; i<=filternum ;i++){
	  if ( ( filterval[i] = (double* )malloc(sizeof(double)*2) ) == NULL ){
	    fprintf(stderr ,"Enough memoly is not available.");
	    exit(EXIT_FAILURE);
	  }
	} 
	filternum=0;
	fclose(fpfilter);
	if((fpfilter=fopen(info.Filter,"r"))==NULL){
	  fprintf(stderr ,"File can not be opened.\n");
	  exit(1);
	}
	while(fscanf(fpfilter,"%lf %lf \n",&filterval[filternum][0],&filterval[filternum][1] )!=EOF ){
	  filternum++;
	}
	filterval[filternum][0] = -1;
	
	if (info.mode==0){
	  lmrcImageFilteringbyFile(&out ,&in ,filterval ,0); 
	}else {
	  lmrcImageMakeFilterFromFile(&out ,&in ,filterval ,0);
	}
	mrcFileWrite(&out ,info.Out ,"in main" ,0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "Mode 0: Filtering input file by filter file.\n");
	fprintf(stderr, "Mode 1: Output mrc fourier image of filter file.Size of filter is size of input file.\n");
}

void lmrcImageFilteringbyFile(mrcImage* out ,mrcImage* in ,double** filterval ,int mode)
{
/* variables */
  mrcImage infft,outfft;
  int X,Y,Z;
  double rdata,idata,e,Lx,Ly,Lz,Fx,Fy,Fz;

/* begin */
  lmrcImageFFT(&infft,in,0);
  outfft.Header = infft.Header;
  mrcInit(&outfft,0);
  Lx = infft.HeaderLength.x * infft.HeaderN.x;
  Ly = infft.HeaderLength.y * infft.HeaderN.y;
  Lz = infft.HeaderLength.z * infft.HeaderN.z;
  Fx = 1 / Lx;
  Fy = 1 / Ly;
  Fz = 1 / Lz;
  for(Z = -infft.HeaderN.z / 2.0; Z < infft.HeaderN.z / 2.0; Z += 1){
    DEBUGPRINT1("Z %d \n",Z);
    for(Y = -infft.HeaderN.y / 2.0; Y < infft.HeaderN.y / 2.0; Y += 1){
      DEBUGPRINT1("Y %d \n",Y);
      for(X = 0; X <= infft.HeaderN.x / 2.0; X += 1){
	DEBUGPRINT1("%d ",X);
	mrcPixelDataGet(&infft, X, Y, Z, &rdata, mrcPixelRePart, mrcPixelHowNearest);
	mrcPixelDataGet(&infft, X, Y, Z, &idata, mrcPixelImPart, mrcPixelHowNearest);
	e = lmrcImageFilteringbyArray(Fx*X ,Fy*Y ,Fz*Z ,filterval ,mode);
	mrcPixelDataSet(&outfft, X, Y, Z, rdata*e, mrcPixelRePart);
	mrcPixelDataSet(&outfft, X, Y, Z, idata*e, mrcPixelImPart);
	DEBUGPRINT5("%f %f %f %f %f\n",e,rdata ,rdata*e,idata, idata*e);
      }
    }
  }
  mrcStatDataSet(&outfft,0);
  lmrcImageFFT(out,&outfft,0);
}

void lmrcImageMakeFilterFromFile(mrcImage* out ,mrcImage* in ,double** filterval ,int mode)
{
/* variables */
  mrcImage infft;
  int X,Y,Z;
  double e,Lx,Ly,Lz,Fx,Fy,Fz;

/* begin */
  lmrcImageFFT(&infft,in,0);
  out->Header = infft.Header;
  mrcInit(out,0);
  Lx = infft.HeaderLength.x * infft.HeaderN.x;
  Ly = infft.HeaderLength.y * infft.HeaderN.y;
  Lz = infft.HeaderLength.z * infft.HeaderN.z;
  Fx = 1 / Lx;
  Fy = 1 / Ly;
  Fz = 1 / Lz;
  for(Z = -infft.HeaderN.z / 2.0; Z < infft.HeaderN.z / 2.0; Z += 1){
    DEBUGPRINT1("Z %d \n",Z);
    for(Y = -infft.HeaderN.y / 2.0; Y < infft.HeaderN.y / 2.0; Y += 1){
      DEBUGPRINT1("Y %d \n",Y);
      for(X = 0; X <= infft.HeaderN.x / 2.0; X += 1){
	DEBUGPRINT1("%d ",X);
	e = lmrcImageFilteringbyArray(Fx*X ,Fy*Y ,Fz*Z ,filterval ,mode);
	mrcPixelDataSet(out, X, Y, Z, e, mrcPixelRePart);
	mrcPixelDataSet(out, X, Y, Z, 0, mrcPixelImPart);
	DEBUGPRINT5("%f %f %f %f %f\n",e,rdata ,rdata*e,idata, idata*e);
      }
    }
  }
  mrcStatDataSet(out,0);
}
  
double lmrcImageFilteringbyArray(double X ,double Y ,double Z ,double** filterval ,int mode)
{
/* variables */
  double R,data,d;
  int i;

/* begin */  
  R=X*X+Y*Y+Z*Z;
  if (R > 1e-10){
    R=sqrt(R);
  }
  DEBUGPRINT1("%f ",R);
  i=0;
  data=0;
  while (R>=filterval[i][0] && filterval[i][0] != -1 ){
    i++;
  }
  if (filterval[i][0] == -1){
    fprintf(stderr ,"Data range of R is too short! Data for R=%g does not exist!" ,R);
    exit(1);
  }
  d=filterval[i][0]-filterval[i-1][0];
  DEBUGPRINT1("%f ",d);
  data = (filterval[i][0]-R)/d*filterval[i-1][1];
  data += (R-filterval[i-1][0])/d*filterval[i][1];
  DEBUGPRINT1("%f ",data);
  return(data);
}







