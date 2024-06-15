/*
# mrcImageTiltAxisSearchHelp : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageTiltAxisSearchHelp
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
#include "Memory.h"
#include "eosString.h"
#include "mrcImage.h"

typedef struct lmrcImageTiltAxisSearchHelpInfo {
	/* Input */	
	int imageNum;

	/* Global */
	mrcImageParaTypeRealCoord  globalAxisPosition;
	mrcImageParaTypeReal       globalAxisAngleYaw;      /* Axis Rotation */
	mrcImageParaTypeReal       globalAxisAnglePitch;    /* Axis Tilting */

	/* Each Image */
	mrcImageParaTypeReal*      TiltAngle;
	mrcImageParaTypeRealCoord* relativeAxisPosition;
	mrcImageParaTypeReal*      relativeAxisAngleYaw;    /* Axis Rotation */
	mrcImageParaTypeReal*      relativeAxisAnglePitch;  /* Axis Tilting  */

	mrcPixelDataHowToGet       InterpolationMode;
} lmrcImageTiltAxisSearchHelpInfo;

typedef struct lmrcImage1Dto2DInfo {
	int imageNum;
	mrcPixelDataHowToGet       InterpolationMode;

	mrcImageParaTypeReal*      TiltAngle;

	mrcImageParaTypeReal Rmin;
	mrcImageParaTypeReal Rmax;
} lmrcImage1Dto2DInfo;

/*
typedef enum lmrcImageTiltAxisSearchHelpMode {
	a=0,
	b=1
} lmrcImageTiltAxisSearchHelpMode;
*/

extern void lmrcImage1DStackExtractedFromTiltImage(
				mrcImage* out, 
				mrcImage* outEnlarged, 
				mrcImage*  in, 
				lmrcImageTiltAxisSearchHelpInfo* linfo, int mode);

extern void lmrcImage1Dto2D(
				mrcImage* out2D, 
				mrcImage* out1D, 
				lmrcImage1Dto2DInfo linfo, 
				int mode); 


static char s[2048];
int
main(int argc, char* argv[]) 
{
	mrcImageTiltAxisSearchHelpInfo   info;
	lmrcImageTiltAxisSearchHelpInfo linfo;
	lmrcImage1Dto2DInfo             linfo2; 
	mrcImage* in;
	mrcImage out1D;
	mrcImage out1DEnlarged;
	mrcImage out2D;
	int i;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	linfo.globalAxisPosition.x = info.OriginX;
	linfo.globalAxisPosition.y = info.OriginY;
	linfo.globalAxisPosition.z = info.OriginZ;
	linfo.globalAxisAngleYaw   = info.AxisAngleYaw;
	linfo.globalAxisAnglePitch = info.AxisAnglePitch;

	linfo.imageNum = info.flagInList;
	in = (mrcImage*)memoryAllocate(sizeof(mrcImage)*linfo.imageNum, "mrcImageList in main");	
	linfo.TiltAngle              = (mrcImageParaTypeReal*)memoryAllocate(sizeof(mrcImageParaTypeReal)*linfo.imageNum, "mrcImageList in main");	
	linfo.relativeAxisPosition   = (mrcImageParaTypeRealCoord*)memoryAllocate(sizeof(mrcImageParaTypeRealCoord)*linfo.imageNum, "mrcImageList in main");	
	linfo.relativeAxisAngleYaw   = (mrcImageParaTypeReal*)memoryAllocate(sizeof(mrcImageParaTypeReal)*linfo.imageNum, "mrcImageList in main");	
	linfo.relativeAxisAnglePitch = (mrcImageParaTypeReal*)memoryAllocate(sizeof(mrcImageParaTypeReal)*linfo.imageNum, "mrcImageList in main");	

	linfo.InterpolationMode = info.InterpolationMode;
	fseek(info.fptInListList, 0L, SEEK_SET);
	for(i=0; i<linfo.imageNum; i++) {
		mrcFileRead(&in[i], info.InList[i], "InList in main", 0);
		stringGetFromFile(s, "", info.fptInListList, stderr, 3);
		linfo.TiltAngle[i]  = stringGetNthRealData(s, 2, " \t")*RADIAN;
		linfo.relativeAxisAngleYaw[i]   = stringGetNthRealData(s, 3, " \t")*RADIAN;
		linfo.relativeAxisAnglePitch[i] = stringGetNthRealData(s, 4, " \t")*RADIAN;
		linfo.relativeAxisPosition[i].x = stringGetNthRealData(s, 5, " \t");
		linfo.relativeAxisPosition[i].y = stringGetNthRealData(s, 6, " \t");
		linfo.relativeAxisPosition[i].z = stringGetNthRealData(s, 7, " \t");
	}

/* */
	lmrcImage1DStackExtractedFromTiltImage(&out1D, &out1DEnlarged, in, &linfo, info.mode);
	if(info.flagOut2D) {
		linfo2.imageNum  = linfo.imageNum;
		linfo2.InterpolationMode = linfo.InterpolationMode;
		linfo2.TiltAngle = linfo.TiltAngle;
		linfo2.Rmin = info.Rmin;
		linfo2.Rmax = info.Rmax;
		lmrcImage1Dto2D(&out2D, &out1D, linfo2, info.mode); 
	}

/* */
	if(info.flagOut1D) {
		mrcFileWrite(&out1D, info.Out1D, "Out1D in main", 0);
	}
	if(info.flagOut1DEnlarged) {
		mrcFileWrite(&out1DEnlarged, info.Out1DEnlarged, "Out1DEnlarged in main", 0);
	}
	if(info.flagOut2D) {
		mrcFileWrite(&out2D, info.Out2D, "Out2D in main", 0);
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "-I fileList format\n");
	fprintf(stderr, "filename tiltAngle[degree] relativeTiltAxisYaw[degree] relativeTiltAxisPitch[degree] relativePosX[pixel] relativePosY[pixel] relativePosZ[pixel]\n");
}

