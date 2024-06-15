#ifndef LLL_EXTRACT_INFO_H
#define LLL_EXTRACT_INFO_H
/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lllExtract.h ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lllExtract.h 
#%Z% Attention
#%Z%
*/

#include "mrcImage.h"
#include "llData.h"
#include "lllDataFit.h"
#include "lllDatarMaxLimit.h"

/* struct begin */
typedef struct lllExtractInfo {
    char* Title;
    float xStep;
    float yStep;
    float MaxX;
    float MaxY;
    float RotationAngle;
    float Omega;
    float Shear;
    long ievery; 
    float axl;
    float ayl;
    float xShift; 
    long llMax;
    llDataParaTypeReal delRInv; /* [A] */
    long flagOutputInfo; /* for Compati */
    long* n;
    long* nn;   /* number of diffenent n along l*/
    long** ns;  /* diffenent n's along l*/
    long* l;
    float* Y;
    float* leftMin;
    float* leftMax;
    float* rightMin;
    float* rightMax;
    float* weight; 
	llDataParaTypeReal truePitch;	
	lllDatarMaxLimitInfo rMax;
	llDataParaTypeReal   RMax;
	llDataParaTypeReal RMaxFirst;

	int flagMagnitudeLimit;
} lllExtractInfo;
/* struct end */

#ifdef __cplusplus
extern "C" {
#endif
/* prototype begin */

/* in lllExtract.c */
extern void lllExtract(llData* nea, llData* far, mrcImage* in, lllExtractInfo* info);


extern void lllExtractWithSeparationUsingFittingParameter(llData* dst, llDataBoth* src, 
		llDataFittedParam* param, 
		int number, 
		lllExtractInfo* info, 
		int mode);

extern void lllExtractWithSeparation(llDataBoth* dst, llDataBoth* src, 
		lllExtractInfo* info, int mode);
extern void lllExtractWithWeightedSeparation(llDataBoth* dst, llDataBoth* src, 
		llData* weight, lllExtractInfo* info, int mode);

extern void lllDatarMaxLimitForSeparation(llData* ll, float rMax, 
		lllExtractInfo* linfo, long mode);

extern void lllDataSeparationInfoRead(lllExtractInfo* linfo, mrcImage* mrc, FILE* fpt);
extern void lllDataSeparationInfoFileFormat(FILE* fpt);


extern void lllDataSeparationInfoTruePitchSet(lllExtractInfo* linfo, llDataParaTypeReal truePitch); 
extern void lllDataSeparationInfoDelRInvSet(lllExtractInfo* linfo, llDataParaTypeReal DelRInv);
extern void lllDataSeparationInfoxShiftSet(lllExtractInfo* linfo, llDataParaTypeReal xShift);
extern void lllExtractWeightSetFollowingllExtractInfo(llData* dst, lllExtractInfo* info, float weight, int mode);
/* prototype end */

#ifdef __cplusplus
};
#endif

#endif
