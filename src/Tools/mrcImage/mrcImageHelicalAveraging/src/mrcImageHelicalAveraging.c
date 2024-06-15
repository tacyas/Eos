/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageHelicalAveraging ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageHelicalAveraging
#%Z% Attention
#%Z% */
static char __sccs_id[] = "%Z%mrcImageHelicalAveraging ver%I%; Date:%D% %Z%";
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

void llmrcImageRotation(mrcImage* out ,mrcImage* in ,double angle ,int mode);
void lmrcImageHelicalAveraging(mrcImage* out, mrcImage* in, double dp, double dz, int N);
void lmrcImageShiftwithZeroPadding(mrcImage* out, mrcImage* in, mrcImageParaTypeRealCoord shift, mrcPixelDataHowToGet mode);
void lmrcImageContinuousHelicalAveraging(mrcImage* out, mrcImage* in, double dp, double dz, int W);
void lmrcImageContinuousHelicalAveragingwithWeight(mrcImage* out, mrcImage* in, double dp, double dz, int W);


int
main(int argc, char* argv[]) 
{
	mrcImageHelicalAveragingInfo info;
	mrcImage in;
	mrcImage out;
	
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);
	mrcFileRead(&in, info.In, "in main", 0);
	if (info.mode==1){
	  lmrcImageContinuousHelicalAveraging(&out, &in, info.dp, info.dz, info.W);
	} else if (info.mode==0) {
	  lmrcImageHelicalAveraging(&out, &in, info.dp, info.dz, info.N);
	} else {
	  lmrcImageContinuousHelicalAveragingwithWeight(&out, &in, info.dp, info.dz, info.W);
	}
	mrcFileWrite(&out, info.Out, "in main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "0: Discrete.  Parameter N is needed.  \n");
	fprintf(stderr, "1: Continuous.  Parameter W is needed.  \n");
	fprintf(stderr, "2: Continuous.  Parameter W is needed.  Data are weighted by exp(- (dz/W)^2) \n");
}

void lmrcImageHelicalAveraging(mrcImage* out, mrcImage* in, double dp, double dz, int N)
{
  int n,sn,en,x,y,z,sz,ez;
  double pdz,data;
  mrcImage tmp1,tmp2;
  mrcImageParaTypeRealCoord shift;
  int* ni;

  if ( ( ni = (int *)malloc(sizeof(int)*in->HeaderN.z) ) == NULL ){
    fprintf(stderr ,"Enough memoly is not available.");
    exit(EXIT_FAILURE);
  }
  for (z=0 ;z<in->HeaderN.z ;z++) ni[z]=0;
  out->Header=in->Header;
  mrcInit(out,NULL);
  pdz=dz/in->HeaderLength.z;
  shift.x=0;
  shift.y=0;
  n=0;
  sn=-N/2;
  en=(N-1)/2;

  for (n=sn ;n<=en ;n++){
    DEBUGPRINT1("%d ",n);
    llmrcImageRotation(&tmp1,in,dp*n*RADIAN,2);
    DEBUGPRINT("rot ");
    shift.z = pdz*n;
    lmrcImageShiftwithZeroPadding(&tmp2,&tmp1,shift,2);
    sz=MAX(0,floor(shift.z+0.99999999));
    ez=MIN(in->HeaderN.z ,floor(in->HeaderN.z+shift.z) );
    DEBUGPRINT3("%d %d %d\n",n,sz,ez);
    for (z=sz ;z<ez ;z++){
      ni[z]+=1;
    }
    if (n==sn){
      shift.z=0;
      lmrcImageCopy(out,&tmp2,shift);       
    } else {
      llmrcImageAdd(out,&tmp2);
      mrcImageFree(&tmp1,"");
      mrcImageFree(&tmp2,"");
    }
  }
  for (z=0; z<out->HeaderN.z ;z++){
    DEBUGPRINT2("%d %d \n",z,ni[z]);
    for (y=0 ;y<out->HeaderN.y ;y++){
      for (x=0 ;x<out->HeaderN.x ;x++){
	
	mrcPixelDataGet(out ,x ,y ,z ,&data ,mrcPixelRePart , mrcPixelHowNearest);	  
	data /= ni[z];
	mrcPixelDataSet(out ,x ,y ,z ,data ,mrcPixelRePart);
      }
    }
  }
}

