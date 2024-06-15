/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageWindowing ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageWindowing 
#%Z% Attention
#%Z%
*/


static char __sccs_id[] = "%Z%lmrcImageWindowing ver%I%; Date:%D% %Z%";
#include <stdlib.h>
#include <math.h>
#undef DEBUG
#include "genUtil.h"

#include "../inc/mrcImage.h"
#include "lmrcImageWindowing.h"

extern void __lmrcImageWindowingMode0(mrcImage* dst, mrcImage* src, lmrcImageWindowingInfo* info, long mode);
extern void __lmrcImageWindowingMode1(mrcImage* dst, mrcImage* src, lmrcImageWindowingInfo* info, long mode);
extern void __lmrcImageWindowingMode2(mrcImage* dst, mrcImage* src, lmrcImageWindowingInfo* info, long mode);
extern void __lmrcImageWindowingRectangleWindow(mrcImage* dst, mrcImage* src, lmrcImageWindowingInfo* info, long mode);
extern void __lmrcImageWindowingHanningWindow(mrcImage* dst, mrcImage* src, lmrcImageWindowingInfo* info, long mode);
extern void __lmrcImageWindowingHammingWindow(mrcImage* dst, mrcImage* src, lmrcImageWindowingInfo* info, long mode);
extern void __lmrcImageWindowingHammingWindow(mrcImage* dst, mrcImage* src, lmrcImageWindowingInfo* info, long mode);
extern void __lmrcImageWindowingBlackmanWindow(mrcImage* dst, mrcImage* src, lmrcImageWindowingInfo* info, long mode);
extern void __lmrcImageWindowingDolphChebyshevWindow(mrcImage* dst, mrcImage* src, lmrcImageWindowingInfo* info, long mode);
extern void __lmrcImageWindowingKaiserWindow(mrcImage* dst, mrcImage* src, lmrcImageWindowingInfo* info, long mode);
extern void __lmrcImageWindowingGaussWindow(mrcImage* dst, mrcImage* src, lmrcImageWindowingInfo* info, long mode);
extern void __lmrcImageWindowingExponentialWindow(mrcImage* dst, mrcImage* src, lmrcImageWindowingInfo* info, long mode);

void
lmrcImageWindowing(mrcImage* dst, mrcImage* src, 
	lmrcImageWindowingInfo* info,
	long mode)
{
	switch(mode&0xf0) {
		case 0x00: {
			info->Offset = 0;
			break;
		}
		case lmrcImageWindowingInfoModeDownToAverage: {
			info->Offset = src->HeaderAMean;
			break;
		}
		default: {
			break;
		 }
	}
	switch(mode&0xf) {
		case lmrcImageWindowingInfoModeCosWindowFixed: {
			__lmrcImageWindowingMode0(dst, src, info, mode);
			break;
		}
		case lmrcImageWindowingInfoModeCosWindowYVariable: {
			__lmrcImageWindowingMode1(dst, src, info, mode);
			break;
		}
		case lmrcImageWindowingInfoModeCosWindowXYVariable: {
			__lmrcImageWindowingMode2(dst, src, info, mode);
			break;
		}
		case lmrcImageWindowingInfoModeRectangleWindow: {
			__lmrcImageWindowingRectangleWindow(dst, src, info, mode);
			break;
		}
		case lmrcImageWindowingInfoModeHanningWindow: {
			__lmrcImageWindowingHanningWindow(dst, src, info, mode);
			break;
		}
		case lmrcImageWindowingInfoModeHammingWindow: {
			__lmrcImageWindowingHammingWindow(dst, src, info, mode);
			break;
		}
		case lmrcImageWindowingInfoModeBlackmanWindow: {
			__lmrcImageWindowingBlackmanWindow(dst, src, info, mode);
			break;
		}
		case lmrcImageWindowingInfoModeDolphChebyshevWindow: {
			__lmrcImageWindowingDolphChebyshevWindow(dst, src, info, mode);
			break;
		}
		case lmrcImageWindowingInfoModeKaiserWindow: {
			__lmrcImageWindowingKaiserWindow(dst, src, info, mode);
			break;
		}
		case lmrcImageWindowingInfoModeGaussWindow: {
			__lmrcImageWindowingGaussWindow(dst, src, info, mode);
			break;
		}
		case lmrcImageWindowingInfoModeExponentialWindow: {
			__lmrcImageWindowingExponentialWindow(dst, src, info, mode);
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode : %ld\n", mode);
			break;
		}
	}
}

