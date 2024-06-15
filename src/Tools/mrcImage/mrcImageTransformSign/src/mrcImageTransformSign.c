/*
# mrcImageTransformSign : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageTransformSign
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
#include "mrcImage.h"

typedef enum lmrcImageTransformSignMode {
	lmrcImageTransformSignModeToSigned=0,
	lmrcImageTransformSignModeToUnsigned=1
} lmrcImageTransformSignMode;

typedef struct lmrcImageTransformSignInfo {
	lmrcImageTransformSignMode flagWork;	
	int Offset;	
} lmrcImageTransformSignInfo;

void lmrcImageTransformSign(mrcImage* out, mrcImage* in, lmrcImageTransformSignInfo linfo, int mode);
void lmrcImageTransformSignToSigned(mrcImage* out, mrcImage* in, lmrcImageTransformSignInfo linfo, int mode);
void lmrcImageTransformSignToUnsigned(mrcImage* out, mrcImage* in, lmrcImageTransformSignInfo linfo, int mode);

int
main(int argc, char* argv[]) 
{
	mrcImageTransformSignInfo info;
	lmrcImageTransformSignInfo linfo;
	mrcImage in;
	mrcImage out;

	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

	DEBUGPRINT("Program Start\n");
	
	if(info.toUnsigned) {
		linfo.flagWork = lmrcImageTransformSignModeToUnsigned; 
	} else {
		linfo.flagWork = lmrcImageTransformSignModeToSigned; 
	}
	linfo.Offset = info.Offset;

	mrcFileRead(&in, info.In, "in main", 0); 
	lmrcImageTransformSign(&out, &in, linfo, info.mode);

	mrcFileWrite(&out, info.Out, "in main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}


void
lmrcImageTransformSign(mrcImage* out, mrcImage* in, lmrcImageTransformSignInfo linfo, int mode)
{
	switch(linfo.flagWork) {
		case  lmrcImageTransformSignModeToUnsigned: {
			lmrcImageTransformSignToSigned(out, in, linfo, mode);
			break;
		}
		case  lmrcImageTransformSignModeToSigned: {
			lmrcImageTransformSignToUnsigned(out, in, linfo, mode);
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode in lmrcImageTrasnformSign: %d", linfo.flagWork);
			exit(EXIT_FAILURE);
		}	
	}
}

void
lmrcImageTransformSignToSigned(mrcImage* out, mrcImage* in, lmrcImageTransformSignInfo linfo, int mode)
{
	int i;
	int max;

	out->Header = in->Header;
	mrcInit(out, NULL);
	mrcTailerCopy(out, in, 1);

	max = out->HeaderN.x*out->HeaderN.y*out->HeaderN.z;

	switch(out->HeaderMode) {
		case mrcCharImage:
			for(i=0; i<max; i++) {
				out->ImageCharImage[i] =(signed char)((signed char)in->ImageCharImage[i] + (signed char)linfo.Offset);
			}
			break;	
		case mrcShortImage:
			for(i=0; i<max; i++) {
				out->ImageShortImage[i] =(signed short)((signed short)in->ImageShortImage[i] + (signed short)linfo.Offset);
			}
			break;	
		default: {
			fprintf(stderr, "Not supported mode in lmrcImageTrasnformSign: %d", out->HeaderMode);
			exit(EXIT_FAILURE);
		}	
	}
}


void
lmrcImageTransformSignToUnsigned(mrcImage* out, mrcImage* in, lmrcImageTransformSignInfo linfo, int mode)
{
	int i;
	int max;

	out->Header = in->Header;
	mrcInit(out, NULL);
	mrcTailerCopy(out, in, 1);

	max = out->HeaderN.x*out->HeaderN.y*out->HeaderN.z;

	switch(out->HeaderMode) {
		case mrcCharImage:
			for(i=0; i<max; i++) {
				out->ImageCharImage[i] =(unsigned char)((signed char)in->ImageCharImage[i] + (signed char)linfo.Offset);
			}
			break;	
		case mrcShortImage:
			for(i=0; i<max; i++) {
				out->ImageShortImage[i] =(unsigned short)((signed short)in->ImageShortImage[i] + (signed short)linfo.Offset);
			}
			break;	
		default: {
			fprintf(stderr, "Not supported mode in lmrcImageTrasnformSign: %d", out->HeaderMode);
			exit(EXIT_FAILURE);
		}	
	}
}


