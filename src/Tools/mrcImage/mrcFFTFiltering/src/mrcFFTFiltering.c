#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define GLOBAL_DECLARATION       
#include "../inc/config.h"
#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "Vector.h"

typedef struct lmrcFFTFiteringInfo {
	float vx;
	float vy;
	float v1x;
	float v1y;
	float v2x;
	float v2y;
	int sx;
	int sy;
	int flagNegF00;	
	int flagIQ;
	mrcImage IQ;
} lmrcFFTFilteringInfo;

extern void lmrcFFTFiltering2DOrthogonalSymmetry(mrcImage* out, mrcImage* fft, lmrcFFTFilteringInfo info);
extern void lmrcFFTFiltering2DRhombicSymmetry(mrcImage* out, mrcImage* fft, lmrcFFTFilteringInfo info);

int
main(int argc, char* argv[])
{
    mrcImage fft;
    mrcImage out;
	mrcFFTFilteringInfo info;
	lmrcFFTFilteringInfo linfo;
	mrcImageParaTypeReal x, y;

    init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);
    mrcFileRead (&fft, info.In,  "from Main Routine", 0);

	linfo.flagIQ  = info.flagIQ;
	if(linfo.flagIQ) {
		linfo.IQ.Header.Cont = fft.Header.Cont;
		mrcInit(&(linfo.IQ), NULL);
		for(x=0; x<=linfo.IQ.HeaderN.x/2; x++) {
		for(y=0; y<linfo.IQ.HeaderN.y/2; y++) {
			mrcPixelDataSet(&(linfo.IQ), x, y, 0.0, 8, mrcPixelRePart);
			mrcPixelDataSet(&(linfo.IQ), x, y, 0.0, 0, mrcPixelImPart);
		}
		for(y=-linfo.IQ.HeaderN.y/2; y<0; y++) {
			mrcPixelDataSet(&(linfo.IQ), x, y, 0.0, 8, mrcPixelRePart);
			mrcPixelDataSet(&(linfo.IQ), x, y, 0.0, 0, mrcPixelImPart);
		}
		}
	}

	if(info.neglectF00) {
		for(x=-(info.sx-1)/2; x<=(info.sx-1)/2; x++) { 
		for(y=-(info.sy-1)/2; y<=(info.sy-1)/2; y++) { 
			mrcPixelDataSet(&fft, x, y, 0.0, 0.0, mrcPixelRePart);
			mrcPixelDataSet(&fft, x, y, 0.0, 0.0, mrcPixelImPart);
		}
		}
	}

	if(info.flagvx || info.flagvy) {
		/* For orthogonalSymmetry */
		DEBUGPRINT("OrthogonalSymmetry\n")
		if(info.flagvx) {
			linfo.vx = info.vx;
		} else {
			linfo.vx = fft.HeaderN.x;
		}
		if(info.flagvy) {
			linfo.vy = info.vy;
		} else {
			linfo.vy = fft.HeaderN.y;
		}
		linfo.sx = info.sx;
		linfo.sy = info.sy;
		lmrcFFTFiltering2DOrthogonalSymmetry(&out, &fft, linfo);
	} else if(info.flagv1x || info.flagv2x) {
		DEBUGPRINT("RhombicSymmetry\n")
		linfo.sx = info.sx;
		linfo.sy = info.sy;
		if(info.flagv1x) {
			linfo.v1x = info.v1x;
			linfo.v1y = info.v1y;
		} else {
			linfo.v1x = fft.HeaderN.x;
			linfo.v1y = fft.HeaderN.y;
		}
		if(info.flagv2x) {
			linfo.v2x = info.v2x;
			linfo.v2y = info.v2y;
		} else {
			linfo.v2x = fft.HeaderN.x;
			linfo.v2y = fft.HeaderN.y;
		}
		lmrcFFTFiltering2DRhombicSymmetry(&out, &fft, linfo);
	}
    mrcFileWrite(&out, info.Out,  "from Main Routine", 0);
	if(info.flagIQ) {
    	mrcFileWrite(&(linfo.IQ), info.IQ,  "from Main Routine", 0);
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
}

