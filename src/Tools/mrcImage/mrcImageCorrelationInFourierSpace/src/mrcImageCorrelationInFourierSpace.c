/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageCorrelationInFourierSpace ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageCorrelationInFourierSpace
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageCorrelationInFourierSpace ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"

/* prototype */
void lmrcImageCorrelationInFourierSpace(mrcImage* out, mrcImage* in1, mrcImage* in2, int mode);

int
main(int argc, char* argv[]) 
{
	mrcImageCorrelationInFourierSpaceInfo info;

/* variables */
	mrcImage in1;
	mrcImage in2;
	mrcImage out;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);
	mrcFileRead(&in1 ,info.In1 ,"in main" ,0);
	mrcFileRead(&in2 ,info.In2 ,"in main" ,0);

/* begin */
	
	DEBUGPRINT("Program Start\n");
	lmrcImageCorrelationInFourierSpace(&out, &in1, &in2, info.mode);
	mrcFileWrite(&out ,info.Out ,"in main" ,0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "Mode 0: (FxG*)/(|FG|) \n");
	fprintf(stderr, "Mode 1: Phase residual \n");
}

void lmrcImageCorrelationInFourierSpace(mrcImage* out, mrcImage* in1, mrcImage* in2, int mode)
{
/* variables */
	int X,Y,Z;
	double  rdata1,idata1,rdata2,idata2,f1,f2,cor,nr1,ni1,nr2,ni2,dr,di,d;

/* begin */
	out->Header = in1->Header;
	mrcInit(out,NULL);
	for (Z=-in1->HeaderN.z/2.0; Z<in1->HeaderN.z/2.0; Z++) {
    for (Y=-in1->HeaderN.y/2.0; Y<in1->HeaderN.y/2.0; Y++) {
	for (X=0; X<=in1->HeaderN.x/2.0; X++) {
		mrcPixelDataGet(in1, X, Y, Z, &rdata1, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(in1, X, Y, Z, &idata1, mrcPixelImPart, mrcPixelHowNearest);
		mrcPixelDataGet(in2, X, Y, Z, &rdata2, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(in2, X, Y, Z, &idata2, mrcPixelImPart, mrcPixelHowNearest);
		f1 = rdata1*rdata1 + idata1*idata1;
		f2 = rdata2*rdata2 + idata2*idata2;
		if (f1 != 0 && f2 != 0 ){
			f1=sqrt(f1);
	  		f2=sqrt(f2);
	  		cor = (rdata1*rdata2 + idata1*idata2) / (f1*f2) ;
	  		DEBUGPRINT4("%d,%d,%d %f ",X,Y,Z,cor);
	  		if (mode==1){
	    		cor=acos(cor);
	    		cor *= 180/PI;
	  		}
	  		DEBUGPRINT1("%f\n",cor);
	  	} else { 
	  		cor=0;
		}
      	mrcPixelDataSet(out,X,Y,Z,cor ,mrcPixelRePart);
	}
	}
	}
	mrcStatDataSet(in1,0);  
}
