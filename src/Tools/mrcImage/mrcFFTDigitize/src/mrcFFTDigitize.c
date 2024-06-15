/*
# mrcFFTDigitize : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcFFTDigitize
# Attention
#   $Loccker$
#  	$State$ 
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"

typedef struct lmrcFFTDigitizeInfo {
	double   Level;
	double   Min;
	double   Max;
} lmrcFFTDigitizeInfo;

/*
typedef enum lmrcFFTDigitizeMode {
	a=0,
	b=1
} lmrcFFTDigitizeMode;
*/

extern void lmrcFFTDigitize(mrcImage* out, mrcImage* in, lmrcFFTDigitizeInfo linfo, int mode);

int
main(int argc, char* argv[]) 
{
	mrcFFTDigitizeInfo  info;
	lmrcFFTDigitizeInfo linfo;

	mrcImage in;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.In, "from main", 0); 

	linfo.Level = info.Level;
	linfo.Min   = info.Min;
	linfo.Max   = info.Max;
	
	
	lmrcFFTDigitize(&out, &in, linfo, info.mode);

	mrcFileWrite(&out, info.Out, "from main", 0); 
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

void 
lmrcFFTDigitize(mrcImage* out, mrcImage* in, lmrcFFTDigitizeInfo linfo, int mode)
{
	float iX, iY;
	double re, im, mag, theta, dstre, dstim;
	int dstmag;
	double mean;

	out -> Header = in -> Header;

	mrcInit(out, NULL);
	mean = (linfo.Max - linfo.Min) / linfo.Level;

	for(iY = -in -> HeaderN.y / 2.0; iY < in -> HeaderN.y / 2.0; iY++) {
		for(iX = 0.0; iX <= in -> HeaderN.x / 2.0; iX++) {
			
			mrcPixelDataGet(in, iX, iY, 0.0, &re, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, iX, iY, 0.0, &im, mrcPixelImPart, mrcPixelHowNearest);

			//mag = sqrt(re*re+im*im);
			//theta = atan2(im, re);

			//dstre = mag*cos(theta);
			//dstim = mag*sin(theta);

			mag = sqrt(re * re + im *im);
			theta = atan2(im, re);

			if(mag < linfo.Min){
				dstmag = 0;
			}else if(mag > linfo.Max) {
				dstmag = 1;
			}else{
				dstmag = (mag - linfo.Min) / mean;
			}	
		
			mrcPixelDataSet(out, iX, iY, 0.0, dstmag * cos(theta), mrcPixelRePart); 
			mrcPixelDataSet(out, iX, iY, 0.0, dstmag * sin(theta), mrcPixelImPart); 
			//mrcPixelDataSet(out, iX, iY, 0.0,  dstre, mrcPixelRePart);
			//mrcPixelDataSet(out, iX, iY, 0.0,  dstim, mrcPixelImPart);
		}

	}
}
