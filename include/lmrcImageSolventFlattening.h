#ifndef  LMRC_IMAGE_SOLVENTFLATTENING_H 
#define  LMRC_IMAGE_SOLVENTFLATTENING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define UNDEBUG
#include "genUtil.h"
#include "mrcImage.h"

/* struct begin */
typedef struct lmrcImageSolventFlatteningInfo {
	double range;
	long   flagrange;

	double density;
	long flagdensity;

	long flagFloating;

	double Mean; /* set the used mean of solvent */	
	double SD; /* set the used SD of solvent */	
} lmrcImageSolventFlatteningInfo;
/* struct end */

/* prototype begin */
extern void lmrcImageSolventFlattening(mrcImage* out,
									   mrcImage* in,
								      lmrcImageSolventFlatteningInfo* linfo,
									   mrcImageInformation* info);
/* prototype end */
#endif