void
lmrcImage1DStackExtractedFromTiltImage(mrcImage* out, mrcImage* outEnlarged,  mrcImage* in, lmrcImageTiltAxisSearchHelpInfo* linfo, int mode) 
{
	int i;
	mrcImageParaTypeReal    dstx;
	mrcImageParaTypeInteger dsty;
	mrcImageParaTypeReal srcx, srcy;
	mrcImageParaTypeReal cenx, ceny;
	mrcImageParaTypeRealCoord c;
	mrcImageParaTypeRealCoord p;
	mrcImageParaTypeRealCoord cp;
	mrcImageParaTypeRealCoord ex;
	mrcImageParaTypeRealCoord exe;
	mrcImageParaTypeRealCoord ey;
	mrcImageParaTypeRealCoord eye;
	mrcImageParaTypeRealCoord len;	
	mrcImageParaTypeRealCoord lene;	
	mrcImageParaTypeRealCoord length;	
	mrcImageParaTypeReal angleYaw;
	mrcImageParaTypeReal anglePitch;
	mrcImageParaTypeReal angleRoll;
	double data;

	mrcDefaultHeaderValueSet(out);
	out->HeaderMode = mrcFloatImage;
	out->HeaderN.x  = MIN(in[0].HeaderN.x, in[0].HeaderN.y);
	out->HeaderN.y  = linfo->imageNum;
	out->HeaderLength.x = in[0].HeaderLength.y;
	out->HeaderLength.y = 1;
	out->HeaderLength.z = 1;
	mrcInit(out, NULL);
	outEnlarged->Header = out->Header;
	mrcInit(outEnlarged, NULL);

	// OC 	
	c.x = (in[0].HeaderN.x-1)/2.0;
	c.y = (in[0].HeaderN.y-1)/2.0;
	c.z = 0;

	for(dsty=0; dsty<out->HeaderN.y; dsty++) {
		// OP
		p.x = linfo->globalAxisPosition.x + linfo->relativeAxisPosition[dsty].x; 
		p.y = linfo->globalAxisPosition.y + linfo->relativeAxisPosition[dsty].y;
		p.z = linfo->globalAxisPosition.z + linfo->relativeAxisPosition[dsty].z;
		angleYaw   = linfo->globalAxisAngleYaw   + linfo->relativeAxisAngleYaw[dsty];
		anglePitch = linfo->globalAxisAnglePitch + linfo->relativeAxisAnglePitch[dsty];
		angleRoll  = linfo->TiltAngle[dsty];

		DEBUGPRINT3("ANGLE: %g %g %g\n", angleYaw*DEGREE, anglePitch*DEGREE, angleRoll*DEGREE);
		// CP	
		cp.x = p.x - c.x;
		cp.y = p.y - c.y;
		cp.z = p.z - c.z;
		  	
		// Parallel Axis: ex, tilted axis: exe 
		exe.x = cos(anglePitch)*cos(angleYaw);
		exe.y =                 sin(angleYaw)*cos(angleRoll) + sin(anglePitch)*cos(angleYaw)*sin(angleRoll);
		exe.z =                 sin(angleYaw)*sin(angleRoll) - sin(anglePitch)*cos(angleYaw)*cos(angleRoll);
		lene.x = cp.x*exe.x + cp.y*exe.y + cp.z*exe.z; 
		ex = exe;
		ex.z = 0;
		length.x = sqrt(SQR(ex.x) + SQR(ex.y));
		ex.x = ex.x/length.x;
		ex.y = ex.y/length.x;

		// Vertical Axis: ey, tilted axis: eye
		eye.x = -cos(anglePitch)*sin(angleYaw);
		eye.y =                  cos(angleYaw)*cos(angleRoll) - sin(anglePitch)*sin(angleYaw)*sin(angleRoll);
		eye.z =                  sin(angleYaw)*sin(angleRoll) + sin(anglePitch)*sin(angleYaw)*cos(angleRoll);
		lene.y = cp.x*eye.x + cp.y*eye.y + cp.z*eye.z; 
		ey   = eye;
		ey.z = 0;
		length.y = sqrt(SQR(ey.x) + SQR(ey.y));
		ey.x = ey.x/length.y;
		ey.y = ey.y/length.y;

		for(dstx=0; dstx<out->HeaderN.x; dstx++) {
			len.y = dstx - c.y; 

			DEBUGPRINT2("len.y %g dstx %g\n", len.y, dstx);
			// Same interval	
			srcx = len.y*ey.x + p.x;  
			srcy = len.y*ey.y + p.y;  

			if(-0.5<=srcx && srcx < in[dsty].HeaderN.x - 0.5 
             &&-0.5<=srcy && srcy < in[dsty].HeaderN.y - 0.5) { 
				DEBUGPRINT2("srcx %g srcy %g\n", srcx, srcy);
				mrcPixelDataGet(&in[dsty], srcx, srcy, 0, &data, mrcPixelRePart, linfo->InterpolationMode);
				mrcPixelDataSet(out,       dstx, dsty, 0,  data, mrcPixelRePart);
			}
			// following tilt angle;
			srcx = len.y*eye.x + p.x;  
			srcy = len.y*eye.y + p.y;  

			if(-0.5<=srcx && srcx < in[dsty].HeaderN.x - 0.5 
             &&-0.5<=srcy && srcy < in[dsty].HeaderN.y - 0.5) { 
				DEBUGPRINT2("srcx %g srcy %g\n", srcx, srcy);
				mrcPixelDataGet(&in[dsty],    srcx, srcy, 0, &data, mrcPixelRePart, linfo->InterpolationMode);
				mrcPixelDataSet(outEnlarged,  dstx, dsty, 0,  data, mrcPixelRePart);
			}
		}
	}
}


