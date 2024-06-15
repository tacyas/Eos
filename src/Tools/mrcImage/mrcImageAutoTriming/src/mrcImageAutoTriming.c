/*
# mrcImageAutoTriming : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageAutoTriming
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
#include "Matrix3D.h"
#include "mrcImage.h"

typedef struct lmrcImageAutoTrimingInfo {
	// Control
	EulerAngleInfo min; 
	EulerAngleInfo max; 
	EulerAngleInfo delta; 
	int InterpolationMode;

	// Temp
	EulerAngleInfo cur; 

	// Final
	EulerAngleInfo best; 
	mrcImageParaTypeReal bestThickness;
	mrcImageParaTypeReal bestThicknessBottom;
	mrcImageParaTypeReal bestThicknessTop;

} lmrcImageAutoTrimingInfo;

typedef enum lmrcImageAutoTrimingMode {
	lmrcImageAutoTrimingModeZLayerMinCut=0,
	lmrcImageAutoTrimingModeZLayerSDCut=1
} lmrcImageAutoTrimingMode;

extern char* stpncpy(char *restrict dst, const char *restrict src, size_t n);
extern void lmrcImageAutoTriming(mrcImage* out, mrcImage* in, lmrcImageAutoTrimingInfo* linfo, int mode);
extern void lmrcImageAutoTrimingOutput(FILE* fpt, lmrcImageAutoTrimingInfo* linfo, int mode);
extern void lmrcImageAutoTrimingUsage(FILE* fpt);

int
main(int argc, char* argv[]) 
{
	mrcImageAutoTrimingInfo info;
	lmrcImageAutoTrimingInfo linfo;
	mrcImage in;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	strncpy(linfo.cur.EAMode, info.EAMode, 4);
	strncpy(linfo.min.EAMode, info.EAMode, 4);
	strncpy(linfo.max.EAMode, info.EAMode, 4);
	strncpy(linfo.delta.EAMode, info.EAMode, 4);
	linfo.min.Rot1 = info.Rot1Min*RADIAN;
	linfo.min.Rot2 = info.Rot2Min*RADIAN;
	linfo.min.Rot3 = info.Rot3Min*RADIAN;
	linfo.max.Rot1 = info.Rot1Max*RADIAN;
	linfo.max.Rot2 = info.Rot2Max*RADIAN;
	linfo.max.Rot3 = info.Rot3Max*RADIAN;
	linfo.delta.Rot1 = info.Rot1Delta*RADIAN;
	linfo.delta.Rot2 = info.Rot2Delta*RADIAN;
	linfo.delta.Rot3 = info.Rot3Delta*RADIAN;
	linfo.InterpolationMode = info.InterpolationMode;

	mrcFileRead(&in, info.In, "in main", 0);

	lmrcImageAutoTriming(&out, &in, &linfo, info.mode);

	lmrcImageAutoTrimingOutput(info.fptOutParam, &linfo, info.mode);

	mrcFileWrite(&out, info.Out, "in main", 0);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	lmrcImageAutoTrimingUsage(stderr);
}

void 
lmrcImageAutoTriming(mrcImage* out, mrcImage* in, lmrcImageAutoTrimingInfo* linfo, int mode)
{
	Matrix3D mat;
	mrcImage tmp;
	mrcImageParaTypeInteger ix, iy, iz, k, kz, ky, kx0;
	double data;

	int flagBottom, izBottom;
	int flagTop, izTop;
	int thickness;
	double minSD;
	mrcImageParaTypeRealCoord to;

	linfo->bestThickness = in->HeaderN.z;  
	for(linfo->cur.Rot1=linfo->min.Rot1; linfo->cur.Rot1<=linfo->max.Rot1; linfo->cur.Rot1+=linfo->delta.Rot1) {
	for(linfo->cur.Rot2=linfo->min.Rot2; linfo->cur.Rot2<=linfo->max.Rot2; linfo->cur.Rot2+=linfo->delta.Rot2) {
	for(linfo->cur.Rot3=linfo->min.Rot3; linfo->cur.Rot3<=linfo->max.Rot3; linfo->cur.Rot3+=linfo->delta.Rot3) {
		lmrcImageRotation3DFollowingEulerAngle(&tmp, in, linfo->cur.EAMode, linfo->cur.Rot1, linfo->cur.Rot2, linfo->cur.Rot3, linfo->InterpolationMode, 0); 

		switch(mode) {
			case lmrcImageAutoTrimingModeZLayerMinCut: {
				flagBottom = 0;
				flagTop = 0;
				izBottom = 0;
				izTop = in->HeaderN.z - 1;
				for(iz=0; iz<in->HeaderN.z; iz++) {
					kz = iz*in->HeaderN.x*in->HeaderN.y; 
					for(iy=0; iy<in->HeaderN.y; iy++) {
						ky  = iy*in->HeaderN.x; 
						kx0 = ky + kz;
					for(ix=0; ix<in->HeaderN.x; ix++) {
						k = ix + kx0;
						
						data = tmp.ImageFloatImage[k];
						if(0<data) {
							flagBottom = 1;	
							izBottom = iz;	
						}
						if(flagBottom) break;
					}
						if(flagBottom) break;
					}	
						if(flagBottom) break;
				}
	
				for(iz=in->HeaderN.z-1; 0<=iz; iz--) {
					kz = iz*in->HeaderN.x*in->HeaderN.y; 
					for(iy=0; iy<in->HeaderN.y; iy++) {
						ky  = iy*in->HeaderN.x; 
						kx0 = ky + kz;
					for(ix=0; ix<in->HeaderN.x; ix++) {
						k = ix + kx0;
						
						data = tmp.ImageFloatImage[k];
						if(0<data) {
							flagTop = 1;	
							izTop  = iz;	
						}
						if(flagTop) break;
					}
						if(flagTop) break;
					}	
						if(flagTop) break;
				}
				thickness = izTop - izBottom + 1;
				if(thickness < linfo->bestThickness) {
					linfo->bestThickness = thickness;
					linfo->bestThicknessTop    = izTop; 
					linfo->bestThicknessBottom = izBottom;
					strncpy(linfo->best.EAMode, linfo->cur.EAMode, 4);
					linfo->best.Rot1 = linfo->cur.Rot1;
					linfo->best.Rot2 = linfo->cur.Rot2;
					linfo->best.Rot3 = linfo->cur.Rot3;
				}
				break;
			}
			case lmrcImageAutoTrimingModeZLayerSDCut: {
				minSD = in->HeaderN.z;

				break;
			}
			default: {
				fprintf(stderr, "Not supported mode: %d\n", mode);
				break;
			}
		}
		mrcImageFree(&tmp, 0);
	}
	}
	}
	lmrcImageRotation3DFollowingEulerAngle(&tmp, in, linfo->best.EAMode, linfo->best.Rot1, linfo->best.Rot2, linfo->best.Rot3, linfo->InterpolationMode, 0); 
	out->Header = tmp.Header;
	out->HeaderN.z = linfo->bestThickness;
	out->HeaderStartN.z = -out->HeaderN.z/2;  
	mrcInit(out, NULL);
	to.x = to.y = 0;
	to.z = -linfo->bestThicknessBottom;
	DEBUGPRINT1("to.z: %f\n", to.z);
	lmrcImageCopy(out, &tmp, to);
}

void 
lmrcImageAutoTrimingOutput(FILE* fpt, lmrcImageAutoTrimingInfo* linfo, int mode)
{
	switch(mode) {
		case lmrcImageAutoTrimingModeZLayerMinCut: 
		case lmrcImageAutoTrimingModeZLayerSDCut: {
			fprintf(fpt, "BestRotation: %4s %15.6g %15.6g %15.6g\n", linfo->best.EAMode, linfo->best.Rot1*DEGREE, linfo->best.Rot2*DEGREE, linfo->best.Rot3*DEGREE);
			fprintf(fpt, "Z-Thickness: %15.6g %15.6g %15.6g\n", linfo->bestThickness, linfo->bestThicknessBottom, linfo->bestThicknessTop);
			break;			
		}
	}
}

void 
lmrcImageAutoTrimingUsage(FILE* fpt)
{
	fprintf(fpt, ">>> mode\n");
	fprintf(fpt, "%d: z-layer(minimum of z-axis by min)\n", lmrcImageAutoTrimingModeZLayerMinCut);
	fprintf(fpt, "%d: z-layer(minimum of z-axis by SD)\n", lmrcImageAutoTrimingModeZLayerSDCut);
}

