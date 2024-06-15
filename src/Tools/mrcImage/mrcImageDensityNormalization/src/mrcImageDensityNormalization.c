/*
# mrcImageDensityNormalization : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageDensityNormalization
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

typedef struct lmrcImageDensityNormalizationInfo {
	double value;
} lmrcImageDensityNormalizationInfo;

typedef enum lmrcImageDensityNormalizationMode {
	lmrcImageDensityNormalizationModeIsovolume=0
} lmrcImageDensityNormalizationMode;


extern void lmrcImageDensityNormalizationModePrint(FILE* fpt);
extern void lmrcImageDensityNormalization(mrcImage* out, mrcImage* in, lmrcImageDensityNormalizationInfo linfo, int mode);
extern void lmrcImageDensityNormalization0(mrcImage* out, mrcImage* in, lmrcImageDensityNormalizationInfo linfo, int mode);

int
main(int argc, char* argv[]) 
{
	mrcImage in;
	mrcImage out;
	mrcImageDensityNormalizationInfo info;
	lmrcImageDensityNormalizationInfo linfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	linfo.value = info.Value;

	mrcFileRead(&in, info.In, "in main", 0);

	lmrcImageDensityNormalization(&out, &in, linfo, info.mode);

	mrcFileWrite(&out, info.Out, "in main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	lmrcImageDensityNormalizationModePrint(stderr);
}

void
lmrcImageDensityNormalizationModePrint(FILE* fpt)
{
	fprintf(fpt, "Isovolume: %d : make the sum of pixel values the input value\n", lmrcImageDensityNormalizationModeIsovolume);
}

void
lmrcImageDensityNormalization(mrcImage* out, mrcImage* in, lmrcImageDensityNormalizationInfo linfo, int mode)
{
	switch(mode) {
		case lmrcImageDensityNormalizationModeIsovolume: {
			lmrcImageDensityNormalization0(out, in, linfo, mode);
			break;
		}
		default: {
			break;
		}
	}

}

void
lmrcImageDensityNormalization0(mrcImage* out, mrcImage* in, lmrcImageDensityNormalizationInfo linfo, int mode)
{
	mrcImageParaTypeReal x, y, z;
	double sum;
	double data;

	out->Header = in->Header;
	mrcInit(out, NULL);

	sum = 0;
	for(x=0; x<in->HeaderN.x; x++) {
	for(y=0; y<in->HeaderN.y; y++) {
	for(z=0; z<in->HeaderN.z; z++) {
		mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);					
		sum += data;
	}
	}
	}

	if(0==linfo.value) {
		fprintf(stderr, "Value is zero.  Do not permit it in this routine\n");	
		exit(EXIT_FAILURE);
	}
	
	if(0==sum) {
		fprintf(stderr, "Density summention is zero.  Do not permit it in this routine\n");	
		exit(EXIT_FAILURE);
	}

	
	DEBUGPRINT1("sum: %lf\n", sum)
	sum = fabs(sum)/linfo.value;
	DEBUGPRINT2("final sum: %lf value: %lf\n", sum, linfo.value);

	for(x=0; x<out->HeaderN.x; x++) {
	for(y=0; y<out->HeaderN.y; y++) {
	for(z=0; z<out->HeaderN.z; z++) {
		mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);					
		data /= sum;
		mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);					
	}
	}
	}
}

