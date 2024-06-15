/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImagePad ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImagePad 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImagePad ver%I%; Date:%D% %Z%";
#undef DEBUG
#include "genUtil.h"
#include "./lmrcImagePad.h"
#include "./lmrcImageCalcArea.h"
#include "./lmrcImageTriming.h"
#include "./lmrcImageBinarization.h"
#include "./lmrcImageEdge.h"

void
lmrcImagePad(mrcImage* out, mrcImage* in, lmrcImagePadInfo* info, lmrcImagePadMode mode)
{
	out->Header    = in->Header;
	out->HeaderN.x = info->Width;
	out->HeaderN.y = info->Height;
	mrcInit(out, NULL);
	
	switch(mode) {
		case lmrcImagePadModeAverage: {
			__lmrcImagePad0(out, in, info, 0);
			break;
		}
		case lmrcImagePadModeAveragedYAxis: {
			__lmrcImagePad1(out, in, info, 0);
			break;
		}
		case lmrcImagePadModeDynamicAveragedYAxis: {
			__lmrcImagePad2(out, in, info, 0);
			break;
		}
		case lmrcImagePadModeDynamicAveragedXYAxis: {
			__lmrcImagePad16(out, in, info, 0);
			break;
		}
		case lmrcImagePadModeAveragedEdge: {
			__lmrcImagePad3(out, in, info, 0);
			break;
		}
		case lmrcImagePadModeBottomLeft: {
			__lmrcImagePad4(out, in, info, 0);
			break;
		}
		case lmrcImagePadModeCenterWithoutAveraging: {
			__lmrcImagePad5(out, in, info, 0);
			break;
		}
		case lmrcImagePadModeBottomLeftWithoutAveraging: {
			__lmrcImagePad6(out, in, info, 0);
			break;
		}
		case lmrcImagePadModeAveragedOutsideCircle: {
			__lmrcImagePad7(out, in, info, 0);
			break;
		}
		case lmrcImagePadModeAveragedOutsideRing: {
			__lmrcImagePad8(out, in, info, 0);
			break;
		}
		case lmrcImagePadModeByValue: {
			__lmrcImagePad9(out, in, info, 0);
			break;
		}
		case lmrcImagePadModePeripheryMaskingByValue: {
			__lmrcImagePad10(out, in, info, 0);
			break;
		}
		case lmrcImagePadModeNormalizedByBgAvgAndBgAvgOffset: {
			__lmrcImagePad11(out, in, info, 0);
			break;
		}
		case lmrcImagePadModeNormalizedByImgVarAndImgAvgOffset: {
			__lmrcImagePad12(out, in, info, 0);
			break;
		}
		case lmrcImagePadModeNormalizedByBgVarAndBgAvgOffset: {
			__lmrcImagePad13(out, in, info, 0);
			break;
		}
		case lmrcImagePadModeNormalizedByDifferenceBeteweenImgAvgAndBgAvg: {
			__lmrcImagePad14(out, in, info, 0);
			break;
		}
		case lmrcImagePadModeTiltedImageCircleAverage: {
			__lmrcImagePadTiltImage(out, in, info, 0);
			break;
		}
		default: {
			fprintf(stderr, "Not supported Mode in lmrcImagePad: %d\n", mode);
			exit(EXIT_FAILURE);
		}
	}
}

void
lmrcImagePadModePrint(FILE* fpt)
{
    fprintf(fpt, "%d: Pad average density(Image Center)\n", lmrcImagePadModeAverage);
    fprintf(fpt, "%d: Pad average density of x=0 and x=MAX(x)(Image Center)\n", lmrcImagePadModeAveragedYAxis);
    fprintf(fpt, "%d: Pad dynamic average density of x=0 and x=MAX(x)(Image Center)\n", lmrcImagePadModeDynamicAveragedYAxis);
    fprintf(fpt, "%d: Pad average density of x=0,MAX(x) and y=0,MAX(y), (Image Center)\n", lmrcImagePadModeAveragedEdge);
    fprintf(fpt, "%d: Pad average density of bottom left\n", lmrcImagePadModeBottomLeft);
    fprintf(fpt, "%d: Pad value (Image Center):Image Value(No Change)\n", lmrcImagePadModeCenterWithoutAveraging);
    fprintf(fpt, "%d: Pad value of bottom left:Image Value(No Change)\n", lmrcImagePadModeBottomLeftWithoutAveraging);
    fprintf(fpt, "%d: Pad value estimated from outside circle\n", lmrcImagePadModeAveragedOutsideCircle);
    fprintf(fpt, "%d: Pad value estimated from outside ring: -AWMin -AMax\n", lmrcImagePadModeAveragedOutsideRing);
    fprintf(fpt, "%d: Pad value is Value (Currently the same as %d)\n", lmrcImagePadModeByValue, lmrcImagePadModeCenterWithoutAveraging);
    fprintf(fpt, "%d: Periphery Masking Using ExpectedValue \n", lmrcImagePadModePeripheryMaskingByValue);
    fprintf(fpt, "%d: Normalized Padding using (I(x,y)-avg(bg))/avg(bg))\n", lmrcImagePadModeNormalizedByBgAvgAndBgAvgOffset);
    fprintf(fpt, "%d: Normalized Padding using (I(x,y)-avg(I))/sqrt(var(I)))\n", lmrcImagePadModeNormalizedByImgVarAndImgAvgOffset);
    fprintf(fpt, "%d: Normalized Padding using (I(x,y)-avg(bg))/sqrt(var(bg)))\n", lmrcImagePadModeNormalizedByBgVarAndBgAvgOffset);
    fprintf(fpt, "%d: Normalized Padding using (I(x,y)-avg(bg))/(avg(I)-avg(bg))\n", lmrcImagePadModeNormalizedByDifferenceBeteweenImgAvgAndBgAvg);
    fprintf(fpt, "%d: Tilted Image Circle Average: Need two values of TiltAxisAngle TiltAngle \n", lmrcImagePadModeTiltedImageCircleAverage);
    fprintf(fpt, "%d: Pad dynamic average density of x=0,MAX(x) and y=0,Max(y)(Image Center)\n", lmrcImagePadModeDynamicAveragedXYAxis);
}
/*
	Pad
*/

