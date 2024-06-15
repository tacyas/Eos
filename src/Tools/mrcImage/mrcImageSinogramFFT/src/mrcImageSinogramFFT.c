/*
# mrcImageSinogramFFT : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageSinogramFFT
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
#include "lmrcImageSinogramFFT.h"

/*
Example:
typedef struct lmrcImageSinogramFFTInfo {
	float a;
	int   b;
} lmrcImageSinogramFFTInfo;

typedef enum lmrcImageSinogramFFTMode {
	a=0,
	b=1
} lmrcImageSinogramFFTMode;
*/
/*
void
lmrcImageSinogramFFT(mrcImage* out, mrcImage* in, int mode);

void
__OneLineGet(mrcImage* out, mrcImage* in, int delta, int mode);
*/

int
main(int argc, char* argv[]) 
{
	mrcImageSinogramFFTInfo  info;
	mrcImage In;
	mrcImage Out;
	
	init0(&info);
        argCheck(&info, argc, argv);
        init1(&info);

	DEBUGPRINT("Program Start\n");
	
	mrcFileRead(&In, info.In, "Read In", 0);
	lmrcImageSinogramFFT(&Out, &In, 0);
	mrcFileWrite(&Out, info.Out, "Read Out", 0);
	
	DEBUGPRINT("Program End\n");

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

/*
void
lmrcImageSinogramFFT(mrcImage* out, mrcImage* in, int mode)
{
	int      i, j;
	mrcImage OneLine;
	mrcImage OneLineFT;
	double   re, im;

	out->Header = in->Header;
	out->HeaderMode = mrcFloatRadonFT;
	mrcInit(out, NULL);

	for(i=0; i<in->HeaderN.y; i++){
		__OneLineGet(&OneLine, in, i, 0);
		lmrcImageFFT(&OneLineFT, &OneLine, 0);
		for(j=0; j<=out->HeaderN.x/2; j++){
			mrcPixelDataGet(&OneLineFT, j, 0, 0, &re, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(&OneLineFT, j, 0, 0, &im, mrcPixelImPart, mrcPixelHowNearest);
			mrcPixelDataSet(out, j, i, 0, re, mrcPixelRePart);
			mrcPixelDataSet(out, j, i, 0, im, mrcPixelImPart);
		}
	}

}

void
__OneLineGet(mrcImage* out, mrcImage* in, int delta, int mode)
{
	int    i;
	double data;

	out->Header = in->Header;
	out->HeaderN.y = out->HeaderN.z = 1;
	mrcInit(out, NULL);

	for(i=0; i<in->HeaderN.x; i++){
		mrcPixelDataGet(in, i, delta, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataSet(out, i, 0, 0, data, mrcPixelRePart);
	}
}
*/
