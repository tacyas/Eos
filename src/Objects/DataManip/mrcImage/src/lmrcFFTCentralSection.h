/*
# lmrcFFTCentralSection.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcFFTCentralSection.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#ifndef LMRC_FFT_CENTRAL_SECTION_H 
#define LMRC_FFT_CENTRAL_SECTION_H 

#include <stdio.h>
#include "mrcImage.h"

/* constant begin */


/* constant end */

/* struct begin */

typedef struct lmrcFFTCentralSectionInfo {
	char EulerMode[5];
	double Rot1;
	double Rot2;
	double Rot3;
	double TransX;
	double TransY;
	
	mrcPixelDataHowToGet InterpMode;

	int flagWeight;
	double weight;
} lmrcFFTCentralSectionInfo;

typedef struct lmrcFFTCentralSectionsGetInfo{
	double Rot1Start;
	double Rot1End;
	double Rot1Delta;
	int nRot1;
       
	double Rot2Start;
	double Rot2End;
	double Rot2Delta;
	int nRot2;
      
	double Rot3Start;
	double Rot3End;
	double Rot3Delta;
	int nRot3;
      
	int RotSize;
      
	lmrcFFTCentralSectionInfo llinfo;
}lmrcFFTCentralSectionsGetInfo;

typedef struct lmrcMultiFFTCentralSectionsCompareInfoOut{
	
	mrcImage out;
	char volume[256];
    char EulerMode[5];
	double Rot[3];
	double Likelihood;
	double Prob;
    double Prior;
    double Post;
    //double Variat;
    int OriginNum;
}lmrcMultiFFTCentralSectionsCompareInfoOut;

typedef struct lmrcMultiFFTCentralSectionsCompareInfo{

	char EulerMode[5];
	lmrcFFTCentralSectionsGetInfo llinfo;
	int OutSize;
    int PriorSize;
    double Variat;
    double** Sigma;
    double SigMin;
    lmrcMultiFFTCentralSectionsCompareInfoOut* Out;
	lmrcMultiFFTCentralSectionsCompareInfoOut* Prior;
}lmrcMultiFFTCentralSectionsCompareInfo;

typedef struct lmrcFFTCentralSectionCompareInfo{
	float* Likelihood;
	mrcImage vol2d;

	lmrcFFTCentralSectionInfo llinfo;

}lmrcFFTCentralSectionCompareInfo;


/* struct end */

#ifdef __cplusplus
extern "C" {
#endif

/* prototype begin */

extern void lmrcFFTCentralSectionGet(mrcImage* out, mrcImage* template3D, mrcImage* volume, lmrcFFTCentralSectionInfo* linfo, int mode);

extern void lmrcImageFFTRhoFilter(mrcImage* volFT, mrcImage* count, lmrcFFTCentralSectionInfo* linfo, int mode);
//extern void lmrcImageFFTCentralSectionPut(mrcImage* volFT, mrcImage* count, mrcImage* template3D, mrcImage* in, lmrcFFTCentralSectionInfo* linfo, int* c, int mode);
extern void lmrcImageFFTCentralSectionPut(mrcImage* volFT, mrcImage* count, mrcImage* template3D, mrcImage* in, lmrcFFTCentralSectionInfo* linfo, int* c, int mode);

//lmrcFFTCentralSectionCompare.c
extern void lmrcFFTCentralSectionCompare(mrcImage* in, mrcImage* volume, lmrcFFTCentralSectionCompareInfo* linfo, int mode);
extern void lmrcFFTCentralSectionCompareInfoWrite(FILE* fpt, float Likelihood, int mode);
extern void lmrcFFTCentralSectionCompareInfoWriteLikelihood(FILE* fpt, float Likelihood, int mode);

//lmrcMultiFFTCentralSectionsComapre
extern void lmrcFFTCentralSectionsGet(lmrcMultiFFTCentralSectionsCompareInfoOut* Out, mrcImage* template3D, mrcImage* volume, lmrcMultiFFTCentralSectionsCompareInfo* linfo, int mode, int nummode);
extern void lmrcMultiFFTCentralSectionsCompare(lmrcMultiFFTCentralSectionsCompareInfoOut* Out, mrcImage* in, mrcImage* volume, lmrcMultiFFTCentralSectionsCompareInfo* linfo, int mode, int nummode);
extern void lmrcMultiFFTCentralSectionsCompareNormalization(lmrcMultiFFTCentralSectionsCompareInfoOut* Out, lmrcMultiFFTCentralSectionsCompareInfo* linfo, int mode);
extern void lmrcMultiFFTCentralSectionsCompareInfoWrite(FILE* fpt, char* filename, lmrcMultiFFTCentralSectionsCompareInfoOut* Out, lmrcMultiFFTCentralSectionsCompareInfo* linfo, float mode1, float mode2);

extern void lmrcMultiFFTCentralSectionsCompareInfoWriteLikelihood(FILE* fpt, char* filename, lmrcMultiFFTCentralSectionsCompareInfoOut* Out, lmrcMultiFFTCentralSectionsCompareInfo* linfo, float mode1, float mode2);

extern void lmrcMultiFFTCentralSectionsCompareInfoSort(lmrcMultiFFTCentralSectionsCompareInfoOut Out[], int left, int right);
extern void lmrcMultiFFTCentralSectionsCompareInfoProbSet(lmrcMultiFFTCentralSectionsCompareInfo* linfo ,int mode); 
extern void lmrcMultiFFTCentralSectionsCompareInfoLimit(lmrcMultiFFTCentralSectionsCompareInfoOut* Out, lmrcMultiFFTCentralSectionsCompareInfo* linfo, float mode1, float mode2);
extern void lmrcMultiFFTCentralSectionsCompareInfoUpdate(lmrcMultiFFTCentralSectionsCompareInfoOut* Out, lmrcMultiFFTCentralSectionsCompareInfo* linfo);
extern void lmrcMultiFFTCentralSectionsCompareInfoVariation(lmrcMultiFFTCentralSectionsCompareInfoOut* Out, lmrcMultiFFTCentralSectionsCompareInfo* linfo);
  extern void lmrcMultiFFTCentralSectionsCompareSigma(mrcImage* in, lmrcMultiFFTCentralSectionsCompareInfo* linfo, int mode);
/* prototype end */


#ifdef __cplusplus
};
#endif

#endif  /* LMRC_FFT_CENTRAL_SECTION_H */ 
