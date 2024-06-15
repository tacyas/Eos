/*
# mrcImageTiltAxisSearch : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageTiltAxisSearch
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
#include "mrcRefUtil.h"
#include "Memory.h"
#include "Vector.h"

typedef struct lmrcImageTiltAxisSearchInfo {
	int	  num;

	float width;
	float minTheta;
	float maxTheta;
	float deltaTheta;

	int interpolationMode;

	int correlationMode;
} lmrcImageTiltAxisSearchInfo;

extern double lmrcImageTiltAxisSearch(mrcImage* out, mrcImage* in, mrcImage* ref, lmrcImageTiltAxisSearchInfo linfo, int mode);

int
main(int argc, char* argv[]) 
{
	mrcImageTiltAxisSearchInfo info;
	lmrcImageTiltAxisSearchInfo linfo;

	mrcImage* in;
	mrcImage ref;
	mrcImage out; 
	int i;
	double result;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	linfo.width = info.Width;
	linfo.minTheta = info.thetaMin*RADIAN;
	linfo.maxTheta = info.thetaMax*RADIAN;
	linfo.deltaTheta = info.thetaDelta*RADIAN;
	linfo.interpolationMode = info.Mode; 
	linfo.correlationMode = info.CorrelationMode; 

	linfo.num = 1;
	if(info.flagIn) {
		linfo.num = 1;	
	} else if(info.flagInList) {
		linfo.num = info.flagInList;
	} else {
		fprintf(stderr, "You need either In or InList.\n");
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	in = memoryAllocate(sizeof(mrcImage)*linfo.num, "in main");
	if(info.flagIn) {
		mrcFileRead(&(in[0]), info.In, "in main", 0);
	} else if(info.flagInList) {
		for(i=0; i<linfo.num; i++) {
			mrcFileRead(&(in[i]), info.InList[i], "in main", 0);
		}
	}

	mrcFileRead(&ref, info.Ref, "in main", 0);

	result = lmrcImageTiltAxisSearch(&out, in, &ref, linfo, info.mode);	

	mrcFileWrite(&out, info.Out, "in main", 0);

	fprintf(info.fptOut2, "%8.3f\n", result*DEGREE);
	return EXIT_SUCCESS;
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}


double
lmrcImageTiltAxisSearch(mrcImage* out, mrcImage* in, mrcImage* ref, lmrcImageTiltAxisSearchInfo linfo, int mode)
{
	int i;
	int j;
	int nTheta;
	int minWidth;
	int tmpMinWidth;
	mrcImage tmp2DRot;
	mrcImage tmp2DCenter;
	mrcImage tmp2DProj;
	mrcImage ref2DRot;
	mrcImage ref2DCenter;
	mrcImage ref2DProj;
	mrcImage cor2DProj;
	float theta;
	float width;
	int Cx, Cy, Cz;
	mrcImageInformation info;
	double weight;
	double data;

	minWidth = MIN(ref->HeaderN.x, ref->HeaderN.y);
	for(i=0; i<linfo.num; i++) {
		tmpMinWidth = MIN(in[i].HeaderN.x, in[i].HeaderN.y);
		if(tmpMinWidth < minWidth) {
			minWidth = tmpMinWidth;
		}
	}
	width =(int)(minWidth*linfo.width + 0.5);

	info.mode = meanOfAll;
	nTheta = ((int)((linfo.maxTheta - linfo.minTheta)/linfo.deltaTheta + 0.5)) + 1;

	mrcDefaultHeaderValueSet(out);
	out->HeaderN.x = nTheta;
	out->HeaderN.y = linfo.num;
	out->HeaderN.z = 1;
	out->HeaderMode = mrcFloatImage;
	mrcInit(out, NULL);

	weight = data = 0.0;
	for(j=0; j<nTheta; j++) {
		theta = linfo.minTheta + j*linfo.deltaTheta;		
		//DEBUGPRINT("ROTATION");
		lmrcImageRotation2DPeriodicBoundary(&ref2DRot, ref, theta, linfo.interpolationMode);
		Cx = MIN(ref2DRot.HeaderN.x/2 + 1, ref2DRot.HeaderN.x);
		Cy = MIN(ref2DRot.HeaderN.y/2 + 1, ref2DRot.HeaderN.y);
		Cz = MIN(ref2DRot.HeaderN.z/2 + 1, ref2DRot.HeaderN.z);

		//DEBUGPRINT("CENTER");
		lmrcImageCenterGet(&ref2DCenter, &ref2DRot, width, width, width, Cx, Cy, Cz,linfo.interpolationMode);
		lmrcImageXProjection(&ref2DProj, &ref2DCenter);
		for(i=0; i<linfo.num; i++) {
			lmrcImageRotation2DPeriodicBoundary(&tmp2DRot, &(in[i]), theta, linfo.interpolationMode);
			Cx = MIN(tmp2DRot.HeaderN.x/2 + 1, tmp2DRot.HeaderN.x);
			Cy = MIN(tmp2DRot.HeaderN.y/2 + 1, tmp2DRot.HeaderN.y);
			Cz = MIN(tmp2DRot.HeaderN.z/2 + 1, tmp2DRot.HeaderN.z);
			lmrcImageCenterGet(&tmp2DCenter, &tmp2DRot, width, width, width, Cx, Cy, Cz, linfo.interpolationMode);
			lmrcImageXProjection(&tmp2DProj, &tmp2DCenter);
			lmrcImageCorrelation(&cor2DProj, &tmp2DProj, &ref2DProj, linfo.correlationMode);
			lmrcImageInformation(&info, &cor2DProj);
			DEBUGPRINT3("%f %f %f\n", theta*DEGREE, info.max, info.maxCoord.x);
			
			weight += info.max;
			data   += theta*info.max;

			mrcPixelDataSet(out, j, i, 0, info.max, mrcPixelRePart);
			
			mrcImageFree(&tmp2DRot, "in lmrcImageTiltAxisSearch");	
			mrcImageFree(&tmp2DCenter, "in lmrcImageTiltAxisSearch");
			mrcImageFree(&tmp2DProj, "in lmrcImageTiltAxisSearch");	
			mrcImageFree(&cor2DProj, "in lmrcImageTiltAxisSearch");	
		}
		mrcImageFree(&ref2DRot, "in lmrcImageTiltAxisSearch");	
		mrcImageFree(&ref2DCenter, "in lmrcImageTiltAxisSearch");	
		mrcImageFree(&ref2DProj, "in lmrcImageTiltAxisSearch");	
	}

	return data/weight;
}