void
lmrcFFTFiltering2DOrthogonalSymmetry(mrcImage* out, mrcImage* fft, lmrcFFTFilteringInfo info)
{
	float cx, x;
	float cy, y;
	double re, re1;
	double im, im1;
	double mag, mag1;
	int    counter;
	out->Header = fft->Header;	
	mrcInit(out, NULL);

	for(cx=0; cx<=out->HeaderN.x/2.0; cx+=info.vx) {
		for(cy=0;   cy<out->HeaderN.y/2.0; cy+=info.vy) {
			counter = 0;
			for(x=cx-info.sx/2; x<=cx+info.sx/2; x++) {
				for(y=cy-info.sy/2; y<=cy+info.sy/2; y++) {
					if(x<0 || fft->HeaderN.x/2.0<x 
					|| y<0 || fft->HeaderN.y/2.0 - 1< y) {
					} else {
						mrcPixelDataGet(fft, x, y, 0.0, &re, mrcPixelRePart, mrcPixelHowNearest);
						mrcPixelDataGet(fft, x, y, 0.0, &im, mrcPixelImPart, mrcPixelHowNearest);
						mrcPixelDataSet(out, x, y, 0.0, re, mrcPixelRePart);
						mrcPixelDataSet(out, x, y, 0.0, im, mrcPixelImPart);

						if(info.flagIQ) {
							if(1<=SQR((x-cx)/info.sx*2)+SQR((y-cy)/info.sy*2)) {
								mrcPixelDataGet(&(info.IQ), cx, cy, 0.0, &mag, mrcPixelMag, mrcPixelHowNearest);
								mrcPixelDataGet(fft,         x,  y, 0.0, &mag1, mrcPixelMag, mrcPixelHowNearest);
								mrcPixelDataSet(&(info.IQ), cx, cy, 0.0, mag+mag1, mrcPixelMag);
								counter++;
							}
						}
					}
				}
			}
			if(1<=counter) {
				mrcPixelDataGet(&(info.IQ), cx, cy, 0.0, &mag, mrcPixelMag, mrcPixelHowNearest);
				mrcPixelDataGet(fft,        cx, cy, 0.0, &mag1, mrcPixelMag, mrcPixelHowNearest);
				mrcPixelDataSet(&(info.IQ), cx, cy, 0.0, 7*mag/counter/(mag1-mag/counter), mrcPixelMag);
			}
		}
		for(cy=0; -out->HeaderN.y/2.0<=cy; cy-=info.vy) {
			counter = 0;
			for(x=cx-info.sx/2; x<=cx+info.sx/2; x++) {
				for(y=cy-info.sy/2; y<=cy+info.sy/2; y++) {
					if(x<0 ||  fft->HeaderN.x/2.0<x 
					|| y>0 || -fft->HeaderN.y/2.0>y) {
					} else {
						mrcPixelDataGet(fft, x, y, 0.0, &re, mrcPixelRePart, mrcPixelHowNearest);
						mrcPixelDataGet(fft, x, y, 0.0, &im, mrcPixelImPart, mrcPixelHowNearest);
						mrcPixelDataSet(out, x, y, 0.0, re, mrcPixelRePart);
						mrcPixelDataSet(out, x, y, 0.0, im, mrcPixelImPart);

						if(info.flagIQ) {
							if(1<=SQR((x-cx)/info.sx*2)+SQR((y-cy)/info.sy*2)) {
								mrcPixelDataGet(&(info.IQ), cx, cy, 0.0, &mag, mrcPixelMag, mrcPixelHowNearest);
								mrcPixelDataGet(fft,         x,  y, 0.0, &mag1, mrcPixelMag, mrcPixelHowNearest);
								mrcPixelDataSet(&(info.IQ), cx, cy, 0.0, mag+mag1, mrcPixelMag);
								counter++;
							}
						}
					}
				}
			}
			if(1<=counter) {
				mrcPixelDataGet(&(info.IQ), cx, cy, 0.0, &mag,  mrcPixelMag, mrcPixelHowNearest);
				mrcPixelDataGet(fft,       cx, cy, 0.0, &mag1, mrcPixelMag, mrcPixelHowNearest);
				mrcPixelDataSet(&(info.IQ), cx, cy, 0.0, 7*mag/counter/(mag1-mag/counter), mrcPixelMag);
			}
		}
	}
}

