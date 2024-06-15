/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageSymmetryFind ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageSymmetryFind 
#%Z% Attention
#%Z%
*/
#ifndef  LMRC_IMAGE_SYMMETRY_FIND_H 
#define  LMRC_IMAGE_SYMMETRY_FIND_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION

#undef DEBUG
#include "genUtil.h"
#include "Vector.h"
#include "lDescartesIntoPolar.h"
#include "lmrcImageTransformDescartesIntoPolar.h"
#include "mrcImage.h"

/* struct begin */
typedef enum lmrcImageSymmetryFindCheckType {
	lmrcImageSymmetryFindCheckTypeCheckByAdd=1,
	lmrcImageSymmetryFindCheckTypeCheckByCorrelation=2,
	lmrcImageSymmetryFindCheckTypeCheckByFourier=4,
	lmrcImageSymmetryFindCheckTypeCheckByTTest=8,
	lmrcImageSymmetryFindCheckTypeCheckBySRP=16
} lmrcImageSymmetryFindCheckType;

typedef enum lmrcImageSymmetryFindCentreType {
	lmrcImageSymmetryFindCheckTypeCentreGC       = 0,
	lmrcImageSymmetryFindCheckTypeCentreSymmetry = 1, 
	lmrcImageSymmetryFindCheckTypeCentreCentre = 2, 
	lmrcImageSymmetryFindCheckTypeCentreOrigin = 3 
} lmrcImageSymmetryFindCentreType;

typedef enum lmrcImageSymmetryFindSubtractionType {
	lmrcImageSymmetryFindCheckTypeNoSubtraction   = 0,
	lmrcImageSymmetryFindCheckTypeMeanSubtraction = 1,
	lmrcImageSymmetryFindCheckTypeMinSubtraction  = 2 
} lmrcImageSymmetryFindSubtractionType;

typedef struct lmrcImageSymmetryFindInfo {
	double dr;
	double dtheta;
	double threshold1;
	double threshold2;
	int    minNfold;
	int    maxNfold;

	double rmin;
	double rmax;
	
	/* Centre */
	lmrcImageSymmetryFindCentreType centreMode;
	lmrcImageDeterminationOfPolarAxisByAssumingNfoldInfo centreInfo;

	lmrcImageSymmetryFindSubtractionType subtractionMode; /* Subtraction Mode */
	int       flagImages;
	mrcImage  Image;
	mrcImage* Images;
	int       flagBacks;
	mrcImage  Back;
	mrcImage* Backs;
	
	floatVector Value;
	floatVector Point;
	int         Symmetry;

	FILE*    fptOut;

	int      flagCorrelation;
	mrcImage correlation;

	int      flagFourier;
	mrcImage  fourier;

	int      flagTmap;
	mrcImage tmap;

	int      flagAvg;
	mrcImage avg;
	char*    avgName;
	DescartesCoord centre;
} lmrcImageSymmetryFindInfo;

/* struct end */

/* prototype begin */
extern void 
lmrcImageSymmetryFind(mrcImage* in, lmrcImageSymmetryFindInfo* linfo, int mode); 

extern void
lmrcImageSymmetryFindCheckByAdd(mrcImage* in, lmrcImageSymmetryFindInfo* linfo, int mode);

extern void
lmrcImageSymmetryFindCheckByCorrelation(mrcImage* in, lmrcImageSymmetryFindInfo* linfo, int mode);

extern void
lmrcImageSymmetryFindCheckByFourier(mrcImage* in, lmrcImageSymmetryFindInfo* linfo, int mode);

extern void
lmrcImageSymmetryFindCheckByTTest(mrcImage* in, lmrcImageSymmetryFindInfo* linfo, int mode);

extern void
lmrcImageSymmetryFindCheckBySRP(mrcImage* in, lmrcImageSymmetryFindInfo* linfo, int mode);

extern void
lmrcImageSymmetryAverage(mrcImage* out, mrcImage* in, int num, DescartesCoord centre, int mode);

extern void
lmrcImageSymmetryFindResultOut(FILE* fpt, mrcImage* in, lmrcImageSymmetryFindInfo* linfo,  int mode);

extern void
lmrcImageSymmetryFindSubtraction(mrcImage* subout, mrcImage* in, lmrcImageSymmetryFindInfo* info, int mode);

extern void 
lmrcImageSymmetryFindModePrint(FILE* fpt);

extern void
lmrcImageSymmetryFindAlgorythmPrint(FILE* fpt);

extern void
lmrcImageSymmetryCentreFind(mrcImage* in, DescartesCoord* centre, int mode);

extern void
lmrcImageSymmetryCentreFindGC(mrcImage* in, DescartesCoord* centre, int mode);

extern void
lmrcImageSymmetryCentreFindSymmetry(mrcImage* in, DescartesCoord* centre, int mode);

/* prototype end */

#endif
