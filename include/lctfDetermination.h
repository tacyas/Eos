/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lctfDetermination ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lctfDetermination 
#%Z% Attention
#%Z%
*/
#ifndef LCTF_DETERMINATION_H
#define LCTF_DETERMINATION_H

#include "mrcImage.h"
#include "ctfInfo.h"

typedef struct lctfDetermineInfo {
	ctfInfo initial;

	long    ThonRing; 	
	/* For Astigmatism */
	int     flagAstigmatism;
	int    section;

	int    degree;
	double step;
	double max;
	double min;
	float  firstRingDefocus;
	float  IntensityMin;
	float  IntensityMax;
	float* noise;
} lctfDetermineInfo;


/* prototype begin */

extern void lctfDetermine(ctfInfo* result, ctfInfo* var, mrcImage* mrc, lctfDetermineInfo* linfo, long mode);
extern void lctfDtermmineUsage(FILE* fpt);

extern void lctfDeterminationbyMinMaxMethods(ctfInfo* res, mrcImage* mrc, ctfInfo* ini, long mode);
extern void lctfDeterminationbyFittingMethods(ctfInfo* res, ctfInfo* var, mrcImage* mrc, ctfInfo* ini, long mode);
extern void angularDistributionFunctionOfSignalAndNoise(float x, float p[], float* y, float dyda[], int na);
extern void lctfDeterminationbyDifferentialMethods(ctfInfo* res, mrcImage* mrc, ctfInfo* ini,long* ThonRing, long mode);
extern void lctfDeterminationbyCovarianceMethods(ctfInfo* res, mrcImage* mrc, ctfInfo* ini,long* ThonRing, long mode);
extern void lctfDeterminationbyMixMethods(ctfInfo* res, mrcImage* mrc, ctfInfo* ini, long* ThonRing,long mode);
extern void lctfDeterminationbyMinSquareMethods(ctfInfo* res, mrcImage* mrc, ctfInfo* ini,long* ThonRing,lctfDetermineInfo* linfo,floatVector* defocus,floatVector* Eres ,long mode);
extern void lctfDeterminationbyMinSquareMethodsWithAcomp(ctfInfo* res, mrcImage* mrc, ctfInfo* ini,long* ThonRing,lctfDetermineInfo* linfo,floatVector* defocus,floatVector* Eres ,long mode);
extern double lctfDeterminationByTangent(ctfInfo* res, mrcImage* mrc, ctfInfo* ini,lctfDetermineInfo* linfo,floatVector* defocus,floatVector* Eres, long mode);
extern void EnvelopeDetermine(ctfInfo* res, mrcImage* mrc, ctfInfo* ini,lctfDetermineInfo* linfo,floatVector* defocus,floatVector* Eres, long mode);
/* prototype end */

#endif /* LCTF_DETERMINATION_H */

