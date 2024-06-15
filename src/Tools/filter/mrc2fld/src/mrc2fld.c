/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrc2fld ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrc2fld
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrc2fld ver%I%; Date:%D% %Z%";
#define DEBUG
#include "genUtil.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#include "mrcImage.h"
#include "avsFile.h"
#include "lmrcImageModeChange.h"

typedef struct lmrc2fldInfo {
	float shiftx;
	float shifty;
	float shiftz;
	int   Inverse;
	double mag;

	int   flagRadiusCylindricalCoordinates;
} lmrc2fldInfo;

extern void lmrc2fld(avsFileField* avs , mrcImage* mrc, lmrc2fldInfo* info, long mode);

int
main(int argc, char* argv[]) 
{
	mrc2fldInfo info;
	mrcImage mrc;
	mrcImage out;
	avsFileField avs;
	lmrc2fldInfo linfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	mrcFileRead (&mrc, info.In, "in main routine", 0);

	linfo.shiftx = info.shiftx;
	linfo.shifty = info.shifty;
	linfo.shiftz = info.shiftz;
	linfo.Inverse = info.I;
	linfo.mag     = info.Mag;

	linfo.flagRadiusCylindricalCoordinates = info.RadiusCylindrical;
	
	if(mrc.HeaderMode!=info.mode) {
		lmrcImageModeChange(&out, &mrc, info.mode);
	} else {
		out = mrc;
	}
	lmrc2fld (&avs, &out, &linfo, info.mode); 

	avsFileFieldWrite(&avs, info.fptOut, 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
		fprintf(stderr, "mode 0:Char(Byte) Image \n");
		fprintf(stderr, "       If you want to use volume rendering, you must select Char.\n");
		fprintf(stderr, "mode 2:Float Image \n");
		fprintf(stderr, "mode 102:Double Image \n");
		fprintf(stderr, "       If you want to use for contour image, you should select Float/Double.\n");
}

void
lmrc2fld (avsFileField* avs, mrcImage* mrc, lmrc2fldInfo* info, long mode)
{
	int byte;
	int i;
	double data;
	double mag;
	mrcImageParaTypeReal x, y, z;
	size_t offset;

	if(1==mrc->HeaderN.z) {
		if(1==mrc->HeaderN.y) { /* 1-D */
			DEBUGPRINT("in Dim 1\n");
			avs->ndim = 1;
			avs->dim1 = mrc->HeaderN.x;
			avs->nspace = 1;
		} else { 				/* 2-D */
			DEBUGPRINT("in Dim 2\n");
			avs->ndim = 2;
			avs->dim1 = mrc->HeaderN.x;
			avs->dim2 = mrc->HeaderN.y;
			avs->nspace = 2;
		}
	} else { 					/* 3-D */
		DEBUGPRINT("in Dim 3\n");
		avs->ndim = 3;
		avs->dim1 = mrc->HeaderN.x;
		avs->dim2 = mrc->HeaderN.y;
		avs->dim3 = mrc->HeaderN.z;
		avs->nspace = 3;
	}
	avs->veclen = 1;
	if(info->flagRadiusCylindricalCoordinates) {
		avs->veclen++;
	}
	switch(mrc->HeaderMode) {
		case mrcCharImage: {
			avs->dataType = avsFileFieldDataTypeByte;
			byte = 1;
			break;
		}
		case mrcFloatImage: {
			avs->dataType = avsFileFieldDataTypeFloat;
			byte = 4;
			break;
		}
		case mrcDoubleImage: {
			avs->dataType = avsFileFieldDataTypeDouble;
			byte = 8;
			break;
		}
		default: {
			fprintf(stderr, "Not supported data: %ld\n", mode);
			exit(EXIT_FAILURE);
		}
	}

	avs->type = avsFileFieldTypeRectilinear;

	avsFileFieldInit(avs, 0);

	i = 0;
	avs->Label[i] = strdup("Density");
	if(info->flagRadiusCylindricalCoordinates) {
		i++;
		avs->Label[i] = strdup("Radius");
	}


	i = 0;
	if(info->Inverse) {
		mag = info->mag*(-1);
	} else {
		mag = info->mag;
	}
	for(x=0; x<mrc->HeaderN.x; x++) {		
	for(y=0; y<mrc->HeaderN.y; y++) {		
	for(z=0; z<mrc->HeaderN.z; z++) {		
		mrcPixelDataGet(mrc, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
		offset = (x + y*mrc->HeaderN.x + z*mrc->HeaderN.x*mrc->HeaderN.y)*byte*avs->veclen + i*byte;
		switch(mrc->HeaderMode) {
			case mrcCharImage: {
				*((char*)((char*)avs->Image+offset)) = (char)data*mag;
				break;
			}
			case mrcFloatImage: {
				*((float*)((char*)avs->Image+offset)) = (float)data*mag;
				break;
			}
			case mrcDoubleImage: {
				*((double*)((char*)avs->Image+offset)) = (double)data*mag;
				break;
			}
			default: {
				fprintf(stderr, "Not supported data: %ld\n", mode);
				exit(EXIT_FAILURE);
			}
		}
	}
	}
	}	

	if(info->flagRadiusCylindricalCoordinates) {
		double radius;

		i++;
		for(x=0; x<mrc->HeaderN.x; x++) {		
		for(y=0; y<mrc->HeaderN.y; y++) {		
		for(z=0; z<mrc->HeaderN.z; z++) {
			radius = sqrt(SQR((x+mrc->HeaderStartN.x-(mrc->HeaderN.x-1)/2)*mrc->HeaderLength.x+info->shiftx)
			             +SQR((y+mrc->HeaderStartN.y-(mrc->HeaderN.y-1)/2)*mrc->HeaderLength.y+info->shifty));

			offset = (x + y*mrc->HeaderN.x + z*mrc->HeaderN.x*mrc->HeaderN.y)*byte*avs->veclen + i*byte;
			switch(mrc->HeaderMode) {
				case mrcCharImage: {
					*((char*)((char*)avs->Image+offset)) = (char)radius;
					break;
				}
				case mrcFloatImage: {
					*((float*)((char*)avs->Image+offset)) = (float)radius;
					break;
				}
				case mrcDoubleImage: {
					*((double*)((char*)avs->Image+offset)) = (double)radius;
					break;
				}
				default: {
					fprintf(stderr, "Not supported data: %ld\n", mode);
					exit(EXIT_FAILURE);
				}
			}
		}
		}
		}	
	}

	for(i=0; i<mrc->HeaderN.x; i++) { 
		avs->Coord[0][i] = (i+mrc->HeaderStartN.x)*mrc->HeaderLength.x + info->shiftx;
	}
	if(2<=avs->ndim) {
		for(i=0; i<mrc->HeaderN.y; i++) { 
			avs->Coord[1][i] = (i+mrc->HeaderStartN.y)*mrc->HeaderLength.y + info->shifty;
		}
	}
	if(3<=avs->ndim) {
		for(i=0; i<mrc->HeaderN.z; i++) { 
			avs->Coord[2][i] = (i+mrc->HeaderStartN.z)*mrc->HeaderLength.z + info->shiftz;
		}
	}
}
