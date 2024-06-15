/*
# mrcImageAutoRotationCorrelation3D : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageAutoRotationCorrelation3D
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

#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lmrcImageCorrelation.h"

typedef struct lmrcImageAutoRotationCorrelation3DRange {
	mrcImageParaTypeReal Min;
	mrcImageParaTypeReal Max;
	mrcImageParaTypeReal Delta;
	mrcImageParaTypeInteger N;
} lmrcImageAutoRotationCorrelation3DRange;

typedef struct lmrcImageAutoRotationCorrelation3DInfo {
	lmrcImageAutoRotationCorrelation3DRange Rot1;
	lmrcImageAutoRotationCorrelation3DRange Rot2;
	lmrcImageAutoRotationCorrelation3DRange Rot3;
	char* EulerAngle;

	int flagXrange;
	int flagYrange;
	int flagZrange;
	lmrcImageAutoRotationCorrelation3DRange	Xrange;	
	lmrcImageAutoRotationCorrelation3DRange	Yrange;	
	lmrcImageAutoRotationCorrelation3DRange	Zrange;	

	long CorrelationMode; 
	mrcImage CorMap;
	mrcImage LinearCorMap;
	mrcImage X;
	mrcImage Y;
	mrcImage Z;
	mrcImage BestFit;
	mrcImage BestCorMap;
	mrcImageParaTypeRealCoord BestPosition;
	mrcImageParaTypeReal      BestRot1;
	mrcImageParaTypeReal      BestRot2;
	mrcImageParaTypeReal      BestRot3;

	int RotationMode;
} lmrcImageAutoRotationCorrelation3DInfo;

/*
typedef enum lmrcImageAutoRotationCorrelation3DMode {
	a=0,
	b=1
} lmrcImageAutoRotationCorrelation3DMode;
*/
extern void lmrcImageAutoRotationCorrelation3D(
			mrcImage* tst, mrcImage* ref, 
			lmrcImageAutoRotationCorrelation3DInfo* linfo, int mode);  

