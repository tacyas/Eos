#ifndef MRC_CTF_DETERMINATION_H
#define MRC_CTF_DETERMINATION_H

/* in lmrcImageCTFDetermination.c */

#include "ctfInfo.h"
#include "mrcImage.h"
#include "lllDataCTFCompensate.h"
#include "lll2ltlg.h"
#include "lltlg2mrc.h"
#include "lmrcImageSolventFlattening.h"
#include "lmrcImageProjection.h"
#include "lmrcImageCrystalCreate.h"
#include "lllExtractdYEstimate.h"
#include "lmrcImagePad.h"

/* struct begin */
typedef struct lmrcImageCTFDeterminationInfo {
	ctfInfo val;
	ctfInfo min;
	ctfInfo max;
	ctfInfo del;
	mrcImageParaTypeReal Rmax;
	mrcImageParaTypeReal Rmin;
	mrcImage Dif;
	double minResidual;
	double minDef;
	double minRatio;
	FILE*   Out;
	int flagOutF;
	mrcImage resFFT;
} lmrcImageCTFDeterminationInfo;

typedef struct lmrcImageCTFDeterminationInfoMode {
	long FilterType;
	long WeightType;
	long SumType;
	long CTFInfoType;
} lmrcImageCTFDeterminationInfoMode;

typedef struct lmrcImageCTFDeterminationInfoRef {
	FILE* fptIn;
	char* In;
	FILE* fptRef;
	char* Ref;
	FILE* fptOut;
	char* Out;
	char MrcOut[100];
	mrcImage* in;
	mrcImage* out;
	long Width;
	float PixelSize;
	float truePitch;
	float firstDf;
	float withinDf;
	float firstAoverP;
	float withinAoverP;
	mrcImageParaTypeReal maxiter;
	mrcImageParaTypeReal iter;
} lmrcImageCTFDeterminationInfoRef;

/* struct end */

/* prototype begin */

extern void lmrcImageCTFDetermination (lmrcImageCTFDeterminationInfo *linfo, 
									   lmrcImageCTFDeterminationInfoRef *refinfo,
							 	        mrcImage* in, mrcImage* ref,
									   lmrcImageCTFDeterminationInfoMode *Mode);

extern void lmrcImageCTFDeterminationResultFFT (lmrcImageCTFDeterminationInfo *linfo, 
									    		lmrcImageCTFDeterminationInfoRef *refinfo,
							 	        	     mrcImage* in, mrcImage* ref,
									   			lmrcImageCTFDeterminationInfoMode *Mode);

extern double MagWeightForCTFDetermine(double inMag, double refMag, 
									 long mode); 

extern void lmrcImageCTFDeterminationCreateRefFilebyNearFar3DReconstInitializeLL
							(lmrcImageCTFDeterminationInfoRef *refinfo,
							 lllDataCTFCompensateInfo *llctfinfo,
							 lll2ltlgInfo *ll2ltlginfo,
							 lltlg2mrcInfo *ltlg2mrcinfo);
							 
extern void lmrcImageCTFDeterminationCreateRefFilebyNearFar3DReconstInitializeMRC
							(lmrcImageCTFDeterminationInfoRef *refinfo,
						     mrcImageInformation *solinfo, 
							 lmrcImageProjectionInfo *projinfo,
							 lmrcImageCrystalCreateInfo *cryinfo,
							 lmrcImagePadInfo *padinfo);
							 
extern void lmrcImageCTFDeterminationCreateRefFilebyNearFar3DReconstLL
							(lmrcImageCTFDeterminationInfoRef *refinfo,
							 lllDataCTFCompensateInfo *llctfinfo,
							 lll2ltlgInfo *ll2ltlginfo,
							 lltlg2mrcInfo *ltlg2mrcinfo);
							 
extern void lmrcImageCTFDeterminationCreateRefFilebyNearFar3DReconstMRC
							(lmrcImageCTFDeterminationInfoRef *refinfo,
						     mrcImageInformation *solinfo, 
							 lmrcImageProjectionInfo *projinfo,
							 lmrcImageCrystalCreateInfo *cryinfo,
							 lmrcImagePadInfo *padinfo);
							 
/* prototype end */

#endif

