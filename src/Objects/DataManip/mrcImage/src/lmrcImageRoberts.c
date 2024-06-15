/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageRoberts ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageRoberts 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageRoberts ver%I%; Date:%D% %Z%";

#include "Memory.h"
#include "./lmrcImageEdgeEnhancement.h"

void
lmrcImageEdgeEnhancementRobertsCrossOperatorSQRT(mrcImage* out, mrcImage* in, lmrcImageEdgeEnhancementInfo* linfo, int mode)
{
	mrcImageParaTypeReal x, y, z;
	double src00, src01, src10, src11;
	double src000, src001, src010, src011;
	double src100, src101, src110, src111;
	double dst;
	double Gx, Gy, Gz;
	int max, i;

	lmrcImageEdgeEnhancementPrepare(out, in, linfo, mode);

	if(1<in->HeaderN.z) { // 3D
		for(z=0; z<in->HeaderN.z; z++) {
		for(y=0; y<in->HeaderN.y; y++) {
		for(x=0; x<in->HeaderN.x; x++) {
			mrcPixelDataGet(in, x,   y,   z  , &src000, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x,   y,   z+1, &src001, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x,   y+1, z  , &src010, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x,   y+1, z+1, &src011, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x+1, y,   z  , &src100, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x+1, y,   z+1, &src101, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x+1, y+1, z  , &src110, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x+1, y+1, z+1, &src111, mrcPixelRePart, mrcPixelHowNearest);
			switch(linfo->mode) { 
				case 0: { /* 2x2x1 */
			 		Gx = SQR(src000 - src011) + SQR(src010 - src001); /* yz-plane */
			 		Gy = SQR(src000 - src101) + SQR(src001 - src100); /* zx-plane */
					Gz = SQR(src000 - src110) + SQR(src100 - src010); /* xy-plane */
					dst = (Gx + Gy + Gz)/6.0;
					break;
				}
				case 1: { /* 2x2x2 */
					dst = SQR(src110-src000) + SQR(src100 - src010) /* xy-plane z=0 */
			 		 	 +SQR(src010-src000) + SQR(src000 - src010) /* yz-plane x=0 */
			 		 	 +SQR(src101-src000) + SQR(src001 - src100) /* zx-plane y=0 */
					     +SQR(src111-src001) + SQR(src101 - src011) /* xy-plane z=1 */
			 		 	 +SQR(src110-src100) + SQR(src100 - src110) /* yz-plane x=1 */
			 		 	 +SQR(src111-src010) + SQR(src011 - src110);/* zx-plane y=1 */
					dst /= 12.0;
					break;
				}
				default: {
					fprintf(stderr, "Not supported mode: %d in lmrcImageEdgeEnhancementRobertsCrossOperatorSQRT\n", linfo->mode);
					exit(EXIT_FAILURE);
					break;
				}
			}
			if(0<dst) {
				dst = sqrt(dst);
			} else {
				dst = 0;
			}
			mrcPixelDataSet(out, x, y, z, dst, mrcPixelRePart);
		}
		}
		}
	} else { // 2D
		for(y=0; y<in->HeaderN.y-1; y++) {
		for(x=0; x<in->HeaderN.x-1; x++) {
			mrcPixelDataGet(in, x,   y,   0, &src00, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x,   y+1, 0, &src01, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x+1, y,   0, &src10, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x+1, y+1, 0, &src11, mrcPixelRePart, mrcPixelHowNearest);

			Gx = src00 - src11;
			Gy = src10 - src01;

			dst = SQR(Gx) + SQR(Gy);
			if(0<dst) {
				dst = sqrt(dst/2.0);
			} else {
				dst = 0;
			}
			mrcPixelDataSet(out, x, y, 0, dst, mrcPixelRePart);

			dst = atan2(Gy, Gx)*180/M_PI;
		
			if(linfo->flagDirection) {
				mrcPixelDataSet(&(linfo->direction[0]), x, y, 0, dst, mrcPixelRePart);
			}
		}
		}
	}
}


void
lmrcImageEdgeEnhancementRobertsCrossOperatorABS(mrcImage* out, mrcImage* in, lmrcImageEdgeEnhancementInfo* linfo, int mode)
{
	mrcImageParaTypeReal x, y, z;
	double src00, src01, src10, src11;
	double src000, src001, src010, src011;
	double src100, src101, src110, src111;
	double dst;
	double Gx, Gy, Gz;
	int max, i;

	lmrcImageEdgeEnhancementPrepare(out, in, linfo, mode);

	if(1<in->HeaderN.z) { // 3D
		for(z=0; z<in->HeaderN.z; z++) {
		for(y=0; y<in->HeaderN.y; y++) {
		for(x=0; x<in->HeaderN.x; x++) {
			mrcPixelDataGet(in, x,   y,   z  , &src000, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x,   y,   z+1, &src001, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x,   y+1, z  , &src010, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x,   y+1, z+1, &src011, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x+1, y,   z  , &src100, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x+1, y,   z+1, &src101, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x+1, y+1, z  , &src110, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x+1, y+1, z+1, &src111, mrcPixelRePart, mrcPixelHowNearest);
			switch(linfo->mode) { 
				case 0: { /* 2x2x1 */
			 		Gx = fabs(src000 - src011) + fabs(src010 - src001); /* yz-plane */
			 		Gy = fabs(src000 - src101) + fabs(src001 - src100); /* zx-plane */
					Gz = fabs(src000 - src110) + fabs(src100 - src010); /* xy-plane */
					dst = (Gx + Gy + Gz)/6.0;
					break;
				}
				case 1: { /* 2x2x2 */
					dst = SQR(src110-src000) + SQR(src100 - src010) /* xy-plane z=0 */
			 		 	 +SQR(src010-src000) + SQR(src000 - src010) /* yz-plane x=0 */
			 		 	 +SQR(src101-src000) + SQR(src001 - src100) /* zx-plane y=0 */
					     +SQR(src111-src001) + SQR(src101 - src011) /* xy-plane z=1 */
			 		 	 +SQR(src110-src100) + SQR(src100 - src110) /* yz-plane x=1 */
			 		 	 +SQR(src111-src010) + SQR(src011 - src110); /* zx-plane y=1 */
					dst /= 12.0;
					break;
				}
				default: {
					fprintf(stderr, "Not supported mode: %d in lmrcImageEdgeEnhancementRobertsCrossOperatorSQRT\n", linfo->mode);
					exit(EXIT_FAILURE);
					break;
				}
			}
			if(0<dst) {
				dst = sqrt(dst);
			} else {
				dst = 0;
			}
			mrcPixelDataSet(out, x, y, z, dst, mrcPixelRePart);
		}
		}
		}
	} else { // 2D
		for(y=0; y<in->HeaderN.y-1; y++) {
		for(x=0; x<in->HeaderN.x-1; x++) {
			mrcPixelDataGet(in, x,   y,   0, &src00, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x,   y+1, 0, &src01, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x+1, y,   0, &src10, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x+1, y+1, 0, &src11, mrcPixelRePart, mrcPixelHowNearest);

			Gx = src00 - src11;
			Gy = src10 - src01;

			dst = (fabs(Gx) + fabs(Gy))/2.0;
			mrcPixelDataSet(out, x, y, 0, dst, mrcPixelRePart);

			if(linfo->flagDirection) {
				dst = atan2(Gy, Gx)*180/M_PI;
				mrcPixelDataSet(&(linfo->direction[0]), x, y, 0, dst, mrcPixelRePart);
			}
		}
		}
	}
}
