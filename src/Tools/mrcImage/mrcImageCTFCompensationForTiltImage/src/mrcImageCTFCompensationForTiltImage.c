/*
# mrcImageCTFCompensationForTiltImage : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageCTFCompensationForTiltImage
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
#include "File.h"
#include "eosString.h"
#include "mrcImage.h"
#include "lmrcImageROI2D.h"
#include "lmrcImageMontage.h"
	 


/*
Example:
typedef struct lmrcImageCTFCompensationForTiltImageInfo {
	float a;
	int   b;
} lmrcImageCTFCompensationForTiltImageInfo;

typedef enum lmrcImageCTFCompensationForTiltImageMode {
	a=0,
	b=1
} lmrcImageCTFCompensationForTiltImageMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImageCTFCompensationForTiltImageInfo info;
	lmrcImageROIsInfo linfo;
	mrcImage in;
	mrcImage *rois;
	mrcImage out;
	double pixelData, pixelDataBuff, pixelDataSum, test;
	double padSize = 0.0;
	int    padNumber = 0;
	int    i,j,k;
	double centerx = 0.0;
	double centery =0.0;
	double weight = 0.0;
	
	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	if(info.flagInfo) {
	    lmrcImageROIsInformationGet(info.fptInfo, &linfo);
	} else {
		fprintf(stderr, "No information to extract ROIs\n");
		exit(EXIT_FAILURE);
	}

	// FileRead
	mrcFileRead(&in, info.In, "main", 0);

	// OutFile
	out.Header.Cont = in.Header.Cont;	
	out.HeaderMode = mrcFloatImage;
	mrcInit(&out, NULL);

	// InFile:: BufferSize
	in.HeaderMode = mrcFloatImage;
	mrcInit(&in, NULL);
	DEBUGPRINT2("%d %d\n", in.HeaderN.x,  in.HeaderN.y);

	rois = (mrcImage*)memoryAllocate(sizeof(mrcImage)*linfo.numROI, "in main (rois)");
	
	for(k=0; k < linfo.numROI; k++) {
		if( (k % 10) == 0){
			fprintf(stderr,"%3d/%3d\n",k,linfo.numROI);
		}
		mrcFileRead(&(rois[k]), linfo.ROI[k].FileName, "main", 0);
		centerx = (linfo.ROI[k].brx - linfo.ROI[k].blx)/2.0;
		centery = (linfo.ROI[k].try - linfo.ROI[k].bry)/2.0;
		for(i = 0; i < linfo.ROI[k].brx - linfo.ROI[k].blx ; i++){
			for(j = 0; j < linfo.ROI[k].try - linfo.ROI[k].bry ; j++){
				weight = ( ((centerx - fabs(centerx - i))/centerx) * ((centery - fabs(centery - j))/centery) );
				pixelData = 0.0;
				pixelDataBuff = 0.0;

				mrcPixelDataGet(&(rois[k]), i,                     j,                    0.0, &pixelData,     mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(&out,       i + linfo.ROI[k].blx , j + linfo.ROI[k].bly, 0.0, &pixelDataBuff, mrcPixelRePart, mrcPixelHowNearest);

				pixelDataSum = pixelData * weight + pixelDataBuff;
				mrcPixelDataSet(&out, i + linfo.ROI[k].blx , j +  linfo.ROI[k].bly, 0.0, pixelDataSum, mrcPixelRePart);

				mrcPixelDataGet(&in, i + linfo.ROI[k].blx , j +  linfo.ROI[k].bly, 0.0, &pixelDataBuff, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataSet(&in, i + linfo.ROI[k].blx , j +  linfo.ROI[k].bly, 0.0, pixelDataBuff + weight, mrcPixelRePart);
			}
		}
	}

    // Cut Reagion
	for( i = 0 + info.cut; i < in.HeaderN.x - info.cut; i++){
		for( j = 0 + info.cut ; j < in.HeaderN.y - info.cut; j++){
			mrcPixelDataGet(&in,  i, j, 0.0, &pixelDataBuff, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(&out, i, j, 0.0, &pixelData,     mrcPixelRePart, mrcPixelHowNearest);
			DEBUGPRINT5("%4d %4d %7.2f %3.2f %7.2f \n", i, j, pixelData, pixelDataBuff, pixelData/pixelDataBuff);
			if(pixelDataBuff > 0.0){
				mrcPixelDataSet(&out, i, j, 0.0, pixelData / pixelDataBuff, mrcPixelRePart);
				padSize += pixelData / pixelDataBuff;
				padNumber ++;
			}
		}
	}

	// Padding 
	for( i = 0 ; i < in.HeaderN.x ; i++){
		for( j = 0; j < in.HeaderN.y; j++){
			mrcPixelDataGet(&out, i, j, 0.0, &pixelData, mrcPixelRePart, mrcPixelHowNearest);
			if(pixelData == 0.0){
				mrcPixelDataSet(&out, i, j, 0.0, padSize/padNumber, mrcPixelRePart);
			}
		}
	}

	// File Write 
	mrcFileWrite(&out, info.Out, "main", 0);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
