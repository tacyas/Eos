/*
# mrcImageFlatFieldCorrection : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageFlatFieldCorrection
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

typedef struct lmrcImageFlatFieldCorrectionInfo {
	float a;
	int   b;
} lmrcImageFlatFieldCorrectionInfo;

typedef enum lmrcImageFlatFieldCorrectionMode {
	a=0,
	b=1
} lmrcImageFlatFieldCorrectionMode;

extern void
lmrcImageFlatFieldCorrection(mrcImage* out, mrcImage* in, mrcImage* flat, mrcImage* dark, lmrcImageFlatFieldCorrectionInfo linfo, int mode);

int
main(int argc, char* argv[]) 
{
	mrcImageFlatFieldCorrectionInfo info;
    mrcImage in;
    mrcImage out;
    mrcImage inFlat;
    mrcImage inDark;
	lmrcImageFlatFieldCorrectionInfo linfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
    mrcFileRead(&in, info.In, "in main", 0);
    mrcFileRead(&inFlat, info.Flat, "in main", 0);
    if(info.flagDark) {
        mrcFileRead(&inDark, info.Dark, "in main", 0);
    } else {
        inDark.Header = in.Header;
        mrcInit(&inDark, NULL);
    }

    lmrcImageFlatFieldCorrection(&out, &in, &inFlat, &inDark, linfo, info.mode);

    mrcFileWrite(&out, info.Out, "in main", 0);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

void
lmrcImageFlatFieldCorrection(mrcImage* out, mrcImage* in, mrcImage* flat, mrcImage* dark, lmrcImageFlatFieldCorrectionInfo linfo, int mode)
{
    mrcImageParaTypeReal x, y, z;
    double data, correction, contrast;
    double f;
    double d;
    double flatSum, darkSum,flatave, darkave, contrastave, ave, sum;
    int n;
    
	if(in->HeaderN.x==flat->HeaderN.x && in->HeaderN.x==dark->HeaderN.x
	 &&in->HeaderN.y==flat->HeaderN.y && in->HeaderN.y==dark->HeaderN.y
	 &&in->HeaderN.z==flat->HeaderN.z && in->HeaderN.z==dark->HeaderN.z) {
        out->Header = in->Header;
        mrcInit(out, NULL);
	} else {
        fprintf(stderr, "Not equal: in(%d, %d, %d), flat(%d, %d, %d), dark(%d, %d, %d)\n",
            in->HeaderN.x, in->HeaderN.y, in->HeaderN.z,
            flat->HeaderN.x, flat->HeaderN.y, flat->HeaderN.z,
            dark->HeaderN.x, dark->HeaderN.y, dark->HeaderN.z);
		exit(EXIT_FAILURE);
	}
    
   flatSum = darkSum = sum = 0;
   for(z=0; z<in->HeaderN.z; z++) {
   for(y=0; y<in->HeaderN.y; y++) { 
   for(x=0; x<in->HeaderN.x; x++) { 
        mrcPixelDataGet(in,       x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
        sum += data;
        mrcPixelDataGet(flat,  x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
        flatSum += data;
        mrcPixelDataGet(dark, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
        darkSum += data;
   }
   }
   }
   n = in->HeaderN.x*in->HeaderN.y*in->HeaderN.z;

   ave     =  sum/n;
   flatave =  flatSum/n;
   darkave =  darkSum/n;
   contrastave = flatave - darkave;

   for(z=0; z<in->HeaderN.z; z++) {
   for(y=0; y<in->HeaderN.y; y++) { 
   for(x=0; x<in->HeaderN.x; x++) { 
        mrcPixelDataGet(in,   x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
        mrcPixelDataGet(flat, x, y, z, &f,    mrcPixelRePart, mrcPixelHowNearest);
        mrcPixelDataGet(dark, x, y, z, &d,    mrcPixelRePart, mrcPixelHowNearest);
        contrast = f - d;
        if(0<contrast) {
            correction = (data - d)/contrast*contrastave + darkave;
        } else {
            correction = darkave;
        }
        mrcPixelDataSet(out, x, y, z, correction, mrcPixelRePart);
   }
   }
   }
}