int
main(int argc, char* argv[]) 
{
	mrcImageAutoRotationCorrelation3DInfo info;
	lmrcImageAutoRotationCorrelation3DInfo linfo;
	mrcImage in;
	mrcImage ref;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	linfo.EulerAngle = info.EulerAngle;

	linfo.Rot1.Min = info.Rot1Min*RADIAN;
	linfo.Rot1.Max = info.Rot1Max*RADIAN;
	linfo.Rot1.Delta = info.Rot1Delta*RADIAN;
	linfo.Rot1.N = (int)((info.Rot1Max - info.Rot1Min)/info.Rot1Delta + 1);
	linfo.Rot2.Min = info.Rot2Min*RADIAN;
	linfo.Rot2.Max = info.Rot2Max*RADIAN;
	linfo.Rot2.Delta = info.Rot2Delta*RADIAN;
	linfo.Rot2.N = (int)((info.Rot2Max - info.Rot2Min)/info.Rot2Delta + 1);

	linfo.Rot3.Min = info.Rot3Min*RADIAN;
	linfo.Rot3.Max = info.Rot3Max*RADIAN;
	linfo.Rot3.Delta = info.Rot3Delta*RADIAN;
	linfo.Rot3.N = (int)((info.Rot3Max - info.Rot3Min)/info.Rot3Delta + 1);
	linfo.CorrelationMode = info.Mode;
	linfo.RotationMode = info.ModeRotation;

	linfo.flagXrange = info.flagXrangeMin;
	linfo.flagYrange = info.flagYrangeMin;
	linfo.flagZrange = info.flagZrangeMin;

	linfo.Xrange.Min = info.XrangeMin; 
	linfo.Xrange.Max = info.XrangeMax; 
	linfo.Yrange.Min = info.YrangeMin; 
	linfo.Yrange.Max = info.YrangeMax; 
	linfo.Zrange.Min = info.ZrangeMin; 
	linfo.Zrange.Max = info.ZrangeMax; 

	mrcFileRead(&in, info.In, "in main", 0);
	mrcFileRead(&ref, info.Ref, "in main", 0);

	lmrcImageAutoRotationCorrelation3D(&in, &ref, &linfo, info.mode);

	if(info.flagOut) {
		int rot1, rot2, rot3;
		double data, data2, x, y, z;

		for(rot1=0; rot1<linfo.Rot1.N; rot1++) {  
		for(rot2=0; rot2<linfo.Rot2.N; rot2++) {  
		for(rot3=0; rot3<linfo.Rot3.N; rot3++) {  
			mrcPixelDataGet(&linfo.CorMap, rot1, rot2, rot3, 
					&data, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(&linfo.LinearCorMap, rot1, rot2, rot3, 
					&data2, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(&linfo.X, rot1, rot2, rot3, 
					&x, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(&linfo.Y, rot1, rot2, rot3, 
					&y, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(&linfo.Z, rot1, rot2, rot3, 
					&z, mrcPixelRePart, mrcPixelHowNearest);
			fprintf(info.fptOut, 
					"%s %15.6f %15.6f %15.6f Cor %15.6f Linear  %15.6f at %15.6f %15.6f %15.6f\n", 
					linfo.EulerAngle, 
					(rot1*linfo.Rot1.Delta + linfo.Rot1.Min)*DEGREE,
					(rot2*linfo.Rot2.Delta + linfo.Rot2.Min)*DEGREE,
					(rot3*linfo.Rot3.Delta + linfo.Rot3.Min)*DEGREE,
					data, data2, x, y, z);
		}
		}
		}
	}

	if(info.flagCor) {
		mrcFileWrite(&linfo.CorMap, info.Cor, "in main", 0);	
	}

	if(info.flagFit) {
		mrcFileWrite(&linfo.BestFit, info.Fit, "in main", 0);	
	}

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "----- -M  CorrelationMode -----\n");
	lmrcImageCorrelationModePrint(stderr);
	fprintf(stderr, "----- -MR RotationMode -----\n");
	lmrcImageRotation3DModePrint(stderr);
}

void lmrcImageAutoRotationCorrelation3D(
	mrcImage* tst, mrcImage* ref, 
	lmrcImageAutoRotationCorrelation3DInfo* linfo, int mode)
{
	int irot1, irot2, irot3;
	double rot1, rot2, rot3;
	double linear;
	mrcImage tmp; // Rotation Image
	mrcImage shift;
	mrcImage cor;
	mrcImageInformation info;	
	double max=-1;	
	mrcImageParaTypeRealCoord offset;

	if(info.flagXrange || info.flagYrange || info.flagZrange) {
		info.mode = meanOfCentre;
			
		info.flagXrange = linfo->flagXrange;
		info.XrangeMin = linfo->Xrange.Min;
		info.XrangeMax = linfo->Xrange.Max;
		info.flagYrange = linfo->flagYrange;
		info.YrangeMin = linfo->Yrange.Min;
		info.YrangeMax = linfo->Yrange.Max;
		info.flagZrange = linfo->flagZrange;
		info.ZrangeMin = linfo->Zrange.Min;
		info.ZrangeMax = linfo->Zrange.Max;

		info.flagCentre = 1;
		info.CentreX = 0; 
		info.CentreY = 0; 
		info.CentreZ = 0; 
	} else {
		info.mode = meanOfAll;
	}

	DEBUGPRINT3("%d %d %d N for Rotation\n", linfo->Rot1.N, linfo->Rot2.N, linfo->Rot3.N);
	DEBUGPRINT3("Rot1 %f %f %f \n", linfo->Rot1.Min, linfo->Rot1.Max, linfo->Rot1.Delta);
	DEBUGPRINT3("Rot2 %f %f %f \n", linfo->Rot2.Min, linfo->Rot2.Max, linfo->Rot2.Delta);
	DEBUGPRINT3("Rot3 %f %f %f \n", linfo->Rot3.Min, linfo->Rot3.Max, linfo->Rot3.Delta);
	linfo->CorMap.HeaderN.x = linfo->Rot1.N;
	linfo->CorMap.HeaderN.y = linfo->Rot2.N;
	linfo->CorMap.HeaderN.z = linfo->Rot3.N;
	linfo->CorMap.HeaderMode = mrcFloatImage;
	linfo->LinearCorMap.Header = linfo->CorMap.Header;
	linfo->X.Header = linfo->CorMap.Header;
	linfo->Y.Header = linfo->CorMap.Header;
	linfo->Z.Header = linfo->CorMap.Header;
	mrcInit(&linfo->CorMap, NULL);
	mrcInit(&linfo->LinearCorMap, NULL);
	mrcInit(&linfo->X, NULL);
	mrcInit(&linfo->Y, NULL);
	mrcInit(&linfo->Z, NULL);

	linfo->BestCorMap.Image = NULL;
	linfo->BestFit.Image    = NULL;
	for(irot1=0; irot1<linfo->Rot1.N; irot1++) {  
	for(irot2=0; irot2<linfo->Rot2.N; irot2++) {  
	for(irot3=0; irot3<linfo->Rot3.N; irot3++) {  
		rot1 = irot1*linfo->Rot1.Delta + linfo->Rot1.Min;
		rot2 = irot2*linfo->Rot2.Delta + linfo->Rot2.Min;
		rot3 = irot3*linfo->Rot3.Delta + linfo->Rot3.Min;
		DEBUGPRINT3("%f %f %f rot \n", rot1*DEGREE, rot2*DEGREE, rot3*DEGREE);
		lmrcImageRotation3DFollowingEulerAngle(
				&tmp, tst, linfo->EulerAngle, rot1, rot2, rot3, 
				mode, linfo->RotationMode);

		lmrcImageCorrelation(&cor, &tmp, ref, linfo->CorrelationMode);
		lmrcImageInformation(&info, &cor);  
		mrcPixelDataSet(&linfo->CorMap, irot1, irot2, irot3, info.max, mrcPixelRePart);
		mrcPixelDataSet(&linfo->X, irot1, irot2, irot3, info.maxCoord.x, mrcPixelRePart);
		mrcPixelDataSet(&linfo->Y, irot1, irot2, irot3, info.maxCoord.y, mrcPixelRePart);
		mrcPixelDataSet(&linfo->Z, irot1, irot2, irot3, info.maxCoord.z, mrcPixelRePart);
		offset.x = -1*info.maxCoord.x;
		offset.y = -1*info.maxCoord.y;
		offset.z = -1*info.maxCoord.z;
		lmrcImageShift(&shift, &tmp, offset, mode);  
		linear = lmrcImageLinearCorrelation(&shift, ref, 0);
		mrcPixelDataSet(&linfo->LinearCorMap, irot1, irot2, irot3, linear, mrcPixelRePart);

		if(max<info.max) {
			max = info.max;

			if(NULL!=linfo->BestFit.Image) {
				mrcImageFree(&linfo->BestFit,    "in lmrcImageAutoRotationCorrelation3D"); 
			}
			if(NULL!=linfo->BestCorMap.Image) {
				mrcImageFree(&linfo->BestCorMap, "in lmrcImageAutoRotationCorrelation3D"); 
			}
			linfo->BestPosition = info.maxCoord;
			linfo->BestCorMap = cor; 
			linfo->BestFit = shift; 
			linfo->BestRot1 = rot1;
			linfo->BestRot2 = rot2;
			linfo->BestRot3 = rot3;
			fprintf(stderr, "Max: %s %f %f %f at %f %f %f Cor %f %f\n", 
					linfo->EulerAngle, 
					rot1*DEGREE, rot2*DEGREE, rot3*DEGREE, 
					info.maxCoord.x, info.maxCoord.y, info.maxCoord.z,
					max, linear);
		} else {
			mrcImageFree(&shift, "in lmrcImageAutoRotationCorrelation3D"); 
			mrcImageFree(&cor, "in lmrcImageAutoRotationCorrelation3D"); 
		}
#ifdef DEBUG2
		fprintf(stderr, "%s %f %f %f at %f %f %f Cor %f %f\n", 
					linfo->EulerAngle, 
					rot1*DEGREE, rot2*DEGREE, rot3*DEGREE, 
					info.maxCoord.x, info.maxCoord.y, info.maxCoord.z,
					max, linear);
#endif
		mrcImageFree(&tmp, "in lmrcImageAutoRoationCorrelation3D");
	}
	}
	}
}