void
lmrcImageWindowingModePrint(FILE* fpt)
{
	fprintf(fpt, "%d: Cos Window (Fixed)\n", lmrcImageWindowingInfoModeCosWindowFixed);
	fprintf(fpt, "   90%% windowing:         fixed.   \n");
	fprintf(fpt, "%d: Cos Window (Y-variable)\n", lmrcImageWindowingInfoModeCosWindowYVariable);
	fprintf(fpt, "   Wy: Settings:          variable.\n");
	fprintf(fpt, "%d: Cos Window XY-variable\n", lmrcImageWindowingInfoModeCosWindowXYVariable);
	fprintf(fpt, "   WxMax and Wx                    \n");
	fprintf(fpt, "   WyMax and Wy Settings: variables\n");
	fprintf(fpt, "           x/Nx < WxMax   or    1-WxMax < x/Nx           : 0 \n");
	fprintf(fpt, "   WxMax < x/Nx < Wx      or    1-Wx    < x/Nx < 1-WxMax : cos window  \n");
	fprintf(fpt, "                  Wx   < x/Nx < 1-Wx                     : 1\n");
	fprintf(fpt, "   Wy and WyMax are also used for windowing in the similar manner.\n");
	fprintf(fpt, "    In general, this is called Tukey window.\n");
	fprintf(fpt, "%d: Rectangle Window\n", lmrcImageWindowingInfoModeRectangleWindow);
	fprintf(fpt, "%d: Hanning Window\n", lmrcImageWindowingInfoModeHanningWindow);
	fprintf(fpt, "%d: Hamming Window\n", lmrcImageWindowingInfoModeHammingWindow);
	fprintf(fpt, "%d: Blackman Window\n", lmrcImageWindowingInfoModeBlackmanWindow);
	fprintf(fpt, "%d: Dolph-Chebyshev Window\n", lmrcImageWindowingInfoModeDolphChebyshevWindow);
	fprintf(fpt, "%d: Kaiser Window\n", lmrcImageWindowingInfoModeKaiserWindow);
	fprintf(fpt, "      Wx, Wy corresponding to alpha. As alpha increases, window becomes narrower.\n");
	fprintf(fpt, "%d: Gauss Window\n", lmrcImageWindowingInfoModeGaussWindow);
	fprintf(fpt, "%d: Exponentail Window\n", lmrcImageWindowingInfoModeExponentialWindow);
	fprintf(fpt, ">> Boundary  \n");
	fprintf(fpt, "+0 : To Zero.  \n");
	fprintf(fpt, "+%d: Contrast down around mean.\n", lmrcImageWindowingInfoModeDownToAverage);
}

void 
__lmrcImageWindowingMode0(mrcImage* dst, mrcImage* src, lmrcImageWindowingInfo* info, long mode)
{
	mrcImageParaTypeReal x, y, z;
	double data;
	double offset;
	double weightx;
	double weighty;

	if(src->HeaderN.z!=1) {
		fprintf(stderr, "Not supported N.z : %d\n", src->HeaderN.z);
		return;
	}
	for(y=0; y<src->HeaderN.y; y++) {
		for(x=0; x<src->HeaderN.x; x++) {
			mrcPixelDataGet(src, x, y, 0.0, &data, mrcPixelMag, mrcPixelHowNearest);
	
			if(0.1*src->HeaderN.x < x && x < 0.9*src->HeaderN.x) {
				weightx = 1;	
			} else if(x < 0.1*src->HeaderN.x) {
				weightx = (0.5 - 0.5*cos(M_PI*x/(0.1*src->HeaderN.x)));
			} else if(0.9*src->HeaderN.x < x) {
				weightx = (0.5 + 0.5*cos(M_PI*(x-0.9*src->HeaderN.x)/(0.1*src->HeaderN.x)));
			}
			if(0.1*src->HeaderN.y < y && y < 0.9*src->HeaderN.y) {
				weighty = 1;
			} else if(y < 0.1*src->HeaderN.y) {
				weighty = (0.5 - 0.5*cos(M_PI*y/(0.1*src->HeaderN.y)));
			} else if(0.9*src->HeaderN.y < y) {
				weighty = (0.5 + 0.5*cos(M_PI*(y-0.9*src->HeaderN.y)/(0.1*src->HeaderN.y)));
			}
			data = weightx*weighty*(data - info->Offset) + info->Offset;	
			mrcPixelDataSet(dst, x, y, 0.0, data, mrcPixelMag);
		}
	}
}

