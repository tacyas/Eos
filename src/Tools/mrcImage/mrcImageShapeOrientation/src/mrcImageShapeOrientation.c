/*
# mrcImageShapeOrientation : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageShapeOrientation
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

typedef struct lmrcImageShapeOrientationInfo {
	// Input
	float	threshold; //  
	// Output
	float	orientationParameter[3];
} lmrcImageShapeOrientationInfo;

typedef enum lmrcImageShapeOrientationMode {
	lmrcImageShapeOrientationModeOrientationParameter=0
} lmrcImageShapeOrientationMode;

extern void lmrcImageShapeOrientation(mrcImage* in, lmrcImageShapeOrientationInfo* linfo, int mode);
extern void lmrcImageShapeOrientationMode0(mrcImage* in, lmrcImageShapeOrientationInfo* linfo, int mode);
extern void lmrcImageShapeOrientationPrint(FILE* fpt, lmrcImageShapeOrientationInfo linfo, int mode);

int
main(int argc, char* argv[]) 
{
	mrcImageShapeOrientationInfo info;
	lmrcImageShapeOrientationInfo linfo;
	mrcImage in;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.In, "in main", 0);
	linfo.threshold = info.threshold;
	lmrcImageShapeOrientation(&in, &linfo, info.mode);

	lmrcImageShapeOrientationPrint(info.fptOut, linfo, info.mode);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}


void 
lmrcImageShapeOrientation(mrcImage* in, lmrcImageShapeOrientationInfo* linfo, int mode)
{
	switch(mode) {
		case lmrcImageShapeOrientationModeOrientationParameter: {
			lmrcImageShapeOrientationMode0(in, linfo, mode);
			break;
		}
		default: {
			fprintf(stderr, "in lmrcImageShapeOrientation\n");
			fprintf(stderr, "Not supported mode: %d \n", mode);
			exit(EXIT_FAILURE);	
			break;
		}
	}
}


void 
lmrcImageShapeOrientationPrint(FILE* fpt, lmrcImageShapeOrientationInfo linfo, int mode)
{

	switch(mode) {
		case lmrcImageShapeOrientationModeOrientationParameter: {
			fprintf(fpt, "OrientationParameter: %f %f %f\n", 
				linfo.orientationParameter[0],  
				linfo.orientationParameter[1], 
				linfo.orientationParameter[2]);
			break;
		}
		default: {
			fprintf(stderr, "in lmrcImageShapeOrientation\n");
			fprintf(stderr, "Not supported mode: %d \n", mode);
			exit(EXIT_FAILURE);	
			break;
		}
	}
}

void 
lmrcImageShapeOrientationMode0(mrcImage* in, lmrcImageShapeOrientationInfo* linfo, int mode)
{
	mrcImageParaTypeReal x1, y1, z1;
	mrcImageParaTypeReal x2, y2, z2;
	double data1, data2, w1, w2, w, len;
	double weight, sum[3], cosTheta[3];
	int i;

	for(i=0; i<3; i++) {
		weight = sum[i] = 0.0;
	}
	for(z1=0; z1<in->HeaderN.z; z1++) {
		DEBUGPRINT1("%f\n", z1);	
	for(y1=0; y1<in->HeaderN.y; y1++) {
	for(x1=0; x1<in->HeaderN.x; x1++) {
		mrcPixelDataGet(in, x1, y1, z1, &data1, mrcPixelRePart, mrcPixelHowNearest);
		if(linfo->threshold<data1) {
			w1 = data1-linfo->threshold; 
		} else {
			break;
		}

		for(z2=0; z2<in->HeaderN.z; z2++) {
		for(y2=0; y2<in->HeaderN.y; y2++) {
		for(x2=0; x2<in->HeaderN.x; x2++) {
			mrcPixelDataGet(in, x2, y2, z2, &data2, mrcPixelRePart, mrcPixelHowNearest);
			if(linfo->threshold<data2) {
				len = sqrt(SQR(x1-x2)+SQR(y1-y2)+SQR(z1-z2));
				w2 = data2-linfo->threshold; 
				w = w1*w2*len;
				weight += w;
				if(0<w) {
					if(w1<w2) {
						cosTheta[0] = (x2-x1)/len;
						cosTheta[1] = (y2-y1)/len;
						cosTheta[2] = (z2-z1)/len;
					} else {
						cosTheta[0] = (x1-x2)/len;
						cosTheta[1] = (y1-y2)/len;
						cosTheta[2] = (z1-z2)/len;
					}
					sum[0] += w*(3*SQR(cosTheta[0]) - 1)/2;
					sum[1] += w*(3*SQR(cosTheta[1]) - 1)/2;
					sum[2] += w*(3*SQR(cosTheta[2]) - 1)/2;
				}
			}	
		}
		}
		}
	}
	}
	}

	linfo->orientationParameter[0] = sum[0]/weight;
	linfo->orientationParameter[1] = sum[1]/weight;
	linfo->orientationParameter[2] = sum[2]/weight;
}