void 
lmrcImage1Dto2D(mrcImage* out2D, mrcImage* in1DStacked, lmrcImage1Dto2DInfo linfo, int mode)
{
	mrcImageParaTypeReal    srcx;
	mrcImageParaTypeInteger srcy;
	mrcImageParaTypeReal    dstx;
	mrcImageParaTypeReal    dsty;
	mrcImageParaTypeReal    X, Y, R;
	mrcImageParaTypeRealCoord c;
	mrcImageParaTypeRealCoord e;
	double data, re; 
	double data2, im, weight ;
	double delR;
	mrcImage pre; 
	mrcImage fft; 

	pre.Header = in1DStacked->Header;
	pre.HeaderN.y      = pre.HeaderN.x;
	pre.HeaderLength.y = pre.HeaderLength.x;
	mrcInit(&pre, NULL);

	c.x = (pre.HeaderN.x -1)/2.0;
	c.y = (pre.HeaderN.y -1)/2.0;
	for(srcy=0; srcy<in1DStacked->HeaderN.y; srcy++) {
		e.x = cos(linfo.TiltAngle[srcy]);
		e.y = sin(linfo.TiltAngle[srcy]);
		for(dsty=0; dsty<pre.HeaderN.y; dsty++) {
		for(dstx=0; dstx<pre.HeaderN.x; dstx++) {
			srcx = e.x*(dstx - c.x) + e.y*(dsty - c.y) + c.x; 	
			mrcPixelDataGet(in1DStacked, srcx, srcy, 0, &data,  mrcPixelRePart, linfo.InterpolationMode);
			mrcPixelDataGet(&pre,         dstx, dsty, 0, &data2, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataSet(&pre,         dstx, dsty, 0, data+data2, mrcPixelRePart);
		}
		}
	}

	lmrcImageFFT(&fft, &pre, 0);

	delR = 1.0/fft.HeaderLength.x;
	for(Y=-fft.HeaderN.y/2; X< fft.HeaderN.y/2; Y++) {
	for(X=0;                X<=fft.HeaderN.x/2; X++) {
		R = sqrt(SQR(X*delR) + SQR(Y*delR)); 	
		if(R<linfo.Rmin) {
			mrcPixelDataGet(&fft, X, Y, 0, &re, mrcPixelRePart, mrcPixelHowNearest); 
			mrcPixelDataGet(&fft, X, Y, 0, &im, mrcPixelImPart, mrcPixelHowNearest);
			mrcPixelDataSet(&fft, X, Y, 0, re*R, mrcPixelRePart);
			mrcPixelDataSet(&fft, X, Y, 0, im*R, mrcPixelImPart);
		} else if(R<linfo.Rmax) {
			weight = linfo.Rmin*(cos(M_PI*(R - linfo.Rmin)/(linfo.Rmax - linfo.Rmin))+1)/2.0;
			mrcPixelDataGet(&fft, X, Y, 0, &re, mrcPixelRePart, mrcPixelHowNearest); 
			mrcPixelDataGet(&fft, X, Y, 0, &im, mrcPixelImPart, mrcPixelHowNearest);
			mrcPixelDataSet(&fft, X, Y, 0, re*weight, mrcPixelRePart);
			mrcPixelDataSet(&fft, X, Y, 0, im*weight, mrcPixelImPart);
		} else {
			mrcPixelDataSet(&fft, X, Y, 0, 0.0, mrcPixelRePart);
			mrcPixelDataSet(&fft, X, Y, 0, 0.0, mrcPixelImPart);
		}
	}
	}

	lmrcImageFFT(out2D, &fft, 0);
}
