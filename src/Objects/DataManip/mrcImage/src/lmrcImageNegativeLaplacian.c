/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageNegativeLappacian ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageNegativeLappacian 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageNegativeLappacian ver%I%; Date:%D% %Z%";

#include <stdio.h>
#include <stdlib.h>
#include "./lmrcImageEdgeEnhancement.h"

void
lmrcImageEdgeEnhancementNegativeLaplacian(mrcImage* out, mrcImage* in, lmrcImageEdgeEnhancementInfo* linfo, int mode)
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
			mrcPixelDataGet(in, x-1, y-1, z-1, &src000, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x-1, y-1, z  , &src001, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x-1, y-1, z+1, &src002, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x-1, y  , z-1, &src010, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x-1, y  , z  , &src011, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x-1, y  , z+1, &src012, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x-1, y+1, z-1, &src020, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x-1, y+1, z  , &src021, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x-1, y+1, z+1, &src022, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x  , y-1, z-1, &src100, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x  , y-1, z  , &src101, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x  , y-1, z+1, &src102, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x  , y  , z-1, &src110, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x  , y  , z  , &src111, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x  , y  , z+1, &src112, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x  , y+1, z-1, &src120, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x  , y+1, z  , &src121, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x  , y+1, z+1, &src122, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x+1, y-1, z-1, &src200, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x+1, y-1, z  , &src201, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x+1, y-1, z+1, &src202, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x+1, y  , z-1, &src210, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x+1, y  , z  , &src211, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x+1, y  , z+1, &src212, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x+1, y+1, z-1, &src220, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x+1, y+1, z  , &src221, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x+1, y+1, z+1, &src222, mrcPixelRePart, mrcPixelHowNearest);
			switch(mode) { 
				case 0: { /* 6-neighbor */
					dst = -1*src011 -1*src211 
					      -1*src101 -1*src121
					      -1*src110 -1*src112
					  	  +6*src111;

					break;
				}
				case 1: { /* 18-neighbor */
				    /*
						    122  
						012 112 212
						    102  

						021 121 221
						011 111 211
						001 101 201

						    120  
						010 110 210
						    100 
					*/
					dst =           -1*src122 
					      -1*src012 -1*src112 -1*src212 
						            -1*src102
					      -1*src021 -1*src121 -1*src221 
						  -1*src011           -1*src211
						  -1*src001 -1*src101 -1*src201
					                -1*src120 
						  -1*src010 -1*src110 -1*src210 
						            -1*src100
						  +18*src111 ;
					break;
				}
				case 2: { /* 26-neighbor */
				    /*
						022 122 222
						012 112 212
						002 102 202

						021 121 221
						011 111 211
						001 101 201

						020 120 220
						010 110 210
						000 100 200

					*/
					dst = +1*src022 -1*src122 +1*src222
					      -1*src012 -1*src112 -1*src212 
						  +1*src002 -1*src102 +1*src202
					      -1*src021 -1*src121 -1*src211
						  -1*src011           -1*src211 
						  -1*src001 -1*src101 -1*src201
						  +1*src020 -1*src120 +1*src220
						  -1*src010 -1*src110 -1*src210 
						  +1*src000 -1*src100 +1*src200
						  +10*src111 ;
					break;
				}
				default: {
					fprintf(stderr, "Not supported mode: %d in lmrcImageEdgeEnhancementRobertsCrossOperatorSQRT\n", mode);
					exit(EXIT_FAILURE);
					break;
				}
			}

			mrcPixelDataSet(out, x, y, z, dst, mrcPixelRePart);
		}
		}
		}
	} else { // 2D
		for(y=0; y<in->HeaderN.y-1; y++) {
		for(x=0; x<in->HeaderN.x-1; x++) {
			mrcPixelDataGet(in, x-1,   y-1 , 0, &src00, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x-1,   y   , 0, &src01, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x-1,   y+1 , 0, &src02, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x  ,   y-1 , 0, &src10, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x  ,   y   , 0, &src11, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x  ,   y+1 , 0, &src12, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x+1,   y-1 , 0, &src20, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x+1,   y   , 0, &src21, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, x+1,   y+1 , 0, &src22, mrcPixelRePart, mrcPixelHowNearest);
	
			switch(linfo->mode) {
				case 0: {
					dst =          -1*src12
					      -1*src01 +4*src11 -1*src21
						           -1*src10;
					break;
				}
				case 1: {
					dst = -1*src02 -1*src12 -1*src22
					      -1*src01 +8*src11 -1*src21
						  -1*src00 -1*src10 -1*src20;
					break;
				}
				case 2: {
					dst = +1*src02 -2*src12 +1*src22
					      -2*src01 +4*src11 -2*src21
						  +1*src00 -2*src10 +1*src20;
					break;
				}
				default: {
					fprintf(stderr, "Not supproted mode: %d", linfo->mode);
					break;
				}
			}	
			mrcPixelDataSet(out, x, y, 0, dst, mrcPixelRePart);
		}
		}
	}
}

