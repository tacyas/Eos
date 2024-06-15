/*
# lmrcSinogramFET.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcSinogramFET.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include <stdio.h>
#include<math.h>
#include "mrcImage.h"
#include "Array.h"
#define NumOfFeature 7 
#define FETwidth 0
#define FETasymmetry 1
#define FETkur 2


typedef struct lmrcSinogramFETInfo {
	int flagOutC;
	mrcImage* OutC;
	int flagsm;
	int sm;
	int outmode; // 1: ordinary 8 features 0: new 3 features
	int mode;
}lmrcSinogramFETInfo;

typedef struct lmrcSinogramFETPCAInfo{
	FILE* inList;
	int flagInImage;
	mrcImage* inImage;
	Array X;
	Array Ave;
	Array C;
	Array u;
	Array lambda;
	Array fetpcad;
	FILE* Out;
	int mode;
}lmrcSinogramFETPCAInfo;

extern void lmrcSinogramFETPCA(lmrcSinogramFETPCAInfo in, int mode);
extern void lmrcSinogramFET(mrcImage* in, mrcImage* out, lmrcSinogramFETInfo info, int mode);
extern void lmrcSinogramFETc(mrcImage* out, mrcImage* OutC, int mode);
extern void sinogramFETsmoothing(mrcImage* in, mrcImage* out, int sm, int mode);
extern void lmrcSinogramFETminimam_Zero(mrcImage* in, mrcImage* out, int mode);
extern void lmrcSinogramFETcutout(mrcImage* in, mrcImage* out, int mode);

