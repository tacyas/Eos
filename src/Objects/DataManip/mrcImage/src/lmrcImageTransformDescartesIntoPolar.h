#ifndef LMRC_IMAGE_TRANSFORM_DESCARTES_INTO_POLAR_H
#define LMRC_IMAGE_TRANSFORM_DESCARTES_INTO_POLAR_H
/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageTransformDescartesIntoPolar.h ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageTransformDescartesIntoPolar.h 
#%Z% Attention
#%Z%
*/

#include "mrcImage.h"
#include "lDescartesIntoPolar.h"

/* struct begin */
typedef struct lmrcImageDeterminationOfPolarAxisByAssumingNfoldInfo {
	int nFold;
	double minx;
	double maxx;
	double delx;
	double miny;
	double maxy;
	double dely;
	double minz;
	double maxz;
	double delz;
	double delPHI;
} lmrcImageDeterminationOfPolarAxisByAssumingNfoldInfo;

typedef struct lmrcImageTransformDescartesIntoPolarInfo {
	double dr;        /* Angstrom */ 
	double dphi;      /* Radian */
	double dtheta;    /* Radian */ 
	int    flagImageCentreIsGravityCentre;
	int    flagDescartesIntoPolarInfo; 
	int    flagrWeight; 

	/* RotationalSymmetry */
	int    flagRotationalSymmetry;
	int    nRotationalSymmetry;
	lmrcImageDeterminationOfPolarAxisByAssumingNfoldInfo axisInfo;

	int    flagCentre;
	mrcImageParaTypeRealCoord Centre;
}  lmrcImageTransformDescartesIntoPolarInfo;

/* struct end */

/* prototype begin */
extern void lmrcImageTransformDescartesIntoPolar(
	mrcImage* out,
	mrcImage* in, 
	lmrcImageTransformDescartesIntoPolarInfo* linfo,
	lDescartesIntoPolarInfo* linfo2,
	long mode);


extern void
lmrcImageDeterminationOfPolarAxisByAssumingNfold(
	mrcImageParaTypeRealCoord* centre, 
	mrcImage* residue, 
	mrcImage* in, 
	lmrcImageDeterminationOfPolarAxisByAssumingNfoldInfo linfo, 
	int mode);
/* prototype end */

#endif 





