/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImage3DHighResoEmphasis ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImage3DHighResoEmphasis
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImage3DHighResoEmphasis ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"

/* prototypes */
double lmrcImage3DHighResoEmphasisFunction(double X ,double Y ,double Z ,double High ,double Low ,double A ,double B);
void lmrcImage3DHighResoEmphasis(mrcImage* out,mrcImage* in,float High,float Low ,float A,float B,int mode);

void
main(int argc, char* argv[]) 
{
	mrcImage3DHighResoEmphasisInfo info;

/* variables */
	mrcImage in;
	mrcImage out;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);
	mrcFileRead(&in ,info.In ,"in main" ,0);

/* begin */
	DEBUGPRINT("Program Start\n");
	lmrcImage3DHighResoEmphasis(&out,&in,info.H,info.L,info.A,info.B,0);
	mrcFileWrite(&out ,info.Out ,"in main" ,0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- algorithm -----\n");
	fprintf(stderr, "R<L data*exp(A*L+B*L*L)\n");
	fprintf(stderr, "L<R<H data*exp(A*R+B*R*R) \n");
	fprintf(stderr, "R>H data*exp(A*H+B*H*H) \n");
}

void lmrcImage3DHighResoEmphasis(mrcImage* out,mrcImage* in,float High,float Low ,float A,float B,int mode)
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
    for(Y = -infft.HeaderN.y / 2.0; Y < infft.HeaderN.y / 2.0; Y += 1){
      for(X = 0; X <= infft.HeaderN.x / 2.0; X += 1){
	mrcPixelDataGet(&infft, X, Y, Z, &rdata, mrcPixelRePart, mrcPixelHowNearest);
	mrcPixelDataGet(&infft, X, Y, Z, &idata, mrcPixelImPart, mrcPixelHowNearest);
	e = lmrcImage3DHighResoEmphasisFunction(Fx*X ,Fy*Y ,Fz*Z ,High ,Low ,A ,B);
	mrcPixelDataSet(&outfft, X, Y, Z, rdata*e, mrcPixelRePart);
	mrcPixelDataSet(&outfft, X, Y, Z, idata*e, mrcPixelImPart);
      }
    }
  }
  mrcStatDataSet(&outfft,0);
  lmrcImageFFT(out,&outfft,0);
}

double lmrcImage3DHighResoEmphasisFunction(double X ,double Y ,double Z ,double High ,double Low ,double A ,double B)
{
/* variables */
  double R,data;

/* begin */  
  R=X*X+Y*Y+Z*Z;
  if (R<SQR(Low) ){
    data=exp(A*Low+B*Low*Low);
  }else if (R<SQR(High)){
    data=exp(sqrt(R)*Low+B*R);
  }else{
    data=exp(A*High+B*High*High);
  }
  return(data);
}