void 
__lmrcImageWindowingMode1(mrcImage* dst, mrcImage* src, lmrcImageWindowingInfo* info, long mode)
{
	mrcImageParaTypeReal x, y, z;
	double data;

	if(src->HeaderN.z!=1) {
		fprintf(stderr, "Not supported N.z : %d\n", src->HeaderN.z);
		return;
	}
	for(y=0; y<src->HeaderN.y; y++) {
		for(x=0; x<src->HeaderN.x; x++) {
			mrcPixelDataGet(src, x, y, 0.0, &data, mrcPixelMag, mrcPixelHowNearest);
			
			if(info->flagWy) {
				if(src->HeaderN.y/info->Wy < y) {
					data = info->Offset;
				}
			}

			mrcPixelDataSet(dst, x, y, 0.0, data, mrcPixelMag);
		}
	}
}

void 
__lmrcImageWindowingMode2(mrcImage* dst, mrcImage* src, lmrcImageWindowingInfo* info, long mode)
{
	mrcImageParaTypeReal x, y, z;
	double data;
	double weightx, weighty;
	double Wx, Wy, WxMax, WyMax;

	if(src->HeaderN.z!=1) {
		fprintf(stderr, "Not supported N.z : %d\n", src->HeaderN.z);
		return;
	}

	if(!info->flagWxMax) {
		WxMax = 0;	
	} else {
		WxMax = info->WxMax*src->HeaderN.x;	
	}

	if(!info->flagWyMax) {
		WyMax = 0;	
	} else {
		WyMax = info->WyMax*src->HeaderN.y;	
	}

	if(!info->flagWx) {
		Wx= 0.1;	
	} else {
		Wx = info->Wx;	
	}
	Wx *= src->HeaderN.x;

	if(!info->flagWy) {
		Wy= 0.1;
	} else {
		Wy = info->Wy;
	}
	Wy *= src->HeaderN.y;
	DEBUGPRINT4("Wx %f %f  Wy %f %f\n",Wx, WxMax, Wy, WyMax );
	for(y=0; y<src->HeaderN.y; y++) {
		for(x=0; x<src->HeaderN.x; x++) {
			mrcPixelDataGet(src, x, y, 0.0, &data, mrcPixelMag, mrcPixelHowNearest);
	
			if(x < WxMax || src->HeaderN.x-WxMax < x) {
				weightx = 0;
			} else if(WxMax <=x && x <= Wx ) {
				weightx = 0.5*(cos((Wx - x)/(Wx - WxMax)*M_PI)+1.0);
			} else if(src->HeaderN.x - Wx <= x && x <= src->HeaderN.x - WxMax) {	
				weightx = 0.5*(cos((x - (src->HeaderN.x - Wx ))/(Wx - WxMax)*M_PI)+1.0);
			} else {
				weightx = 1;	
			}
			if(y < WyMax || src->HeaderN.y-WyMax < y) {
				weighty = 0;
			} else if(WyMax<=y && y <= Wy ) {
				weighty = 0.5*(cos((Wy - y)/(Wy - WyMax)*M_PI)+1.0);
			} else if(src->HeaderN.y - Wy <= y && y <= src->HeaderN.y - WyMax) {	
				weighty = 0.5*(cos((y - (src->HeaderN.y - Wy ))/(Wy - WyMax)*M_PI)+1.0);
			} else {
				weighty = 1;	
			}
			data = weightx*weighty*(data - info->Offset) + info->Offset;	
			mrcPixelDataSet(dst, x, y, 0.0, data, mrcPixelMag);
		}
	}
}


