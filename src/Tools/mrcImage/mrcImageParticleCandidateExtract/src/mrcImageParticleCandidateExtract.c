/*
# mrcImageParticleCandidateExtract : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageParticleCandidateExtract
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

typedef enum lmrcImageParticleCandidateExtractMode {
	lmrcImageParticleCandidateExtractModeSphere=0
} lmrcImageParticleCandidateExtractMode;

typedef struct lmrcImageParticleCandidateExtractInfo {
	float RingRadius; // A 
	float RingWidth; // A 
	float Threshold;
	FILE* fptThreshold;
} lmrcImageParticleCandidateExtractInfo;


void lmrcImageParticleCandidateExtract(mrcImage* out, mrcImage* in, lmrcImageParticleCandidateExtractInfo linfo, lmrcImageParticleCandidateExtractMode mode);

int
main(int argc, char* argv[]) 
{
	lmrcImageParticleCandidateExtractInfo linfo;
	mrcImageParticleCandidateExtractInfo   info;
	mrcImage in;
	mrcImage out;

	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

	DEBUGPRINT("Program Start\n");
	linfo.RingRadius = info.RingRadius;
	linfo.RingWidth  = info.RingWidth;
	linfo.Threshold  = info.Threshold;
	linfo.fptThreshold = info.fptoutFileThres;
	mrcFileRead(&in, info.In, "in main", 0);
	
	lmrcImageParticleCandidateExtract(&out, &in, linfo, info.mode);

	mrcFileWrite(&out, info.Out, "in main", 0);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}


void 
lmrcImageParticleCandidateExtract(mrcImage* out, mrcImage* in, lmrcImageParticleCandidateExtractInfo linfo, lmrcImageParticleCandidateExtractMode mode)
{
	mrcImageParaTypeReal x, y, z;
	mrcImageParaTypeReal xx, yy, zz;
	mrcImageParaTypeReal RR, RW;
	double RIN, ROUT;
	double R2;
	double RIN2, ROUT2;
	double testdata, data;
	double sum, sum2;
	double sd, mean;
	double IQ;
	int n;
	int working, all;

	out->Header = in->Header;
	mrcInit(out, NULL);

	// Real Space
	RIN2  = SQR(linfo.RingRadius);
	ROUT2 = SQR(linfo.RingRadius+linfo.RingWidth);

	// Pixel
	RR = MAX(MAX(linfo.RingRadius/in->HeaderLength.x, linfo.RingRadius/in->HeaderLength.y), linfo.RingRadius/in->HeaderLength.z);
	RW = MAX(MAX(linfo.RingWidth /in->HeaderLength.x, linfo.RingWidth /in->HeaderLength.y), linfo.RingWidth /in->HeaderLength.z);
	RIN  = RR;
	ROUT = RR + RW;

	all = in->HeaderN.x*in->HeaderN.y*in->HeaderN.z;
	working = 0;
	for(z=0; z<in->HeaderN.z; z++) {
	for(y=0; y<in->HeaderN.y; y++) {
	for(x=0; x<in->HeaderN.x; x++) {
		if(working*100/all==working*100.0/(double)all) {
			fprintf(stderr, "%d%\n", working*100/all);
		}
		working++;
		mrcPixelDataGet(in, x, y, z, &testdata, mrcPixelRePart, mrcPixelHowNearest);
		sum  = 0;
		sum2 = 0;
		n = 0;
		for(zz=z-ROUT; zz<=z+ROUT; zz++) {
		for(yy=y-ROUT; yy<=y+ROUT; yy++) {
		for(xx=x-ROUT; xx<=x+ROUT; xx++) {
			R2 = SQR((xx-x)*in->HeaderLength.x) + SQR((yy-y)*in->HeaderLength.y) + SQR((zz-z)*in->HeaderLength.z);
			if(RIN2 <= R2 && R2 <= ROUT2) {
				if(-0.5 <= xx && xx < in->HeaderN.x-0.5   
				 &&-0.5 <= yy && yy < in->HeaderN.y-0.5   
				 &&-0.5 <= zz && zz < in->HeaderN.z-0.5) {
					mrcPixelDataGet(in, xx, yy, zz, &data, mrcPixelRePart, mrcPixelHowNearest);
					sum  += data;
					sum2 += data*data;
					n++;
				}
			}
		}
		}
		}
		if(0<n) { 
			mean = sum/n;
			sd = sqrt(sum2/n - SQR(mean));  
			IQ = (testdata - mean)/sd;
			if(0<linfo.Threshold) {
				if(linfo.Threshold<IQ) {
					fprintf(linfo.fptThreshold, "%f %f %f %f\n", x, y, z, IQ);
				}
			} else {
				if(IQ<linfo.Threshold) {
					fprintf(linfo.fptThreshold, "%f %f %f %f\n", x, y, z, IQ);
				}
			}
		} else {
			IQ = 0;
		}
		mrcPixelDataSet(out, x, y, z, IQ, mrcPixelRePart);
	}
	}
	}
}

