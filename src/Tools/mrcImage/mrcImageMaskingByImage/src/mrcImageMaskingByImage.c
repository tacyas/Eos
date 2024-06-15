/*
# mrcImageMaskingByImage.c  1.1
# The latest update : 11/28/96 at 12:28:52
#
#@(#) mrcImageMaskingByImage ver 1.1
#@(#) Created by 
#@(#)
#@(#) Usage : mrcImageMaskingByImage
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)mrcImageMaskingByImage ver1.1; Date:96/11/28 @(#)";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"


typedef struct lmrcImageMaskingByImageInfo {

	int   flagCutValue;
	float CutValue;	
} lmrcImageMaskingByImageInfo;

extern void lmrcImageMaskingByImage(
	mrcImage* out, 
	mrcImage* in, 
	mrcImage* mask, 
	lmrcImageMaskingByImageInfo* linfo, 
	int mode);

int
main(int argc, char* argv[]) 
{
	long status;
	mrcImageMaskingByImageInfo info;
	lmrcImageMaskingByImageInfo linfo;

	mrcImage in;
	mrcImage out;
	mrcImage mask;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("---- Program Start -----\n");
	linfo.flagCutValue = info.flagCutValue;
	linfo.CutValue     = info.CutValue;

	mrcFileRead(&in,   info.In,       "in main", 0); 
	mrcFileRead(&mask, info.MaskFile, "in main", 0); 

	out.Header = in.Header;
	mrcInit(&out, NULL);

	lmrcImageMaskingByImage(&out, &in, &mask, &linfo, info.mode); 

	mrcStatDataSet(&out, 0);
	mrcFileWrite(&out, info.Out, "in main", 0); 

	return 0;	
}

void
additionalUsage()
{
	fprintf(stderr,"mode = 0  : cut off values larger that CutValue.\n");
	fprintf(stderr,"mode = 1  : cut off values smaller that CutValue.\n");
	fprintf(stderr,"mode = 2  : multiplying mask image \n");
	fprintf(stderr,"mode = +16 : Subtract the average of ROI from the density  \n");
}


void 
lmrcImageMaskingByImage(
	mrcImage* out, 
	mrcImage* in, 
	mrcImage* mask, 
	lmrcImageMaskingByImageInfo* linfo, 
	int mode)
{
	mrcImageParaTypeReal x, y, z;
	double data, data0;
	double maskdata;
	double avg; 
	double n;
	double dn;

	if(in->HeaderN.x != mask->HeaderN.x ||
	   in->HeaderN.y != mask->HeaderN.y ||
	   in->HeaderN.z != mask->HeaderN.z){
		fprintf(stderr,"Not same size.\n");
		exit(EXIT_FAILURE);
	}
	
	avg = 0;
	n   = 0;
	for(z=0; z<in->HeaderN.z; z++) {
	for(y=0; y<in->HeaderN.y; y++) {
	for(x=0; x<in->HeaderN.x; x++) {
		mrcPixelDataGet(in,   x, y, z, &data,     mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(mask, x, y, z, &maskdata, mrcPixelRePart, mrcPixelHowNearest);

		dn = 1;
		switch(mode&0xf) {
			case 0: {
				if(linfo->CutValue < maskdata) {
					data = 0;
					dn   = 0;
				} 
				break;
			}
			case 1: {	
				if(maskdata < linfo->CutValue) {
					data = 0;
					dn   = 0;
				} 
				break;
			}
			case 2: {
				data = data*maskdata;
				dn   = maskdata;
				if(linfo->flagCutValue 
				&&(maskdata < linfo->CutValue)) {
					dn    = 0;
				}
				break;
			}
			default: {
				fprintf(stderr, "Not supported Mode: %d\n", mode);
			}
		}
		mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);

		if(linfo->flagCutValue) {
			avg += data;
			n   += dn;	
		}
	}
	}
	}

	DEBUGPRINT3("avg %f n %f mode %d\n", avg, n, mode&0x2);

	if( 0 != (mode&0xf0) 
	 && 0 <  n) {
		avg /= n;
		DEBUGPRINT1("avg %f\n", avg);

		for(z=0; z<in->HeaderN.z; z++) {
		for(y=0; y<in->HeaderN.y; y++) {
		for(x=0; x<in->HeaderN.x; x++) {
			mrcPixelDataGet(out,  x, y, z, &data,     mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(mask, x, y, z, &maskdata, mrcPixelRePart, mrcPixelHowNearest);
			
			switch(mode&0xf) {
				case 0: {
					data -= avg;
					if(linfo->CutValue < maskdata){
						data = 0;
					} 
					break;
				}
				case 1: {	
					data -= avg; 	
					if(maskdata < linfo->CutValue){
						data = 0;
					} 
					break;
				}
				case 2: {	
					mrcPixelDataGet(in, x, y, z, &data0, mrcPixelRePart, mrcPixelHowNearest);
					data = (data0 - avg)*maskdata;
					break;
				}
			}
			mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);
		}
		}	
		}	
	}
}

