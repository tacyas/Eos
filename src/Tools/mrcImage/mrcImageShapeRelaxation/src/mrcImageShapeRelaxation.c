/*
# mrcImageShapeRelaxation : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageShapeRelaxation
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
#include "mrcImageShape.h"

typedef struct lmrcImageShapeRelaxationInfo {
	float a;
	int   maxIter;
} lmrcImageShapeRelaxationInfo;

typedef enum lmrcImageShapeRelaxationMode {
	a=0,
	b=1
} lmrcImageShapeRelaxationMode;

extern void lmrcImageShapeRelaxation(mrcImage* out, mrcImage* shape, mrcImage* shapeVec, lmrcImageShapeRelaxationInfo* linfo, int mode); 

int
main(int argc, char* argv[]) 
{
	mrcImageShapeRelaxationInfo info;
	lmrcImageShapeRelaxationInfo linfo;
	mrcImage shape;
	mrcImage shapeVec[3];
	mrcImage out;
	int i;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&shape, info.In, "in main", 0);
	mrcFileRead(&shapeVec[0], info.InVec0, "in main", 0);
	mrcFileRead(&shapeVec[1], info.InVec1, "in main", 0);
	mrcFileRead(&shapeVec[2], info.InVec2, "in main", 0);

	lmrcImageShapeRelaxation(&out, &shape, shapeVec, &linfo, info.mode);

	mrcFileWrite(&out, info.Out, "in main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}


void 
lmrcImageShapeRelaxation(mrcImage* out, mrcImage* shape, mrcImage* shapeVec, lmrcImageShapeRelaxationInfo* linfo, int mode)
{
	mrcImageParaTypeInteger x, y, z;
	int k000, k100, k_00, k010, k0_0, k001, k00_; 
	int s000, s100, s_00, s010, s0_0, s001, s00_; 
	char s[7];
	float v000[3], v100[3], v_00[3], v010[3], v0_0[3], v001[3], v00_[3]; 
	float v[7][3]
	int iter, i;
	int shapeCount[lmrcImageShapeModeMax+1];

	out->Header = shape->Header;
	mrcInit(out, NULL);

	for(iter=0; iter<linfo->maxIter; iter++) { 
		for(z=0; z<out->HeaderN.z; z++) {
		for(y=0; y<out->HeaderN.y; y++) {
		for(x=0; x<out->HeaderN.x; x++) {
			k000 = x   + y*out->HeaderN.x + z*out->HeaderN.x*out->HeaderN.y;
			s[0]=s000 = shape->ImageFloatImage[k000];

			// 6-Neighbor
			s[1]=k100 = (x+1) + y*out->HeaderN.x + z*out->HeaderN.x*out->HeaderN.y;
			s[2]=k_00 = (x-1) + y*out->HeaderN.x + z*out->HeaderN.x*out->HeaderN.y;
			s[3]=k010 = x + (y+1)*out->HeaderN.x + z*out->HeaderN.x*out->HeaderN.y;
			s[4]=k0_0 = x + (y-1)*out->HeaderN.x + z*out->HeaderN.x*out->HeaderN.y;
			s[5]=k001 = x + y*out->HeaderN.x + (z+1)*out->HeaderN.x*out->HeaderN.y;
			s[6]=k00_ = x + y*out->HeaderN.x + (z-1)*out->HeaderN.x*out->HeaderN.y;
				
			s[1]=s100 = shape->ImageFloatImage[k100];
			s[2]=s_00 = shape->ImageFloatImage[k_00];
			s[3]=s010 = shape->ImageFloatImage[k010];
			s[4]=s0_0 = shape->ImageFloatImage[k0_0];
			s[5]=s001 = shape->ImageFloatImage[k001];
			s[6]=s00_ = shape->ImageFloatImage[k00_];

			for(i=0; i<3; i++) {
				v[0][i]=v000[i] = shapeVec[i].ImageFloatImage[k000];
				v[1][i]=v100[i] = shapeVec[i].ImageFloatImage[k100];
				v[2][i]=v_00[i] = shapeVec[i].ImageFloatImage[k_00];
				v[3][i]=v010[i] = shapeVec[i].ImageFloatImage[k010];
				v[4][i]=v0_0[i] = shapeVec[i].ImageFloatImage[k0_0];
				v[5][i]=v001[i] = shapeVec[i].ImageFloatImage[k001];
				v[6][i]=v00_[i] = shapeVec[i].ImageFloatImage[k00_];
			}

			for(i=0; i<7; i++) {
				shapeCount[s[i]]=0;
			}
			for(i=0; i<7; i++) {
				shapeCount[s[i]]++;	
			}

			switch(s000) {
				case lmrcImageShapeModeNoShape: {
					break;
				}
				case lmrcImageShapeModeSylinder: {
					break;
				}
				case lmrcImageShapeModeDisk: {
					
					break;
				}
				case lmrcImageShapeModeSphere: {
					break;
				}
				default: {
					break;
				}
			}
		}
		}
		}
	}
}