void 
__lmrcImageWindowingRectangleWindow(mrcImage* dst, mrcImage* src, lmrcImageWindowingInfo* info, long mode)
{
	mrcImageParaTypeReal x, y, z;
	double data;
	double weightx, weighty;
	double WxMin, WxMax;
	double WyMin, WyMax;

	if(src->HeaderN.z!=1) {
		fprintf(stderr, "Not supported N.z : %d\n", src->HeaderN.z);
		return;
	}
	
	WxMin = src->HeaderN.x*info->Wx;
	WxMax = src->HeaderN.x*(1-info->Wx);
	WyMin = src->HeaderN.y*info->Wy;
	WyMax = src->HeaderN.y*(1-info->Wy);
	
	for(x=0; x<src->HeaderN.x; x++) {
	for(y=0; y<src->HeaderN.y; y++) {
		if(x<WxMin || WxMax <x
		 ||y<WyMin || WyMax <y) {
		 	data = info->Offset;
		} else {	
			mrcPixelDataGet(src, x, y, 0.0, &data, mrcPixelMag, mrcPixelHowNearest);
		}
		mrcPixelDataSet(dst, x, y, 0.0, data, mrcPixelMag);
	}
	}
}


void 
__lmrcImageWindowingHanningWindow(mrcImage* dst, mrcImage* src, lmrcImageWindowingInfo* info, long mode)
{
	mrcImageParaTypeReal x, y, z;
	mrcImageParaTypeReal rx, ry, rz;
	double data;
	double weightx, weighty;
	double WxMin, WxMax, Wx;
	double WyMin, WyMax, Wy;

	if(src->HeaderN.z!=1) {
		fprintf(stderr, "Not supported N.z : %d\n", src->HeaderN.z);
		return;
	}

	Wx    = 1.0 - 2*info->Wx;
	WxMin = src->HeaderN.x*info->Wx;
	WxMax = src->HeaderN.x*(1-info->Wx);

	Wy    = 1.0 - 2*info->Wy;
	WyMin = src->HeaderN.y*info->Wy;
	WyMax = src->HeaderN.y*(1-info->Wy);
	
	for(x=0; x<src->HeaderN.x; x++) {
		rx = (x-(src->HeaderN.x-1)/2)/(src->HeaderN.x*Wx);
	for(y=0; y<src->HeaderN.y; y++) {
		ry = (y-(src->HeaderN.y-1)/2)/(src->HeaderN.y*Wy);

		if(x<WxMin || WxMax <x
		 ||y<WyMin || WyMax <y) {
		 	data = info->Offset;
		} else {	
			weightx = 0.5+0.5*cos(2*M_PI*(rx));	
			weighty = 0.5+0.5*cos(2*M_PI*(ry));	
			mrcPixelDataGet(src, x, y, 0.0, &data, mrcPixelMag, mrcPixelHowNearest);
			data = weightx*weighty*(data - info->Offset) + info->Offset; 
		}
		mrcPixelDataSet(dst, x, y, 0.0, data, mrcPixelMag);
	}
	}
}

void 
__lmrcImageWindowingHammingWindow(mrcImage* dst, mrcImage* src, lmrcImageWindowingInfo* info, long mode)
{
	mrcImageParaTypeReal x, y, z;
	mrcImageParaTypeReal rx, ry, rz;
	double data;
	double weightx, weighty;
	double WxMin, WxMax, Wx;
	double WyMin, WyMax, Wy;

	if(src->HeaderN.z!=1) {
		fprintf(stderr, "Not supported N.z : %d\n", src->HeaderN.z);
		return;
	}

	Wx    = 1.0 - 2*info->Wx;
	WxMin = src->HeaderN.x*info->Wx;
	WxMax = src->HeaderN.x*(1-info->Wx);

	Wy    = 1.0 - 2*info->Wy;
	WyMin = src->HeaderN.y*info->Wy;
	WyMax = src->HeaderN.y*(1-info->Wy);
	
	for(x=0; x<src->HeaderN.x; x++) {
		rx = (x-(src->HeaderN.x-1)/2)/(src->HeaderN.x*Wx);
	for(y=0; y<src->HeaderN.y; y++) {
		ry = (y-(src->HeaderN.y-1)/2)/(src->HeaderN.y*Wy);

		if(x<WxMin || WxMax <x
		 ||y<WyMin || WyMax <y) {
		 	data = info->Offset;
		} else {	
			weightx = 0.54+0.46*cos(2*M_PI*(rx));	
			weighty = 0.54+0.46*cos(2*M_PI*(ry));	
			mrcPixelDataGet(src, x, y, 0.0, &data, mrcPixelMag, mrcPixelHowNearest);
			data = weightx*weighty*(data - info->Offset) + info->Offset; 
		}
		mrcPixelDataSet(dst, x, y, 0.0, data, mrcPixelMag);
	}
	}
}


