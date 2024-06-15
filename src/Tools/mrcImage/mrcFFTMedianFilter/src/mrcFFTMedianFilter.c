/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcFFTMedianFilter ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcFFTMedianFilter
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcFFTMedianFilter ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "Memory.h"

/* prototype */
void lmrcFFTMedianFilter(mrcImage* out, mrcImage* in, float r);
int lmrcImageFFTMedianFilterCompare(const float* a, const float* b);

int
main(int argc, char* argv[]) 
{
	mrcFFTMedianFilterInfo info;

/* variables */
	mrcImage inft;
	mrcImage outft;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */
	DEBUGPRINT("Program Start\n");
	mrcFileRead(&inft, info.In, "from Main Routine", 0);
	lmrcFFTMedianFilter(&outft, &inft, info.r);
	mrcFileWrite(&outft, info.Out, "from Main Routine", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "Calculation is performed on amplitude only.\n");
	fprintf(stderr, "Output: Real part is amplitude and imaginary part is zero.\n");
	fprintf(stderr, "Use this program only for CTF determination.\n");
}

void 
lmrcFFTMedianFilter(mrcImage* dst, mrcImage* src, float r)
{
  /* variables */
  long n, index, center;
  float x, y, r2;
  float tmpx, tmpy;
  long offsetx, offsety;
  double data;
  float* kernel; 
  extern int lmrcImageFFTMedianFilterCompare(const float* a, const float* b);
  /* Initialize */
  offsetx=offsety=floor(r); 
  if (src->HeaderN.z!=1 ){
    fprintf(stderr,"Warning! Only Nz=1 is supported.\n");
  }
  r2 = SQR(r) ;
  fprintf(stderr,"%d %d %f\n",offsetx,offsety,r2);
  n=(offsetx*2+1)*(offsety*2+1);
  kernel = (float*)memoryAllocate(sizeof(float)*n, "in lFFTMedianFilter");
  dst->Header = src->Header;
  mrcInit(dst, NULL);	

  /* Begin */
	  for(x = 0; x <= src->HeaderN.x / 2.0; x++) {
	    DEBUGPRINT1("\n%f: ",x);
	    for(y = -src->HeaderN.y / 2.0; y < src->HeaderN.y / 2.0; y++) {
	      DEBUGPRINT1(" %f ",y);
	      index = 0;	
	      if (x > src->HeaderN.x / 2.0 - offsetx  ||
		  y > src->HeaderN.x / 2.0 - offsetx - 1 ||
		  y < -src->HeaderN.y / 2.0 + offsety ) {
		mrcPixelDataGet(src, x, y, 0, &data, mrcPixelMag, mrcPixelHowNearest);
		mrcPixelDataSet(dst, x, y, 0, data, mrcPixelRePart);
		mrcPixelDataSet(dst, x, y, 0, 0, mrcPixelImPart);
	      } else {
		for(tmpx=x-offsetx; tmpx<=x+offsetx; tmpx++) {
		  DEBUGPRINT1("\n%f ",tmpx);
		  for(tmpy=y-offsety; tmpy<=y+offsety; tmpy++) {
		    DEBUGPRINT1("%f ",tmpy);
		    if (SQR(y-tmpy)+SQR(x-tmpx) <= r2 ){
		      DEBUGPRINT("a");
		      mrcPixelDataGet(src, tmpx, tmpy, 0, &data, mrcPixelMag, mrcPixelHowNearest);
		      DEBUGPRINT("b");
		      kernel[index] = data;
		      DEBUGPRINT("c");
		      index++;		
		    }	
		  }
		  center = (index-1)/2;
		  n=index;
		}
		qsort(kernel, n, sizeof(float), lmrcImageFFTMedianFilterCompare);
		data = kernel[center];
		mrcPixelDataSet(dst, x, y, 0, data, mrcPixelRePart);
		mrcPixelDataSet(dst, x, y, 0, 0, mrcPixelImPart);
	      }
	    }
	  }
	  memoryFree(kernel);
}

int lmrcImageFFTMedianFilterCompare(const float* a, const float* b)
{
	if(*a<*b) {
		return -1;
	} else if(*a==*b) {
		return 0;
	} else {
		return 1;
	}
}

