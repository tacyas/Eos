/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageSobel ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageSobel 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageSobel ver%I%; Date:%D% %Z%";


#include <stdlib.h>
#include "./lmrcImageEdgeEnhancement.h"

void
lmrcImageEdgeEnhancementSobelOperatorSQRT(mrcImage* out, mrcImage* in, lmrcImageEdgeEnhancementInfo* linfo, int mode)
{
	mrcImageParaTypeReal x, y, z;
	double src00, src01, src02;
	double src10, src11, src12;
	double src20, src21, src22;
	double src000, src001, src002, src010, src011, src012, src020, src021, src022;
	double src100, src101, src102, src110, src111, src112, src120, src121, src122;
	double src200, src201, src202, src210, src211, src212, src220, src221, src222;
	double dst, Gx, Gy, Gz;


	lmrcImageEdgeEnhancementPrepare(out, in, linfo, mode);

	if(1<in->HeaderN.z) { // 3D
		for(z=0; z<in->HeaderN.z; z++) {
		for(y=0; y<in->HeaderN.y; y++) {
		for(x=0; x<in->HeaderN.x; x++) {
			mrcPixelDataGet(in, x,   y,   z  , &src000, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x,   y,   z+1, &src001, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x,   y+1, z  , &src010, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x,   y+1, z+1, &src011, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x,   y,   z  , &src100, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x,   y,   z+1, &src101, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x,   y+1, z  , &src010, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x,   y+1, z+1, &src011, mrcPixelRePart, mrcPixelHowNearest);
			switch(linfo->mode) { 
				case 0: { /* 3x3x1 */
					Gx = (src200 - src000 + 2.0*(src210 - src010) + src220 - src020
					     +src200 - src000 + 2.0*(src201 - src001) + src202 - src002)/8.0;
					Gy = (src020 - src000 + 2.0*(src021 - src001) + src022 - src002
					     +src020 - src000 + 2.0*(src120 - src100) + src220 - src200)/8.0;
					Gz = (src002 - src000 + 2.0*(src102 - src100) + src202 - src200
					     +src002 - src000 + 2.0*(src012 - src010) + src022 - src020)/8.0;
					break;
				}
				case 1: { /* 3x3x1 */
					Gx = (src200 - src000 + 2.0*(src210 - src010) + src220 - src020
					     +src200 - src000 + 2.0*(src201 - src001) + src202 - src002)/8.0;
					Gy = (src020 - src000 + 2.0*(src021 - src001) + src022 - src002
					     +src020 - src000 + 2.0*(src120 - src100) + src220 - src200)/8.0;
					Gz = (src002 - src000 + 2.0*(src102 - src100) + src202 - src200
					     +src002 - src000 + 2.0*(src012 - src010) + src022 - src020)/8.0;
					break;
				}
				default: {
					fprintf(stderr, "Not supported mode: %d in lmrcImageEdgeEnhancementRobertsCrossOperatorSQRT\n", linfo->mode);
					exit(EXIT_FAILURE);
					break;
				}
			}
			dst = SQR(Gx) + SQR(Gy) + SQR(Gz);
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
		for(y=1; y<in->HeaderN.y-1; y++) {
		for(x=1; x<in->HeaderN.x-1; x++) {
			mrcPixelDataGet(in, x-1, y-1, 0, &src00, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x-1, y,   0, &src01, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x-1, y+1, 0, &src02, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x,   y-1, 0, &src10, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x,   y+1, 0, &src12, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x+1, y-1, 0, &src20, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x+1, y,   0, &src21, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x+1, y+1, 0, &src22, mrcPixelRePart, mrcPixelHowNearest);
		
			Gx = (src20 - src00 + 2.0*(src21 - src01) + src22 - src02)/4.0;
			Gy = (src02 - src00 + 2.0*(src12 - src10) + src22 - src20)/4.0;
			
			dst = SQR(Gx) + SQR(Gy);
			if(0<dst) {
				dst = sqrt(dst);
			} else {
				dst = 0;
			}
			mrcPixelDataSet(out, x, y, 0, dst, mrcPixelRePart);

			if(linfo->flagDirection) {
				dst = atan2(Gy, Gx)*180.0/M_PI;
				mrcPixelDataSet(&(linfo->direction[0]), x, y, 0, dst, mrcPixelRePart);
			}
		}
		}
	}
}

void
lmrcImageEdgeEnhancementSobelOperatorABS(mrcImage* out, mrcImage* in, lmrcImageEdgeEnhancementInfo* linfo, int mode)
{
	mrcImageParaTypeReal x, y, z;
	double src00, src01, src02;
	double src10, src11, src12;
	double src20, src21, src22;
	double src000, src001, src002, src010, src011, src012, src020, src021, src022;
	double src100, src101, src102, src110, src111, src112, src120, src121, src122;
	double src200, src201, src202, src210, src211, src212, src220, src221, src222;
	double dst, Gx, Gy, Gz;


	lmrcImageEdgeEnhancementPrepare(out, in, linfo, mode);

	if(1<in->HeaderN.z) { // 3D
		for(z=0; z<in->HeaderN.z; z++) {
		for(y=0; y<in->HeaderN.y; y++) {
		for(x=0; x<in->HeaderN.x; x++) {
			mrcPixelDataGet(in, x,   y,   z  , &src000, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x,   y,   z+1, &src001, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x,   y+1, z  , &src010, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x,   y+1, z+1, &src011, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x,   y,   z  , &src100, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x,   y,   z+1, &src101, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x,   y+1, z  , &src010, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x,   y+1, z+1, &src011, mrcPixelRePart, mrcPixelHowNearest);
			switch(linfo->mode) { 
				case 0: { /* 2x2x1 */
					Gx = (src200 - src000 + 2.0*(src210 - src010) + src220 - src020
					     +src200 - src000 + 2.0*(src201 - src001) + src202 - src002)/8.0;
					Gy = (src020 - src000 + 2.0*(src021 - src001) + src022 - src002
					     +src020 - src000 + 2.0*(src120 - src100) + src220 - src200)/8.0;
					Gz = (src002 - src000 + 2.0*(src102 - src100) + src202 - src200
					     +src002 - src000 + 2.0*(src012 - src010) + src022 - src020)/8.0;
					break;
				}
				default: {
					fprintf(stderr, "Not supported mode: %d in lmrcImageEdgeEnhancementRobertsCrossOperatorSQRT\n", linfo->mode);
					exit(EXIT_FAILURE);
					break;
				}
			}
			dst = fabs(Gx) + fabs(Gy) + fabs(Gz);
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
		for(y=1; y<in->HeaderN.y-1; y++) {
		for(x=1; x<in->HeaderN.x-1; x++) {
			mrcPixelDataGet(in, x-1, y-1, 0, &src00, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x-1, y,   0, &src01, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x-1, y+1, 0, &src02, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x,   y-1, 0, &src10, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x,   y+1, 0, &src12, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x+1, y-1, 0, &src20, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x+1, y,   0, &src21, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x+1, y+1, 0, &src22, mrcPixelRePart, mrcPixelHowNearest);
		
			Gx = (src20 - src00 + 2.0*(src21 - src01) + src22 - src02)/4.0;
			Gy = (src02 - src00 + 2.0*(src12 - src10) + src22 - src20)/4.0;
			
			dst = fabs(Gx) + fabs(Gy);
			mrcPixelDataSet(out, x, y, 0, dst, mrcPixelRePart);

			if(linfo->flagDirection) {
				dst = atan2(Gy, Gx)*180.0/M_PI;
				mrcPixelDataSet(&(linfo->direction[0]), x, y, 0, dst, mrcPixelRePart);
			}
		}
		}
	}
}

