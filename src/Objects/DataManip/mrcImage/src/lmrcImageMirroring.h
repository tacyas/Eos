/*
# lmrcImageMirroing.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageMirroing.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include "mrcImage.h"

typedef enum lmrcImageMirroringMode {
	lmrcImageMirroringModeYZPlane = 0 
} lmrcImageMirroringMode;

extern void lmrcImageMirroring(mrcImage* out, mrcImage* in, lmrcImageMirroringMode mode);
extern void lmrcImageMirroringYZPlane(mrcImage* out, mrcImage* in, lmrcImageMirroringMode mode);

extern void lmrcImageMirroringUsage(FILE* fpt);