void 
__lmrcImageWindowingBlackmanWindow(mrcImage* dst, mrcImage* src, lmrcImageWindowingInfo* info, long mode)
{
	mrcImageParaTypeReal x, y, z;
	mrcImageParaTypeReal rx, ry, rz;
	double data;
	double weightx, weighty;
	double WxMin, WxMax, Wx;
	double WyMin, WyMax, Wy;

	if(src->HeaderN.z!=1) {
		fprintf(stderr, "Not supported N.z : %d\n", src->HeaderN.z);
		return;
	}

	Wx    = 1.0 - 2*info->Wx;
	WxMin = src->HeaderN.x*info->Wx;
	WxMax = src->HeaderN.x*(1-info->Wx);

	Wy    = 1.0 - 2*info->Wy;
	WyMin = src->HeaderN.y*info->Wy;
	WyMax = src->HeaderN.y*(1-info->Wy);
	
	for(x=0; x<src->HeaderN.x; x++) {
		rx = (x-(src->HeaderN.x-1)/2)/(src->HeaderN.x*Wx);
	for(y=0; y<src->HeaderN.y; y++) {
		ry = (y-(src->HeaderN.y-1)/2)/(src->HeaderN.y*Wy);

		if(x<WxMin || WxMax <x
		 ||y<WyMin || WyMax <y) {
		 	data = info->Offset;
		} else {	
			weightx = 0.42+0.5*cos(2*M_PI*(rx))+0.08*cos(4*M_PI*(rx));	
			weighty = 0.42+0.5*cos(2*M_PI*(ry))+0.08*cos(4*M_PI*(ry));	
			mrcPixelDataGet(src, x, y, 0.0, &data, mrcPixelMag, mrcPixelHowNearest);
			data = weightx*weighty*(data - info->Offset) + info->Offset; 
		}
		mrcPixelDataSet(dst, x, y, 0.0, data, mrcPixelMag);
	}
	}
}


void 
__lmrcImageWindowingDolphChebyshevWindow(mrcImage* dst, mrcImage* src, lmrcImageWindowingInfo* info, long mode)
{
	mrcImageParaTypeReal x, y, z;
	mrcImageParaTypeReal rx, ry, rz;
	double data;
	double weightx, weighty;
	double WxMin, WxMax, Wx;
	double WyMin, WyMax, Wy;

	fprintf(stderr, "Not supported yet\n");
	exit(EXIT_FAILURE);

	if(src->HeaderN.z!=1) {
		fprintf(stderr, "Not supported N.z : %d\n", src->HeaderN.z);
		return;
	}

	Wx    = 1.0 - 2*info->Wx;
	WxMin = src->HeaderN.x*info->Wx;
	WxMax = src->HeaderN.x*(1-info->Wx);

	Wy    = 1.0 - 2*info->Wy;
	WyMin = src->HeaderN.y*info->Wy;
	WyMax = src->HeaderN.y*(1-info->Wy);
	
	for(x=0; x<src->HeaderN.x; x++) {
		rx = (x-(src->HeaderN.x-1)/2)/(src->HeaderN.x*Wx);
	for(y=0; y<src->HeaderN.y; y++) {
		ry = (y-(src->HeaderN.y-1)/2)/(src->HeaderN.y*Wy);

		if(x<WxMin || WxMax <x
		 ||y<WyMin || WyMax <y) {
		 	data = info->Offset;
		} else {	
			weightx = 1;
			weighty = 1;
			mrcPixelDataGet(src, x, y, 0.0, &data, mrcPixelMag, mrcPixelHowNearest);
			data = weightx*weighty*(data - info->Offset) + info->Offset; 
		}
		mrcPixelDataSet(dst, x, y, 0.0, data, mrcPixelMag);
	}
	}
}


