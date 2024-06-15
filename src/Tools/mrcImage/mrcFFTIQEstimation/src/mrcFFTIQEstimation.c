/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcFFTIQEstimation ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcFFTIQEstimation
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcFFTIQEstimation ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#undef DEBUG
#include "genUtil.h"
#include "File.h"
#include "Memory.h"
#include "eosString.h"
#include "mrcImage.h"


typedef struct lmrcFFTIQEstimationInfo {
	double                     radius;
	int                        numberOfSpot;
	mrcImageParaTypeRealCoord* P;
	double*                    IQ;                  	
	double*                    Peak;                  	
	double*                    Back;                  	
	double*                    Count;                  	
} lmrcFFTIQEstimationInfo;

extern int lmrcFFTIQEstimation(mrcImage* mrc, lmrcFFTIQEstimationInfo* linfo, int mode);

int
main(int argc, char* argv[]) 
{
	mrcFFTIQEstimationInfo info;
	lmrcFFTIQEstimationInfo linfo;
	mrcImage mrc;
	int i;
	char s[1024];

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
/* Data Input */
	mrcFileRead(&mrc, info.In, "in main", 0);
	linfo.numberOfSpot = fileLineNumberGet2(info.fptSpotList, "#");
	linfo.P  = (mrcImageParaTypeRealCoord*)memoryAllocate
		(sizeof(mrcImageParaTypeRealCoord)*linfo.numberOfSpot, "in main");
	fseek(info.fptSpotList, 0L, SEEK_SET);
	for(i=0; i<linfo.numberOfSpot; i++) {
		stringGetFromFile(s, "in main", info.fptSpotList, stdout, 3);
		linfo.P[i].x = stringGetNthRealData(s, 1, " ,\t");
		linfo.P[i].y = stringGetNthRealData(s, 2, " ,\t");
		linfo.P[i].z = stringGetNthRealData(s, 3, " ,\t");
	}	
	linfo.radius = info.radius; 

/* Main Routin */
	lmrcFFTIQEstimation(&mrc, &linfo, info.mode);

/* Output */	
	for(i=0; i<linfo.numberOfSpot; i++) {
		fprintf(info.fptOut, "%10.2f %10.2f %10.2f %10.2f %5d %10.2g %10.2g %5d\n", 
			linfo.P[i].x, linfo.P[i].y, linfo.P[i].z, linfo.IQ[i], (int)(linfo.IQ[i]+0.5),
			linfo.Peak[i], linfo.Back[i], (int)(linfo.Count[i]+0.5));
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

int
lmrcFFTIQEstimation(mrcImage* mrc, lmrcFFTIQEstimationInfo* linfo, int mode)   
{
	mrcImageParaTypeReal X, Y, Z;
	int i;
	double peak;
	double back;
	double data;
	int count;
	mrcImageParaTypeReal minZ, maxZ;

	linfo->IQ    = (double*)memoryAllocate(sizeof(double)*linfo->numberOfSpot, "in main");
	linfo->Peak  = (double*)memoryAllocate(sizeof(double)*linfo->numberOfSpot, "in main");
	linfo->Back  = (double*)memoryAllocate(sizeof(double)*linfo->numberOfSpot, "in main");
	linfo->Count = (double*)memoryAllocate(sizeof(double)*linfo->numberOfSpot, "in main");
	for(i=0; i<linfo->numberOfSpot; i++) {
		mrcPixelDataGet(mrc, linfo->P[i].x, linfo->P[i].y, linfo->P[i].z, &peak, 
			mrcPixelMag, mrcPixelHowNearest);
		back = count = 0;
		for(X=linfo->P[i].x-linfo->radius-1; X<=linfo->P[i].x+linfo->radius+1; X++) {
		for(Y=linfo->P[i].y-linfo->radius-1; Y<=linfo->P[i].y+linfo->radius+1; Y++) {
		if(mrc->HeaderN.z<=1) {
			minZ=0;
			maxZ=0;
		} else {
			minZ = linfo->P[i].z-linfo->radius-1;
			maxZ = linfo->P[i].z+linfo->radius+1;
		}
		for(Z=minZ; Z<=maxZ; Z++) {
			if(SQR(X-linfo->P[i].x)
			  +SQR(Y-linfo->P[i].y)
			  +SQR(Z-linfo->P[i].z)>=SQR(linfo->radius-0.5) 
			 &&SQR(X-linfo->P[i].x)
			  +SQR(Y-linfo->P[i].y)
			  +SQR(Z-linfo->P[i].z)<SQR(linfo->radius+0.5))  {
			  	DEBUGPRINT3("%f %f %f\n", X, Y, Z);
				mrcPixelDataGet(mrc, X, Y, Z, &data, mrcPixelMag, mrcPixelHowNearest);
				back += data;
				count++;
			}
		}
		}
		}
		back /= count;
		linfo->IQ[i] = 7*back/(peak-back);
		linfo->Peak[i] = peak;
		linfo->Back[i] = back;
		linfo->Count[i] = count;
	}
}

