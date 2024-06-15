/*
# mrcFFTFibreDiagram : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcFFTFibreDiagram
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

typedef struct lmrcFFTFibreDiagramInfo {
	float a;
	int   b;
} lmrcFFTFibreDiagramInfo;

typedef enum lmrcFFTFibreDiagramMode {
	lmrcFFTFibreDiagramModeRZ=0
} lmrcFFTFibreDiagramMode;

extern void lmrcFFTFibreDiagram(mrcImage* out, mrcImage* in, lmrcFFTFibreDiagramInfo* linfo, int mode);

int
main(int argc, char* argv[]) 
{
	mrcImage in;
	mrcImage out; 
	mrcFFTFibreDiagramInfo info;
	lmrcFFTFibreDiagramInfo linfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.In, "in main", 0); 

	lmrcFFTFibreDiagram(&out, &in, &linfo, info.mode);

	mrcFileWrite(&out, info.Out, "in main", 0); 
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "  -mode 0 : average PHI-axis to express RZ space\n");
}

void 
lmrcFFTFibreDiagram(mrcImage* out, mrcImage* in, lmrcFFTFibreDiagramInfo* linfo, int mode)
{
	mrcImage inFFT;		
	mrcImage count;
	mrcImageParaTypeReal X, Y, Z;
	mrcImageParaTypeReal R, dstR1, dstR2, dstZ;
	double delR, delX, delY;
	double data, data1;

	if(IsImage(in, "lmrcFFTFibreDiagram", 0)) {
		lmrcImageFFT(&inFFT, in, 0);
	} else if(IsFT(in, "lmrcFFTFibreDiagram", 0)) {
		inFFT = *in;	
	} else {
		fprintf(stderr,"Not Supported Mode :%d", in->HeaderMode); 
		exit(EXIT_FAILURE);
	}

	mrcDefaultHeaderValueSet(out);	
	out->HeaderLength.x = inFFT.HeaderLength.x;
	out->HeaderLength.y = inFFT.HeaderLength.z;
	out->HeaderLength.z = inFFT.HeaderLength.z;
	out->HeaderMode = mrcFloatImage;
	out->HeaderN.x = inFFT.HeaderN.x;
	out->HeaderN.y = inFFT.HeaderN.z;
	out->HeaderN.z = 1;
	delX = 1.0/(in->HeaderLength.x*in->HeaderN.x);
	delY = 1.0/(in->HeaderLength.y*in->HeaderN.y);
	delR = delX;

	mrcInit(out, NULL);
	count.Header.Cont = out->Header.Cont;
	mrcInit(&count, NULL);

	for(R=0; R<out->HeaderN.x; R++) {
	for(Z=0; Z<out->HeaderN.z; Z++) {
		mrcPixelDataSet(out,    R, Z, 0, 0, mrcPixelRePart);
		mrcPixelDataSet(&count, R, Z, 0, 0, mrcPixelRePart);
	}
	}	

	mrcFileWrite(out, "/tmp/test.init", "test", 0); 

	for(Z=-inFFT.HeaderN.z/2; Z< inFFT.HeaderN.z/2; Z++) {
	for(Y=-inFFT.HeaderN.y/2; Y< inFFT.HeaderN.y/2; Y++) {
	for(X=0;                  X<=inFFT.HeaderN.x/2; X++) {
		R = (SQR(X*delX)+SQR(Y*delY))/SQR(delR);	
		if(0<R) {
			R = (int)(sqrt(R)+0.5);
		} else {
			R = 0;	
		}
		if(R<out->HeaderN.x/2) {
			dstR1=(+R)+out->HeaderN.x/2;
			dstR2=(-R)+out->HeaderN.x/2;
			dstZ =  Z +inFFT.HeaderN.z/2;
			
			mrcPixelDataGet(&inFFT, X, Y,    Z, &data,  mrcPixelMag,    mrcPixelHowNearest); 
			mrcPixelDataGet(out,    dstR1, dstZ, 0, &data1, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataSet(out,    dstR1, dstZ, 0, data+data1, mrcPixelRePart);
			mrcPixelDataSet(out,    dstR2, dstZ, 0, data+data1, mrcPixelRePart);
	
			mrcPixelDataGet(&count, dstR1, dstZ, 0, &data,  mrcPixelRePart, mrcPixelHowNearest); 
			mrcPixelDataSet(&count, dstR1, dstZ, 0, data+1, mrcPixelRePart);
			mrcPixelDataSet(&count, dstR2, dstZ, 0, data+1, mrcPixelRePart);
		}
	}
	}
	}

	mrcFileWrite(out, "/tmp/test.raw", "test", 0); 

	for(R=0; R<out->HeaderN.x; R++) {
	for(Z=0; Z<out->HeaderN.y; Z++) {
		mrcPixelDataGet(&count, R, Z, 0, &data,  mrcPixelRePart, mrcPixelHowNearest); 
		if(0<data) {
			mrcPixelDataGet(out, R, Z, 0, &data1, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataSet(out, R, Z, 0, data1/data, mrcPixelRePart); 
		}
	}
	}	

	mrcFileWrite(&count, "/tmp/test.count", "test", 0); 
	mrcImageFree(&count, "for count");

}