void 
__lmrcImageWindowingKaiserWindow(mrcImage* dst, mrcImage* src, lmrcImageWindowingInfo* info, long mode)
{
	mrcImageParaTypeReal x, y, z;
	mrcImageParaTypeReal rx, ry, rz;
	double data;
	double weightx, weighty;
	double WxMin, WxMax, Wx;
	double WyMin, WyMax, Wy;


	//fprintf(stderr, "Not supported yet\n");
	//exit(EXIT_FAILURE);

	if(src->HeaderN.z!=1) {
		fprintf(stderr, "Not supported N.z : %d\n", src->HeaderN.z);
		return;
	}

	for(y=0; y<src->HeaderN.y; y++) {
		Wy = j0(M_PI*info->Wy*sqrt(1 - SQR(2*y/(src->HeaderN.y-1) - 1)))/j0(M_PI*info->Wy);
	for(x=0; x<src->HeaderN.x; x++) {
		Wx = j0(M_PI*info->Wx*sqrt(1 - SQR(2*x/(src->HeaderN.x-1) - 1)))/j0(M_PI*info->Wx);
		
		mrcPixelDataGet(src, x, y, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);

		mrcPixelDataSet(dst, x, y, 0.0, data*Wx*Wy, mrcPixelRePart);
	}
	}
}

void 
__lmrcImageWindowingGaussWindow(mrcImage* dst, mrcImage* src, lmrcImageWindowingInfo* info, long mode)
{
	mrcImageParaTypeReal x, y, z;
	mrcImageParaTypeReal rx, ry, rz;
	double data;
	double weightx, weighty;
	double Wx, Cx;
	double Wy, Cy;

	if(src->HeaderN.z!=1) {
		fprintf(stderr, "Not supported N.z : %d\n", src->HeaderN.z);
		return;
	}

	Wx    = (0.5 - info->Wx)*src->HeaderN.x;
	Wy    = (0.5 - info->Wy)*src->HeaderN.y;
   	Cx    = (src->HeaderN.x-1)/2.0;  
   	Cy    = (src->HeaderN.y-1)/2.0;  

	for(x=0; x<src->HeaderN.x; x++) {
		rx = (x-Cx)/Wx;
		weightx = exp(-SQR(rx)/2.0);	
	for(y=0; y<src->HeaderN.y; y++) {
		ry = (y-Cy)/Wy;
		weighty = exp(-SQR(ry)/2.0);	

		mrcPixelDataGet(src, x, y, 0.0, &data, mrcPixelMag, mrcPixelHowNearest);
		data = weightx*weighty*(data - info->Offset) + info->Offset; 
		mrcPixelDataSet(dst, x, y, 0.0, data, mrcPixelMag);
	}
	}
}

void
__lmrcImageWindowingExponentialWindow(mrcImage* dst, mrcImage* src, lmrcImageWindowingInfo* info, long mode)
{
	mrcImageParaTypeReal x, y, z;
	mrcImageParaTypeReal rx, ry, rz;
	double data;
	double weightx, weighty;
	double Wx, Cx;
	double Wy, Cy;

	if(src->HeaderN.z!=1) {
		fprintf(stderr, "Not supported N.z : %d\n", src->HeaderN.z);
		return;
	}

	Wx    = (0.5 - info->Wx)*src->HeaderN.x;
	Wy    = (0.5 - info->Wy)*src->HeaderN.y;
   	Cx    = (src->HeaderN.x-1)/2.0;  
   	Cy    = (src->HeaderN.y-1)/2.0;  

	for(x=0; x<src->HeaderN.x; x++) {
		rx = (x-Cx)/Wx;
		weightx = exp(-fabs(rx));	
	for(y=0; y<src->HeaderN.y; y++) {
		ry = (y-Cy)/Wy;
		weighty = exp(-fabs(ry));	

		mrcPixelDataGet(src, x, y, 0.0, &data, mrcPixelMag, mrcPixelHowNearest);
		data = weightx*weighty*(data - info->Offset) + info->Offset; 
		mrcPixelDataSet(dst, x, y, 0.0, data, mrcPixelMag);
	}
	}
}