void
lmrcFFTFiltering2DRhombicSymmetry(mrcImage* out, mrcImage* fft, lmrcFFTFilteringInfo info)
{
	int iv1, iv2;
	double v1, v2;
	double re;
	double im;
	double mag, mag1;
	double IQ;
	double det, lengthV1, lengthV2;
	double cx, cy;
	mrcImageParaTypeReal X, Y;
	mrcImageParaTypeReal x, y;
	int counter;
	out->Header = fft->Header;	
	mrcInit(out, NULL);

	det = (info.v1x*info.v2y - info.v2x*info.v1y);
	if(det==0.0) {
		fprintf(stderr, "two vectors are parallel in lmrcFFTFiltering2DRhombicSymmetry\n");
		exit(EXIT_FAILURE);
	}
	lengthV1 = sqrt(SQR(info.v1x)+SQR(info.v1y));
	lengthV2 = sqrt(SQR(info.v2x)+SQR(info.v2y));
	DEBUGPRINT4("v1 %lf %lf v2 %lf %lf\n", info.v1x, info.v1y, info.v2x, info.v2y);
	DEBUGPRINT2("s %d %d \n", info.sx, info.sy);
	for(X=0; X<=fft->HeaderN.x/2; X++) {
		for(Y=-fft->HeaderN.y/2; Y<fft->HeaderN.y/2; Y++) {
			/*
				X = v1*info.v1 + v2*info.v2 

				/X\   / info.v1x info.v2x \ /v1\
				| |  =|                   | |  |
				\Y/   \ info.v1y info.v2y / \v2/


				/v1\         / info.v2y -info.v2x \ /X\
				|  |  =1/det*|                    | | |
				\v2/         \ -info.v1y info.v1x / \Y/


			*/

			v1 = ( info.v2y*X - info.v2x*Y)/det;
			v2 = (-info.v1y*X + info.v1x*Y)/det; 
			iv1 = floor(v1+0.5);
			iv2 = floor(v2+0.5);
			cx = floor(iv1*info.v1x + iv2*info.v2x + 0.5);
			cy = floor(iv1*info.v1y + iv2*info.v2y + 0.5);
			if(fabs(cx-X)<1e-2 && fabs(cy-Y)<1e-2) { /* If Nearest Point */
				DEBUGPRINT4("vector (%5d %5d) : centre(%15.6g %15.6g)\n", iv1, iv2, cx, cy);				
				counter = 0;
				if(info.flagIQ) {
					 mrcPixelDataSet(&(info.IQ), cx, cy, 0.0, 0, mrcPixelRePart);
					 mrcPixelDataSet(&(info.IQ), cx, cy, 0.0, 0, mrcPixelImPart);
				}
				for(x=cx-info.sx/2; x<=cx+info.sx/2; x++) {
					for(y=cy-info.sy/2; y<=cy+info.sy/2; y++) {
						if(x < -fft->HeaderN.x/2.0  
						||      fft->HeaderN.x/2.0 < x 
						|| y < -fft->HeaderN.y/2.0
						||      fft->HeaderN.y/2.0 - 1 < y) {
						} else {
							DEBUGPRINT2("%15.6g %15.6g\n", x, y);
							mrcPixelDataGet(fft, x, y, 0.0, &re, mrcPixelRePart, mrcPixelHowNearest);
							mrcPixelDataGet(fft, x, y, 0.0, &im, mrcPixelImPart, mrcPixelHowNearest);
							mrcPixelDataSet(out, x, y, 0.0, re, mrcPixelRePart);
							mrcPixelDataSet(out, x, y, 0.0, im, mrcPixelImPart);
							if(info.flagIQ) {
								if(1<=SQR((x-cx)/(info.sx/2))+SQR((y-cy)/(info.sy*2))) {
									mrcPixelDataGet(&(info.IQ), cx, cy, 0.0, &re, mrcPixelRePart, mrcPixelHowNearest);
									mrcPixelDataGet(fft,         x,  y, 0.0, &mag1, mrcPixelMag, mrcPixelHowNearest);
									mrcPixelDataSet(&(info.IQ), cx, cy, 0.0, re+mag1, mrcPixelRePart);
									mrcPixelDataSet(&(info.IQ), cx, cy, 0.0, 0, mrcPixelImPart);
									DEBUGPRINT3("(%f,%f): %f\n",cx,cy,re+mag1);
									counter++;
								}
								DEBUGPRINT3("(%f,%f): %f\n",cx,cy,SQR((x-cx)/info.sx*2.0)+SQR((y-cy)/info.sy*2.0));
							}	
						}
					}
				}
				if(1<=counter) {
					mrcPixelDataGet(&(info.IQ), cx, cy, 0.0, &mag,  mrcPixelRePart, mrcPixelHowNearest);
					mrcPixelDataGet(fft,        cx, cy, 0.0, &mag1, mrcPixelMag, mrcPixelHowNearest);
					IQ = 7*(mag/counter)/(mag1-(mag/counter));
					if(IQ<=0 || 7<=IQ) {
						IQ = 7;	
					} 
					mrcPixelDataSet(&(info.IQ), cx, cy, 0.0, IQ, mrcPixelRePart);
					fprintf(stderr, "(%f,%f): %f\n",cx,cy,IQ);
				}
			}
		}
	}
}

