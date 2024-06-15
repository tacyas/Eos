/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageSpatialFrequencyFilter ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageSpatialFrequencyFilter 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageSpatialFrequencyFilter ver%I%; Date:%D% %Z%";
#undef DEBUG

#include "genUtil.h"
#include "./lmrcImageSpatialFrequencyFilter.h"

void
lmrcImageSpatialFrequencyFilter(mrcImage* out, mrcImage* in, lmrcImageSpatialFrequencyFilterInfo linfo, int mode)
{
	mrcImage fft;
	float X, Y, Z;
	float delX, delY, delZ;
	float XX, YY, ZZ, RR;
	double W, WL, WH;
	int R, RL, RH;
	double DR;
	double rdata;
	double idata;
	int flag;

	DEBUGPRINT("Start lmrcImageSpatialFrequencyFilter\n");
	if(IsImage(in, "in lmrcImageSpatialFrequencyFilter", 0)) {	
		lmrcImageFFT(&fft, in, 0);
	} else {
		fft = *in;
		mrcInit(&fft, NULL);
	}

	R = 0;
	delX = 1.0/(fft.HeaderN.x*fft.HeaderLength.x);
	delY = 1.0/(fft.HeaderN.y*fft.HeaderLength.y);
	delZ = 1.0/(fft.HeaderN.z*fft.HeaderLength.z);
	DEBUGPRINT3("delta: %f %f %f\n", delX, delY, delZ);

	for(Z=-fft.HeaderN.z/2; Z< fft.HeaderN.z/2; Z++) {
		ZZ = Z*delZ;
	for(Y=-fft.HeaderN.y/2; Y< fft.HeaderN.y/2; Y++) {
		YY = Y*delY;
	for(X=0.0;              X<=fft.HeaderN.x/2; X++) {
		XX = X*delX;	
	
		RR = sqrt(SQR(XX) + SQR(YY) + SQR(ZZ));

		W = 0.0;
		flag = 1;
		if(flag && linfo.flagH && linfo.H < RR) {
			W = 0.0;
			DEBUGPRINT2("R: %f  W: %f\n", RR, W);	
			flag = 0;
		} 
		if(flag && linfo.flagL && RR < linfo.L) {
			W = 0.0;
			DEBUGPRINT2("R: %f  W: %f\n", RR, W);	
			flag = 0;
		} 
		while(flag) {
			RL = MAX(R-1,0);
			RH = MIN(R+1,linfo.nR-1);
			if(linfo.R[R] <= RR) {
				if(RR<linfo.R[RH]) {
					DR = (RR - linfo.R[R])/(linfo.R[RH] - linfo.R[R]);    
					W = DR*linfo.W[RH] + (1.0-DR)*linfo.W[R]; 
					DEBUGPRINT5("R: %f  W: %f DR: %f %f %f\n", RR, W, DR, linfo.W[R], linfo.W[RH]);	
					flag = 0;
				} else {
					if(R==RH) {
						W = 0.0;
						flag=0;
					} else {
						R++;
					}
				}
			} else {
				if(R==RL) {
					W = 0.0;
					flag=0;
				} else {
					R--;
				}
			}
		}
		mrcPixelDataGet(&fft, X, Y, Z, &rdata, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(&fft, X, Y, Z, &idata, mrcPixelImPart, mrcPixelHowNearest);
		rdata *= W;
		idata *= W;
		mrcPixelDataSet(&fft, X, Y, Z, rdata, mrcPixelRePart);
		mrcPixelDataSet(&fft, X, Y, Z, idata, mrcPixelImPart);
	}
	}
	}

	if(IsImage(in, "in lmrcImageSpatialFrequencyFilter", 0)) {	
		lmrcImageFFT(out, &fft, 0);
		mrcImageFree(&fft, "in lmrcImageSpatialFrequencyFilter");
	} else {
		*out = fft;	
	}
}