void llmrcImageRotation(mrcImage* out ,mrcImage* in ,double angle ,int mode)
{
  int z;
  mrcImage tmpin,tmpout;

  if (in->HeaderN.z==1){
    lmrcImageRotation2D(out, in, angle, mode);
  }else{
    out->Header=in->Header;
    mrcInit(out,NULL);
    for (z=0 ;z<out->HeaderN.z ;z++){
      lmrc3DZ1ImgGet(&tmpin ,in ,z);
      lmrcImageRotation2D(&tmpout, &tmpin, angle, mode);
      lmrc3DZ1ImgPut(out ,&tmpout ,z);
      mrcImageFree(&tmpin,"");
      mrcImageFree(&tmpout,"");
    }
    mrcStatDataSet(out,0);
  }
}


void
lmrcImageShiftwithZeroPadding(mrcImage* out, mrcImage* in, mrcImageParaTypeRealCoord shift, mrcPixelDataHowToGet mode)
{ 
	float x, y, z;
	double data;

	out->Header = in->Header;
	mrcInit(out, NULL);
	for(x=0; x<in->HeaderN.x; x++) {
		for(y=0; y<in->HeaderN.y; y++) {
			for(z=0; z<in->HeaderN.z; z++) {
				mrcPixelDataGet(in, x - shift.x, 
						    y - shift.y, 
						    z - shift.z, 
						&data, mrcPixelRePart, mode); 
				if ( x-shift.x < 0 || x-shift.x > in->HeaderN.x - 1 ||
				     y-shift.y < 0 || y-shift.y > in->HeaderN.y - 1 ||
				     z-shift.z < 0 || z-shift.z > in->HeaderN.z - 1 ){
				  data = 0;
				}
				mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);
			}
		}
	}
}



void lmrcImageContinuousHelicalAveraging(mrcImage* out, mrcImage* in, double dp, double dz, int W)
{ 
  int x,y,z,tmpz;
  double pixeldp,tmpx,tmpy,data,tmpdata,phi,cx,cy;

  out->Header = in->Header;
  mrcInit(out, NULL);
  cx = (in->HeaderN.x - 1.0 ) / 2.0;
  cy = (in->HeaderN.x - 1.0 ) / 2.0;

  pixeldp=dp / (dz / in->HeaderLength.z);
  for (z=0; z<in->HeaderN.z; z++){
    DEBUGPRINT1("%d ",z);
    for (x=0; x<in->HeaderN.x; x++){
      for (y=0; y<in->HeaderN.y; y++){	
	data = 0;
	for (tmpz=-W; tmpz<=W; tmpz++){
	  phi=pixeldp*tmpz*RADIAN;
	  tmpx = cos(phi) * (x-cx) - sin(phi) * (y-cy) + cx;
	  tmpy = sin(phi) * (x-cx) + cos(phi) * (y-cy) + cy;
	  mrcPixelDataGet(in ,tmpx ,tmpy ,tmpz+z ,&tmpdata ,mrcPixelRePart ,mrcPixelHowCubicConv);
	  data += tmpdata;
	}
	mrcPixelDataSet(out ,x ,y ,z ,data ,mrcPixelRePart);
      }
    }
  }
  mrcStatDataSet(out, 0);
}



void lmrcImageContinuousHelicalAveragingwithWeight(mrcImage* out, mrcImage* in, double dp, double dz, int W)
{ 
  int x,y,z,tmpz;
  double pixeldp,tmpx,tmpy,data,tmpdata,phi,cx,cy;

  out->Header = in->Header;
  mrcInit(out, NULL);
  cx = (in->HeaderN.x - 1.0 ) / 2.0;
  cy = (in->HeaderN.x - 1.0 ) / 2.0;

  pixeldp=dp / (dz / in->HeaderLength.z);
  for (z=0; z<in->HeaderN.z; z++){
    DEBUGPRINT1("%d ",z);
    for (x=0; x<in->HeaderN.x; x++){
      for (y=0; y<in->HeaderN.y; y++){	
	data = 0;
	for (tmpz=-2*W; tmpz<=+2*W; tmpz++){
	  phi=pixeldp*tmpz*RADIAN;
	  tmpx = cos(phi) * (x-cx) - sin(phi) * (y-cy) + cx;
	  tmpy = sin(phi) * (x-cx) + cos(phi) * (y-cy) + cy;
	  mrcPixelDataGet(in ,tmpx ,tmpy ,tmpz+z ,&tmpdata ,mrcPixelRePart ,mrcPixelHowCubicConv);
	  data += tmpdata * exp(-(tmpz/W)*(tmpz/W));
	}
	mrcPixelDataSet(out ,x ,y ,z ,data ,mrcPixelRePart);
      }
    }
  }
  mrcStatDataSet(out, 0);
}