void
__lmrcImagePadTiltImage(mrcImage* out, mrcImage* in, lmrcImagePadInfo* info, long mode)
{
	mrcImageParaTypeReal x, y;
	mrcImageParaTypeReal sx, sy;
	mrcImageParaTypeReal cx, cy;
	mrcImageParaTypeReal lx, ly;
	double data;
	double offset;
	int n;
	double r;
	/*
	out->Header = in->Header;
	mrcInit(out, NULL);
	*/
	DEBUGPRINT2("Tilt: Axis %f Angle %f\n", info->TiltAxisAngle*DEGREE, info->TiltAngle*DEGREE);	
	lx = in->HeaderN.x/2.0;
	ly = in->HeaderN.y*cos(info->TiltAngle)/2.0;
	cx = (in->HeaderN.x-1)/2.0; 
	cy = (in->HeaderN.y-1)/2.0; 

	DEBUGPRINT4("TiltImage: L %f %f, C %f %f\n", lx, ly, cx, cy);	
	n=0;
	offset = 0; 
 	for(y=0; y<in->HeaderN.y; y++) {
	for(x=0; x<in->HeaderN.x; x++) {
		mrcPixelDataGet(in, x, y, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
		sx = (x-cx)*cos(-info->TiltAxisAngle) - (y-cy)*sin(-info->TiltAxisAngle);
		sy = (x-cx)*sin(-info->TiltAxisAngle) + (y-cy)*cos(-info->TiltAxisAngle);
		r =SQR(sx/lx)+SQR(sy/ly);
		if(1<=r && r <= 1.2 ) {
			n++;
			offset+=data;
		}
	}
	}
	offset /= n;
	DEBUGPRINT2("Offset: %f N: %d\n", offset, n);	
 	for(y=0; y<out->HeaderN.y; y++) {
	for(x=0; x<out->HeaderN.x; x++) {
		mrcPixelDataGet(in, x, y, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
	
		sx = (x-cx)*cos(-info->TiltAxisAngle) - (y-cy)*sin(-info->TiltAxisAngle);
		sy = (x-cx)*sin(-info->TiltAxisAngle) + (y-cy)*cos(-info->TiltAxisAngle);
		
		if(SQR(sx/lx)+SQR(sy/ly)<=1) {
			mrcPixelDataSet(out, x, y, 0.0,  data-offset, mrcPixelRePart);
		} else {
			mrcPixelDataSet(out, x, y, 0.0,  info->Value, mrcPixelRePart);
		}
	}
	}
}

void 
__lmrcImagePad0(mrcImage* out, mrcImage* in, lmrcImagePadInfo* info, long mode)
{
	double data;
	mrcImageParaTypeReal x, y, delta, offsetx, offsety;
	mrcImageParaTypeReal dstx, dsty;

	mrcStatDataSet(in, 0);
	delta = info->Value - in->HeaderAMean;
	DEBUGPRINT3("__lmrcImagePad0:  %f = %f - %f\n", delta, info->Value, in->HeaderAMean);

	for(x=0; x<out->HeaderN.x; x++) {
		for(y=0; y<out->HeaderN.y; y++) {
			mrcPixelDataSet(out, x, y, 0.0, info->Value, mrcPixelRePart);
		}
	}

	offsetx = (out->HeaderN.x - in->HeaderN.x)/2.0;
	offsety = (out->HeaderN.y - in->HeaderN.y)/2.0;

 	for(x=0; x<in->HeaderN.x; x++) {
		for(y=0; y<in->HeaderN.y; y++) {
			dstx = x + offsetx;
			dsty = y + offsety;
			if(   0 <= dstx && dstx < out->HeaderN.x 
			   && 0 <= dsty && dsty < out->HeaderN.y) {
				mrcPixelDataGet(in,  x, y, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataSet(out, dstx, dsty, 0.0, data+delta, mrcPixelRePart);
			}
		}
	}
}

/*
	Pad mean along X = 0, X=Xmax 
*/
void 
__lmrcImagePad1(mrcImage* out, mrcImage* in, lmrcImagePadInfo* info, long mode)
{

	double data, average;
	mrcImageParaTypeReal x, y, delta, offsetx, offsety;
	mrcImageParaTypeReal dstx, dsty;

	average = 0.0;	
	for(y=0; y<in->HeaderN.y; y++) {
		mrcPixelDataGet(in,  0.0, y, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
		average += data;
		mrcPixelDataGet(in,  in->HeaderN.x-1, y, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
		average += data;
	}
	average /= (2*in->HeaderN.y);
	delta = info->Value - average;

	for(x=0; x<out->HeaderN.x; x++) {
		for(y=0; y<out->HeaderN.y; y++) {
			mrcPixelDataSet(out, x, y, 0.0, info->Value, mrcPixelRePart);
		}
	}

	offsetx = (out->HeaderN.x - in->HeaderN.x)/2.0;
	offsety = (out->HeaderN.y - in->HeaderN.y)/2.0;

	for(x=0; x<in->HeaderN.x; x++) {
		for(y=0; y<in->HeaderN.y; y++) {
			dstx = x + offsetx;
			dsty = y + offsety;
			if(   0 <= dstx && dstx < out->HeaderN.x 
			   && 0 <= dsty && dsty < out->HeaderN.y) {
				mrcPixelDataGet(in,  x, y, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataSet(out, dstx, dsty, 0.0, data+delta, mrcPixelRePart);
			}
		}
	}
}

/* 
	Pad mead along X=0, X=Xmax, Y=0, Y=Ymax
*/
void 
__lmrcImagePad3(mrcImage* out, mrcImage* in, lmrcImagePadInfo* info, long mode)
{

	double data, average;
	mrcImageParaTypeReal x, y, delta, offsetx, offsety;
	mrcImageParaTypeReal dstx, dsty;

	average = 0.0;	
	for(y=0; y<in->HeaderN.y; y++) {
		mrcPixelDataGet(in,  0.0, y, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
		average += data;
		mrcPixelDataGet(in,  in->HeaderN.x-1, y, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
		average += data;
	}
	for(x=0; x<in->HeaderN.x; x++) {
		mrcPixelDataGet(in,  x, 0.0, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
		average += data;
		mrcPixelDataGet(in,  x, in->HeaderN.y-1, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
		average += data;
	}
	average /= (2*in->HeaderN.x + 2*in->HeaderN.y);
	delta = info->Value - average;
	DEBUGPRINT2("av: %f ; delta: %f\n", average, delta);
	for(x=0; x<out->HeaderN.x; x++) {
		for(y=0; y<out->HeaderN.y; y++) {
			mrcPixelDataSet(out, x, y, 0.0, info->Value, mrcPixelRePart);
		}
	}

	offsetx = (out->HeaderN.x - in->HeaderN.x)/2.0;
	offsety = (out->HeaderN.y - in->HeaderN.y)/2.0;

	for(x=0; x<in->HeaderN.x; x++) {
		for(y=0; y<in->HeaderN.y; y++) {
			dstx = x + offsetx;
			dsty = y + offsety;
			if(   0 <= dstx && dstx < out->HeaderN.x 
			   && 0 <= dsty && dsty < out->HeaderN.y) {
				mrcPixelDataGet(in,  x, y, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataSet(out, dstx, dsty, 0.0, data+delta, mrcPixelRePart);
			}
		}
	}
}

void 
__lmrcImagePad2(mrcImage* out, mrcImage* in, lmrcImagePadInfo* info, long mode)
{
	double data;
	double averageLeft;
	double averageRight;
	mrcImageParaTypeReal* deltaRight;
	mrcImageParaTypeReal* deltaLeft;
	mrcImageParaTypeReal x, y, offsetx, offsety;
	mrcImageParaTypeReal y2;
	mrcImageParaTypeInteger count;
	mrcImageParaTypeReal dstx, dsty;
	double WinSize;

	if(in->HeaderN.x<=1) {
		fprintf(stderr, "Not supported : N.x = 1 : in __lmrcImagePad2 \n");
		return;
	}
	WinSize = info->AWSize/in->HeaderLength.y/2.0;

	deltaLeft  = (mrcImageParaTypeReal*)memoryAllocate(sizeof(mrcImageParaTypeReal)*in->HeaderN.y, "in __lmrcImagePad2");
	deltaRight = (mrcImageParaTypeReal*)memoryAllocate(sizeof(mrcImageParaTypeReal)*in->HeaderN.y, "in __lmrcImagePad2");

	for(y=0; y<in->HeaderN.y; y++) {
		averageLeft  = 0.0;	
		averageRight = 0.0;	
		count   = 0;
		for(y2=MAX(0, y-WinSize); y2<=MIN(in->HeaderN.y-1, y+WinSize); y2++) {
			mrcPixelDataGet(in,  0.0, y2, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
			averageLeft  += data;
			mrcPixelDataGet(in,  in->HeaderN.x-1, y2, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
			averageRight += data;
			count += 1;
		}
		averageLeft  /= (count);
		averageRight /= (count);
		deltaLeft[(int)y]  = info->Value - averageLeft;
		deltaRight[(int)y] = info->Value - averageRight;
	}

	for(x=0; x<out->HeaderN.x; x++) {
		for(y=0; y<out->HeaderN.y; y++) {
			mrcPixelDataSet(out, x, y, 0.0, info->Value, mrcPixelRePart);
		}
	}

	offsetx = (out->HeaderN.x - in->HeaderN.x)/2.0;
	offsety = (out->HeaderN.y - in->HeaderN.y)/2.0;

	for(x=0; x<in->HeaderN.x; x++) {
		for(y=0; y<in->HeaderN.y; y++) {
			dstx = x + offsetx;
			dsty = y + offsety;
			if(   0 <= dstx && dstx < out->HeaderN.x 
			   && 0 <= dsty && dsty < out->HeaderN.y) {
				mrcPixelDataGet(in,  x, y, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
				data = data + ((in->HeaderN.x - 1 - x)*deltaLeft[(int)y] + x*deltaRight[(int)y])/(in->HeaderN.x-1);
				mrcPixelDataSet(out, dstx, dsty, 0.0, data, mrcPixelRePart);
			}
		}
	}
}

void 
__lmrcImagePad16(mrcImage* out, mrcImage* in, lmrcImagePadInfo* info, long mode)
{
	double data;
	double averageLeft;
	double averageRight;
	double averageTop;
	double averageBottom;
	mrcImageParaTypeReal* deltaRight;
	mrcImageParaTypeReal* deltaLeft;
	mrcImageParaTypeReal* deltaTop;
	mrcImageParaTypeReal* deltaBottom;
	mrcImageParaTypeReal x, y, offsetx, offsety;
	mrcImageParaTypeReal y2;
	mrcImageParaTypeReal x2;
	mrcImageParaTypeInteger count;
	mrcImageParaTypeReal dstx, dsty;
	double WinSize;

	if(in->HeaderN.x<=1) {
		fprintf(stderr, "Not supported : N.x = 1 : in __lmrcImagePad2 \n");
		return;
	}
	WinSize = info->AWSize/in->HeaderLength.y/2.0;

	deltaLeft  = (mrcImageParaTypeReal*)memoryAllocate(sizeof(mrcImageParaTypeReal)*in->HeaderN.y, "in __lmrcImagePad2");
	deltaRight = (mrcImageParaTypeReal*)memoryAllocate(sizeof(mrcImageParaTypeReal)*in->HeaderN.y, "in __lmrcImagePad2");

	deltaTop = (mrcImageParaTypeReal*)memoryAllocate(sizeof(mrcImageParaTypeReal)*in->HeaderN.x, "in __lmrcImagePad2");
	deltaBottom = (mrcImageParaTypeReal*)memoryAllocate(sizeof(mrcImageParaTypeReal)*in->HeaderN.x, "in __lmrcImagePad2");

	for(y=0; y<in->HeaderN.y; y++) {
		averageLeft  = 0.0;	
		averageRight = 0.0;	
		count   = 0;
		for(y2=MAX(0, y-WinSize); y2<=MIN(in->HeaderN.y-1, y+WinSize); y2++) {
			mrcPixelDataGet(in,  0.0, y2, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
			averageLeft  += data;
			mrcPixelDataGet(in,  in->HeaderN.x-1, y2, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
			averageRight += data;
			count += 1;
		}
		averageLeft  /= (count);
		averageRight /= (count);
		deltaLeft[(int)y]  = info->Value - averageLeft;
		deltaRight[(int)y] = info->Value - averageRight;
	}

	for(x=0; x<in->HeaderN.x; x++) {
		averageTop = 0.0;	
		averageBottom= 0.0;	
		count   = 0;
		for(x2=MAX(0, x-WinSize); x2<=MIN(in->HeaderN.x-1, x+WinSize); x2++) {
			mrcPixelDataGet(in,  x2, 0.0, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
			averageBottom += data;
			mrcPixelDataGet(in,  x2, in->HeaderN.x-1, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
			averageTop  += data;
			count += 1;
		}
		averageTop    /= (count);
		averageBottom /= (count);
		deltaTop[(int)x]  = info->Value - averageTop;
		deltaBottom[(int)x] = info->Value - averageBottom;
	}

	for(x=0; x<out->HeaderN.x; x++) {
		for(y=0; y<out->HeaderN.y; y++) {
			mrcPixelDataSet(out, x, y, 0.0, info->Value, mrcPixelRePart);
		}
	}

	offsetx = (out->HeaderN.x - in->HeaderN.x)/2.0;
	offsety = (out->HeaderN.y - in->HeaderN.y)/2.0;

	for(x=0; x<in->HeaderN.x; x++) {
		for(y=0; y<in->HeaderN.y; y++) {
			dstx = x + offsetx;
			dsty = y + offsety;
			if(   0 <= dstx && dstx < out->HeaderN.x 
			   && 0 <= dsty && dsty < out->HeaderN.y) {
				mrcPixelDataGet(in,  x, y, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
				data = data + 
                    (((in->HeaderN.y - 1 - y)*deltaBottom[(int)x] + y*deltaTop[  (int)x])  /(in->HeaderN.y-1)
                    +((in->HeaderN.x - 1 - x)*deltaLeft[  (int)y] + x*deltaRight[(int)y])/(in->HeaderN.x-1))/2.0;
				mrcPixelDataSet(out, dstx, dsty, 0.0, data, mrcPixelRePart);
			}
		}
	}
}

void 
__lmrcImagePad4(mrcImage* out, mrcImage* in, lmrcImagePadInfo* info, long mode)
{
	double delta;
	double data;
	double avg;
	double total;
	double PadSize;
	mrcImageParaTypeReal x, y;

	
	mrcStatDataSet(in, 0);
	delta = info->Value - in->HeaderAMean;

	for(x=0; x<out->HeaderN.x; x++) {
		for(y=0; y<out->HeaderN.y; y++) {
			mrcPixelDataSet(out, x, y, 0.0, info->Value, mrcPixelRePart);
		}
	}	

	for(x=0; x<in->HeaderN.x; x++) {
		for(y=0; y<in->HeaderN.y; y++) {
			if(x<out->HeaderN.x 
			 &&y<out->HeaderN.y) { 
				mrcPixelDataGet(in,  x, y, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataSet(out, x, y, 0.0, data+delta, mrcPixelRePart);
			}
		}
	}
}

void 
__lmrcImagePad5(mrcImage* out, mrcImage* in, lmrcImagePadInfo* info, long mode)
{
	double data;
	mrcImageParaTypeReal x, y, delta, offsetx, offsety;
	mrcImageParaTypeReal dstx, dsty;

	for(x=0; x<out->HeaderN.x; x++) {
		for(y=0; y<out->HeaderN.y; y++) {
			mrcPixelDataSet(out, x, y, 0.0, info->Value, mrcPixelRePart);
		}
	}

	offsetx = (out->HeaderN.x - in->HeaderN.x)/2.0;
	offsety = (out->HeaderN.y - in->HeaderN.y)/2.0;

	for(x=0; x<in->HeaderN.x; x++) {
		for(y=0; y<in->HeaderN.y; y++) {
			dstx = x + offsetx;
			dsty = y + offsety;
			if(   0 <= dstx && dstx < out->HeaderN.x 
			   && 0 <= dsty && dsty < out->HeaderN.y) {
				mrcPixelDataGet(in,  x, y, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataSet(out, dstx, dsty, 0.0, data, mrcPixelRePart);
			}
		}
	}
}


void 
__lmrcImagePad6(mrcImage* out, mrcImage* in, lmrcImagePadInfo* info, long mode)
{
	double delta;
	double data;
	double avg;
	double total;
	double PadSize;
	mrcImageParaTypeReal x, y;

	
	for(x=0; x<out->HeaderN.x; x++) {
		for(y=0; y<out->HeaderN.y; y++) {
			mrcPixelDataSet(out, x, y, 0.0, info->Value, mrcPixelRePart);
		}
	}	

	for(x=0; x<in->HeaderN.x; x++) {
		for(y=0; y<in->HeaderN.y; y++) {
			if(x<out->HeaderN.x 
			 &&y<out->HeaderN.y) { 
				mrcPixelDataGet(in,  x, y, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataSet(out, x, y, 0.0, data, mrcPixelRePart);
			}
		}
	}
}

void 
__lmrcImagePad7(mrcImage* out, mrcImage* in, lmrcImagePadInfo* info, long mode)
{
	double delta;
	double data;
	double avg;
	double total;
	double PadSize;
	mrcImageParaTypeReal x, y;
	mrcImageParaTypeReal offsetx, offsety;
	mrcImageParaTypeReal dstx, dsty;
	
	DEBUGPRINT("__lmrcImagePad7\n");	
	for(x=0; x<out->HeaderN.x; x++) {
		for(y=0; y<out->HeaderN.y; y++) {
			mrcPixelDataSet(out, x, y, 0.0, info->Value, mrcPixelRePart);
		}
	}	
	/* calc average */
	avg = 0;
	total = 0;
	for(x=0; x<in->HeaderN.x; x++) {
		for(y=0; y<in->HeaderN.y; y++) {
			if(SQR(x-in->HeaderN.x/2.0)/SQR(in->HeaderN.x/2.0) 
			  +SQR(y-in->HeaderN.y/2.0)/SQR(in->HeaderN.y/2.0)>=1) {
				mrcPixelDataGet(in,  x, y, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
				avg += data;
				total++;
			}
		}
	}
	avg /= total;
	DEBUGPRINT3("Average %f := %f/%f", avg, avg*total, total);

	offsetx = (out->HeaderN.x - in->HeaderN.x)/2.0;
	offsety = (out->HeaderN.y - in->HeaderN.y)/2.0;
	for(x=0; x<in->HeaderN.x; x++) {
		for(y=0; y<in->HeaderN.y; y++) {
			if(SQR(x-in->HeaderN.x/2.0)/SQR(in->HeaderN.x/2.0) 
			  +SQR(y-in->HeaderN.y/2.0)/SQR(in->HeaderN.y/2.0)<1) {
				mrcPixelDataGet(in,  x, y, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
				data -= avg;
				dstx = x + offsetx;  
				dsty = y + offsety;  
				if(dstx < -0.5) {
					dstx = 0;
				} else if(out->HeaderN.x - 0.5 < dstx) {
					dstx = out->HeaderN.x - 1;
				}
				if(dsty < -0.5) {
					dsty = 0;
				} else if(out->HeaderN.y - 0.5 < dsty) {
					dsty = out->HeaderN.y - 1;
				}
				mrcPixelDataSet(out, dstx, dsty, 0.0,  data, mrcPixelRePart);
			} 
		}
	}
}

void 
__lmrcImagePad8(mrcImage* out, mrcImage* in, lmrcImagePadInfo* info, long mode)
{
	double delta;
	double data;
	double avg;
	double total;
	double PadSize;
	mrcImageParaTypeReal x, y;
	mrcImageParaTypeReal offsetx, offsety;
	mrcImageParaTypeReal dstx, dsty;
	
	DEBUGPRINT("__lmrcImagePad8\n");	
	for(x=0; x<out->HeaderN.x; x++) {
		for(y=0; y<out->HeaderN.y; y++) {
			mrcPixelDataSet(out, x, y, 0.0, info->Value, mrcPixelRePart);
		}
	}	
	/* calc average */
	avg = 0;
	total = 0;
	for(x=0; x<in->HeaderN.x; x++) {
		for(y=0; y<in->HeaderN.y; y++) {
			if(SQR(x-in->HeaderN.x/2.0)+SQR(y-in->HeaderN.y/2.0)<=SQR(info->AWMax) 
			 &&SQR(x-in->HeaderN.x/2.0)+SQR(y-in->HeaderN.y/2.0)>=SQR(info->AWMin)) {
				mrcPixelDataGet(in,  x, y, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
				avg += data;
				total++;
			}
		}
	}
	avg /= total;
	DEBUGPRINT3("Average %f := %f/%f", avg, avg*total, total);

	offsetx = (out->HeaderN.x - in->HeaderN.x)/2.0;
	offsety = (out->HeaderN.y - in->HeaderN.y)/2.0;
	for(x=0; x<in->HeaderN.x; x++) {
		for(y=0; y<in->HeaderN.y; y++) {
			if(SQR(x-in->HeaderN.x/2.0)+SQR(y-in->HeaderN.y/2.0)<=SQR(info->AWMin)) {
				mrcPixelDataGet(in,  x, y, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
				data -= avg;
				dstx = x + offsetx;  
				dsty = y + offsety;  
				if(dstx < -0.5) {
					dstx = 0;
				} else if(out->HeaderN.x - 0.5 < dstx) {
					dstx = out->HeaderN.x - 1;
				}
				if(dsty < -0.5) {
					dsty = 0;
				} else if(out->HeaderN.y - 0.5 < dsty) {
					dsty = out->HeaderN.y - 1;
				}
				mrcPixelDataSet(out, dstx, dsty, 0.0,  data, mrcPixelRePart);
			} 
		}
	}
}

void 
__lmrcImagePad9(mrcImage* out, mrcImage* in, lmrcImagePadInfo* info, long mode)
{
	double data;
	mrcImageParaTypeReal x, y, offsetx, offsety;
	mrcImageParaTypeReal dstx, dsty;

	mrcStatDataSet(in, 0);

	for(x=0; x<out->HeaderN.x; x++) {
		for(y=0; y<out->HeaderN.y; y++) {
			mrcPixelDataSet(out, x, y, 0.0, info->Value, mrcPixelRePart);
		}
	}

	offsetx = (out->HeaderN.x - in->HeaderN.x)/2.0;
	offsety = (out->HeaderN.y - in->HeaderN.y)/2.0;

 	for(x=0; x<in->HeaderN.x; x++) {
		for(y=0; y<in->HeaderN.y; y++) {
			dstx = x + offsetx;
			dsty = y + offsety;
			if(   0 <= dstx && dstx < out->HeaderN.x 
			   && 0 <= dsty && dsty < out->HeaderN.y) {
				mrcPixelDataGet(in,  x, y, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataSet(out, dstx, dsty, 0.0, data, mrcPixelRePart);
			}
		}
	}
}


void 
__lmrcImagePad10(mrcImage* out, mrcImage* in, lmrcImagePadInfo* info, long mode)
{
	double data, data0, data1, data2, data3, data4;
	mrcImageParaTypeReal x, y, offsetx, offsety;
	mrcImageParaTypeReal dstx, dsty;
	double avg, std, ExpectedValue;
	int total;
	mrcImage maskImage, areaImage, labelImage, smoothImage, trimImage, binImage, weightImage;

	mrcStatDataSet(in, 0);

	/* calc average */
	avg = 0;
	total = 0;
	for(x=0; x<in->HeaderN.x; x++) {
		for(y=0; y<in->HeaderN.y; y++) {
			if(SQR(x-in->HeaderN.x/2.0)+SQR(y-in->HeaderN.y/2.0)<=SQR(info->AWMax) 
			 &&SQR(x-in->HeaderN.x/2.0)+SQR(y-in->HeaderN.y/2.0)>=SQR(info->AWMin)) {
				mrcPixelDataGet(in,  x, y, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
				avg += data;
				total++;
			}
		}
	}
	avg /= total;

	/* calc standard deviation */
	total = 0;
	std = 0;
	for(x=0; x<in->HeaderN.x; x++) {
		for(y=0; y<in->HeaderN.y; y++) {
			if(SQR(x-in->HeaderN.x/2.0)+SQR(y-in->HeaderN.y/2.0)<=SQR(info->AWMax) 
			 &&SQR(x-in->HeaderN.x/2.0)+SQR(y-in->HeaderN.y/2.0)>=SQR(info->AWMin)) {
				mrcPixelDataGet(in,  x, y, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
				std += SQR(data-avg);
				total++;
			}
		}
	}
	std /= total;
	std = sqrt(std);

	maskImage.Header    = in->Header;
	mrcInit(&maskImage, NULL);

	/* Set 0.0 in periphery as an areaForMasking */
	for(x=0; x<maskImage.HeaderN.x; x++) {
		for(y=0; y<maskImage.HeaderN.y; y++) {
			if(SQR(x-maskImage.HeaderN.x/2.0)+SQR(y-maskImage.HeaderN.y/2.0)<=SQR(info->AWMax) 
			 &&SQR(x-maskImage.HeaderN.x/2.0)+SQR(y-maskImage.HeaderN.y/2.0)>=SQR(info->AWMin)) {
				mrcPixelDataSet(&maskImage, x, y, 0.0, 0.0, mrcPixelRePart); /* In periphery */
			} else {
				mrcPixelDataSet(&maskImage, x, y, 0.0, 1.0, mrcPixelRePart); /* On an object */
			}
		}
	}
	/* Make an areaForMasking elarger */
	while(1) {
		total = 0;
		for(x=0; x<maskImage.HeaderN.x; x++) {
			for(y=0; y<maskImage.HeaderN.y; y++) {
				mrcPixelDataGet(&maskImage,  x, y, 0.0, &data,  mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(in,          x, y, 0.0, &data0, mrcPixelRePart, mrcPixelHowNearest);
				if(fabs(data-1)<1e-6 
				 &&fabs(data0-avg)<3.0*std) { /* On the object but the same deviation as periphery */ 
					mrcPixelDataGet(&maskImage,  x+1, y-1, 0.0, &data1, mrcPixelRePart, mrcPixelHowNearest);
					mrcPixelDataGet(&maskImage,  x+1, y+1, 0.0, &data2, mrcPixelRePart, mrcPixelHowNearest);
					mrcPixelDataGet(&maskImage,  x-1, y-1, 0.0, &data3, mrcPixelRePart, mrcPixelHowNearest);
					mrcPixelDataGet(&maskImage,  x-1, y+1, 0.0, &data4, mrcPixelRePart, mrcPixelHowNearest);
					if(fabs(data1)<1e-6
					 ||fabs(data2)<1e-6
					 ||fabs(data3)<1e-6
					 ||fabs(data4)<1e-6) {
						mrcPixelDataSet(&maskImage,  x, y, 0.0, 0.0, mrcPixelRePart);
						total++;
					} 
				}
			}
		}
		DEBUGPRINT1("Total: %d\n", total);
		if(total==0) {
			break;
		}
	}
	
	{ /* Median Filter */
		lmrcImageSmoothingInfo linfo;
		linfo.mode = 1;
		linfo.sx = 5;
		linfo.sy = 5;
		linfo.sz = 1;
		lmrcImageSmoothing(&smoothImage, &maskImage, &linfo, 0);
	}

	lmrcImageTriming(&trimImage, &smoothImage, 8, 2, 0);
	lmrcImageCalcArea(&areaImage, &labelImage, &trimImage, 4, 0);
	{
		lmrcImageBinarizationInfo linfo;
		linfo.thresHold = areaImage.HeaderAMax - 1e-6;
		linfo.value     = 1;
		lmrcImageBinarization(&binImage, &areaImage, linfo, 0); 
	}

#ifdef DEBUG
	mrcFileWrite(&maskImage, "/tmp/maskImage", "maskImage", 0);
	mrcFileWrite(&areaImage, "/tmp/areaImage", "areaImage", 0);
	mrcFileWrite(&labelImage, "/tmp/labelImage", "labelImage", 0);
	mrcFileWrite(&trimImage, "/tmp/trimImage", "trimImage", 0);
#endif
	for(x=0; x<out->HeaderN.x; x++) {
		for(y=0; y<out->HeaderN.y; y++) {
			mrcPixelDataSet(out, x, y, 0.0, info->Value, mrcPixelRePart);
		}
	}
	
	offsetx = (out->HeaderN.x - in->HeaderN.x)/2.0;
	offsety = (out->HeaderN.y - in->HeaderN.y)/2.0;

	if(info->flagExpectedValue) {
		ExpectedValue = info->ExpectedValue;
	} else {
		double avg = 0;	
		int    total = 0;
		float*  edge;

		total = 0;
 		for(x=0; x<in->HeaderN.x; x++) {
			for(y=0; y<in->HeaderN.y; y++) {
				dstx = x + offsetx;
				dsty = y + offsety;
				if(   1 <= dstx && dstx < out->HeaderN.x-1 
				   && 1 <= dsty && dsty < out->HeaderN.y-1) { /* Reject Edges */
					if(lmrcImageIsEdge(&binImage,  x, y, 0.0, 4, 0)) {
						total++;
					}
				}
			}
		}

		edge = (float*)memoryAllocate(sizeof(float)*total, "in lmrcImagePad");
		total = 0;
		ExpectedValue = 0;
 		for(x=0; x<in->HeaderN.x; x++) {
			for(y=0; y<in->HeaderN.y; y++) {
				dstx = x + offsetx;
				dsty = y + offsety;
				if(   1 <= dstx && dstx < out->HeaderN.x-1 
				   && 1 <= dsty && dsty < out->HeaderN.y-1) { /* Reject Edges */
					mrcPixelDataGet(in,         x, y, 0.0, &data,  mrcPixelRePart, mrcPixelHowNearest);
					if(lmrcImageIsEdge(&binImage,  x, y, 0.0, 4, 0)) {
						DEBUGPRINT1("Edge: %f\n", data);
						edge[total] = data;
						total++;
					}
				}
			}
		}
		{
			extern int __lmrcImagePad10Compare(const void* a, const void* b);
			qsort(edge, total, sizeof(float), __lmrcImagePad10Compare);
		}
		if(total!=0) {
			ExpectedValue = edge[0];
		}
		DEBUGPRINT1("ExpectedValue: %lf\n", ExpectedValue);
	}

 	for(x=0; x<in->HeaderN.x; x++) {
		for(y=0; y<in->HeaderN.y; y++) {
			dstx = x + offsetx;
			dsty = y + offsety;
			if(   0 <= dstx && dstx < out->HeaderN.x 
			   && 0 <= dsty && dsty < out->HeaderN.y) {
				mrcPixelDataGet(in,        x, y, 0.0, &data,  mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(&binImage, x, y, 0.0, &data0, mrcPixelRePart, mrcPixelHowNearest);
				if(fabs(data0)<1e-6) {
					mrcPixelDataSet(out, dstx, dsty, 0.0, info->Value, mrcPixelRePart);
				} else {
					mrcPixelDataSet(out, dstx, dsty, 0.0, data - ExpectedValue + info->Value, mrcPixelRePart);
				}
			}
		}
	}
}

int
__lmrcImagePad10Compare(const void* a, const void* b)
{
	if(*(float*)a<*(float*)b) {
		return -1;
	} else if(*(float*)a==*(float*)b) {
		return 0;
	} else {
		return 1;
	}
}

/*
Sorzano et al. Ultramicroscopy 101 (2004) 129-138
	Carazo Group

	Pad11-15
*/

/*
	II(x,y) = (I(x,y)-avg(bg))/avg(bg)
*/
void
__lmrcImagePad11(mrcImage* out, mrcImage* in, lmrcImagePadInfo* info, long mode)
{

	double data;
	double avgbg, varbg;
	double avgim, varim;
	int count;
	mrcImageParaTypeReal x, y, delta, offsetx, offsety;
	mrcImageParaTypeReal dstx, dsty;

	avgbg= 0.0;	
	count = 0;
	for(x=0; x<in->HeaderN.x; x++) {
	for(y=0; y<in->HeaderN.y; y++) {
		if(1<=SQR(x/in->HeaderN.x)+SQR(y/in->HeaderN.y)) {
			mrcPixelDataGet(in,  x, y, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
			avgbg += data;	
			count++;
		}
	}
	}
	avgbg /= count;

	for(x=0; x<out->HeaderN.x; x++) {
		for(y=0; y<out->HeaderN.y; y++) {
			mrcPixelDataSet(out, x, y, info->Value, info->Value, mrcPixelRePart);
		}
	}

	offsetx = (out->HeaderN.x - in->HeaderN.x)/2.0;
	offsety = (out->HeaderN.y - in->HeaderN.y)/2.0;

	for(x=0; x<in->HeaderN.x; x++) {
		for(y=0; y<in->HeaderN.y; y++) {
			dstx = x + offsetx;
			dsty = y + offsety;
			if(   0 <= dstx && dstx < out->HeaderN.x 
			   && 0 <= dsty && dsty < out->HeaderN.y) {
				mrcPixelDataGet(in,  x, y, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
				data = (data - avgbg)/avgbg + info->Value;
				mrcPixelDataSet(out, dstx, dsty, 0.0, data, mrcPixelRePart);
			}
		}
	}
}

/*
	II(x,y) = (I(x,y)-avg(I))/sqrt(var(I))
*/
void
__lmrcImagePad12(mrcImage* out, mrcImage* in, lmrcImagePadInfo* info, long mode)
{

	double data;
	double avgbg, varbg;
	double avgim, varim;
	int count;
	mrcImageParaTypeReal x, y, delta, offsetx, offsety;
	mrcImageParaTypeReal dstx, dsty;

	avgim= 0.0;	
	varim= 0.0;	
	count = 0;
	for(x=0; x<in->HeaderN.x; x++) {
	for(y=0; y<in->HeaderN.y; y++) {
		mrcPixelDataGet(in,  x, y, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
		avgim += data;	
		varim += SQR(data);	
		count++;
	}
	}
	avgim /= count;
	varim = varim/count - SQR(avgim);

	for(x=0; x<out->HeaderN.x; x++) {
		for(y=0; y<out->HeaderN.y; y++) {
			mrcPixelDataSet(out, x, y, info->Value, info->Value, mrcPixelRePart);
		}
	}

	offsetx = (out->HeaderN.x - in->HeaderN.x)/2.0;
	offsety = (out->HeaderN.y - in->HeaderN.y)/2.0;

	for(x=0; x<in->HeaderN.x; x++) {
		for(y=0; y<in->HeaderN.y; y++) {
			dstx = x + offsetx;
			dsty = y + offsety;
			if(   0 <= dstx && dstx < out->HeaderN.x 
			   && 0 <= dsty && dsty < out->HeaderN.y) {
				mrcPixelDataGet(in,  x, y, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
				data = (data - avgim)/sqrt(varim) + info->Value;
				mrcPixelDataSet(out, dstx, dsty, 0.0, data, mrcPixelRePart);
			}
		}
	}
}

/*
	II(x,y) = (I(x,y)-avg(bg))/sqrt(var(bg))
*/
void
__lmrcImagePad13(mrcImage* out, mrcImage* in, lmrcImagePadInfo* info, long mode)
{

	double data;
	double avgbg, varbg;
	double avgim, varim;
	int count;
	mrcImageParaTypeReal x, y, delta, offsetx, offsety;
	mrcImageParaTypeReal dstx, dsty;

	avgbg= 0.0;	
	varbg= 0.0;	
	count = 0;
	for(x=0; x<in->HeaderN.x; x++) {
	for(y=0; y<in->HeaderN.y; y++) {
		if(1<=SQR(x/in->HeaderN.x)+SQR(y/in->HeaderN.y)) {
			mrcPixelDataGet(in,  x, y, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
			avgbg += data;	
			varbg += SQR(data);	
			count++;
		}
	}
	}
	avgbg /= count;
	varbg = varbg/count - SQR(avgbg);

	for(x=0; x<out->HeaderN.x; x++) {
		for(y=0; y<out->HeaderN.y; y++) {
			mrcPixelDataSet(out, x, y, info->Value, info->Value, mrcPixelRePart);
		}
	}

	offsetx = (out->HeaderN.x - in->HeaderN.x)/2.0;
	offsety = (out->HeaderN.y - in->HeaderN.y)/2.0;

	for(x=0; x<in->HeaderN.x; x++) {
		for(y=0; y<in->HeaderN.y; y++) {
			dstx = x + offsetx;
			dsty = y + offsety;
			if(   0 <= dstx && dstx < out->HeaderN.x 
			   && 0 <= dsty && dsty < out->HeaderN.y) {
				mrcPixelDataGet(in,  x, y, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
				data = (data - avgbg)/sqrt(varbg) + info->Value;
				mrcPixelDataSet(out, dstx, dsty, 0.0, data, mrcPixelRePart);
			}
		}
	}
}

/*
	II(x,y) = (I(x,y)-avg(bg))/(avg(I) - avg(bg))
*/
void
__lmrcImagePad14(mrcImage* out, mrcImage* in, lmrcImagePadInfo* info, long mode)
{

	double data;
	double avgbg, varbg;
	double avgim, varim;
	int count;
	mrcImageParaTypeReal x, y, delta, offsetx, offsety;
	mrcImageParaTypeReal dstx, dsty;

	avgbg= 0.0;	
	avgim= 0.0;	
	count = 0;
	for(x=0; x<in->HeaderN.x; x++) {
	for(y=0; y<in->HeaderN.y; y++) {
		if(1<=SQR(x/in->HeaderN.x)+SQR(y/in->HeaderN.y)) {
			mrcPixelDataGet(in,  x, y, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
			avgbg += data;	
			count++;
		}
		avgim += data;	
	}
	}
	avgbg /= count;
	avgim /= (in->HeaderN.x*in->HeaderN.y);

	for(x=0; x<out->HeaderN.x; x++) {
		for(y=0; y<out->HeaderN.y; y++) {
			mrcPixelDataSet(out, x, y, info->Value, info->Value, mrcPixelRePart);
		}
	}

	offsetx = (out->HeaderN.x - in->HeaderN.x)/2.0;
	offsety = (out->HeaderN.y - in->HeaderN.y)/2.0;

	for(x=0; x<in->HeaderN.x; x++) {
		for(y=0; y<in->HeaderN.y; y++) {
			dstx = x + offsetx;
			dsty = y + offsety;
			if(   0 <= dstx && dstx < out->HeaderN.x 
			   && 0 <= dsty && dsty < out->HeaderN.y) {
				mrcPixelDataGet(in,  x, y, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
				data = (data - avgbg)/(avgim - avgbg) + info->Value;
				mrcPixelDataSet(out, dstx, dsty, 0.0, data, mrcPixelRePart);
			}
		}
	}
}

