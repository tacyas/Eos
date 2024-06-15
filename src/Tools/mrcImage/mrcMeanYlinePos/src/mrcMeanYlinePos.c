/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcMeanYlinePos ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcMeanYlinePos
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcMeanYlinePos ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "genUtil.h"
#include "mrcImage.h"

/* prototype */
double llmrcLineMean(mrcImage* in1,int xLine, int width , int* error);

void
main(int argc, char* argv[]) 
{
	long status;
	mrcMeanYlinePosInfo info;

/* variables */
	mrcImage in;
	int x;
	int err;
	double yMeanPos;	
/* input parameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */
	mrcFileRead(&in,   info.In,  "in main",0);
	DEBUGPRINT("Read\n");
	
	fprintf(stdout,"x,yMeanPosition\n");

	for (x=0 ; x<in.HeaderN.x ; x++) {
		yMeanPos=llmrcLineMean(&in,x,info.width,&err);

		DEBUGPRINT1("%d\n",x)

		if (err == 0) {
			fprintf(info.fptOut,"%d,%f\n",x,(float)yMeanPos);
		}
		else	{
			fprintf(info.fptOut,"%d,-1\n",x);
		}
		
	}
	
	DEBUGPRINT("End\n");
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
}

double llmrcLineMean(mrcImage* in1 , int xLine , int width , int* error)
{
	/* variables */
	int y,z,yStart,yEnd, centre;
	double data,maxPosition,maxPositionBright;
	double normalization;
	double lineMean;
	double meanBright;
	double cutRatio;

	/* main */
	z=0; 			 	/*Plain Data Only */
	lineMean      = 0; 	/*initialization */
	maxPosition = 0; 	/*initialization */
	maxPositionBright = -99999; /*initialization*/
	normalization = 0;	 /*normalization */
	meanBright = 0;
	cutRatio = 1.2;

	if(width < 0 || in1->HeaderN.y < width) {
		yStart = 0;
		yEnd = (in1->HeaderN.y);
	} else { 
		centre = in1->HeaderN.y/2;
		yStart = centre - width/2;
		yEnd   = yStart + width - 1;
	}
	
	for (y=yStart; y<=yEnd ; y++) {
		mrcPixelDataGet(in1,xLine,y,z,&data,mrcPixelRePart,mrcPixelHowNearest);
		meanBright += data;
	}
	
	meanBright = meanBright / (double)(yEnd-yStart+1);

	/* Bottom up */
	meanBright = meanBright * cutRatio;
	
	/* Detect MeanPosition */
	*error = 1;

	for (y=yStart; y<=yEnd ; y++) {
		mrcPixelDataGet(in1,xLine,y,z,&data,mrcPixelRePart,mrcPixelHowNearest);
		
		if (data>meanBright) {
			lineMean += (data-meanBright)*(double)y;
			normalization += (data-meanBright);
			*error =0;
		}
	}
	
	
	/* position data */
	if (*error == 0) {
		lineMean = (lineMean / normalization);
		return(lineMean);
	} else {
 		return(-1);
	}
} 
