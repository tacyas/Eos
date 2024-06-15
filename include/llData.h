/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% llData.h ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : llData.h 
#%Z% Attention
#%Z%
*       Edited by tacyas@tkyemg
*       1992.10.24-
*/    

#ifndef LL_DATA_H
#define LL_DATA_H

#include <stdio.h>
#include <math.h>
#include "ctfInfo.h"

/* constant begin */
typedef unsigned int llDataStatusType;

#define llDataStatusOK          ((llDataStatusType)0x00000000)

/* ReferFile */
#define llDataCanNotReadFile    ((llDataStatusType)0x00010000);
#define llDataCanNotWriteFile   ((llDataStatusType)0x00010001);


#ifdef __LLDATAINIT__ 
char* llDataErrorMsgReferFile[] = {
    "File Pointer ",
    ""
};

char* llDataReferenceData[] = {
"Amos,L.A. & Klug,A. J.Mol.Biol(1975),99,51-73",
"  Three-dimensional Image Reconstructions of the Contractile Tail of T4 Bacteriophage",
"  Appendix: Combination of Data from Helical Particles : Correlation and Selection",
"              Amos,L.A",
"              delta(theta)= -n*delta(phi) + 2*PI*Z*delta(z)",
"                Klug,A. Crick,A., F.H.C. & Wyckoff,H.W. Acta Crystallogr.sect.(1958),11,199-213",
NULL
}; 

#else
extern char* llDataErrorMsgReferFile[];
extern char* llDataReferenceData[]; 
#endif

#define DefaultStringLength (256)
#define NearSide    (0)
#define FarSide     (1)
#define AverageSide (2)
#define SidePosition (14)
#define CommentLength  (80)
#define WeightPosition (SidePosition+4+CommentLength)
#define NNPosition     (WeightPosition+12)
#define NLPosition     (NNPosition+5)
#define LLDataFormat  "%12.5e%12.5e%12.5e\n"
#define LLDataFormat0 "%12.5e%12.5e%12.5e"
#define LLDataFormat1 "%12.5e %12.5e %12.5e"
#define RRPosition     (0)
#define FPosition      (RRPosition+12)
#define PHIPosition    (FPosition +12)


#define PVALUE_MODE  (0x01)
#define QVALUE_MODE  (0x02)
#define RVALUE_MODE  (0x04)
#define Q2VALUE_MODE (0x08)

typedef int   llDataParaTypeInteger;
typedef float llDataParaTypeReal;
typedef enum llDataPole {
	llDataPoleNormal = 0,
	llDataPoleAnti   = 1
} llDataPole;

typedef enum llDataMode {
    llDataModeMemoryNotAllocate = 0, 
    llDataModeMemoryAllocate = 1
} llDataMode;
/* contant end */

/* struct begin */

typedef struct llComplex {
    llDataParaTypeReal      R;  /* Spherical R */ 
    llDataParaTypeReal      RR; /* Radial R    */ 
    llDataParaTypeReal      F;  /* F*exp(PHI)  */
    llDataParaTypeReal      PHI;
    llDataParaTypeReal      Re; /* Re + i * Im */
    llDataParaTypeReal      Im;
} llComplex;

typedef struct oneLLData {
    char					Head[DefaultStringLength]; /* Comment */
	llDataParaTypeReal      Weight;  /* Weight of This Layer Line */
    llDataParaTypeInteger   nn;      /* The [n] dim. Bessel function */
    llDataParaTypeInteger   nl;      /* The [l]th layer line  */
    llDataParaTypeInteger   nm;      /* [l] = t*[n]+s*[m] */
    llComplex*              data;    /* Layer line data */
	llDataParaTypeInteger   Side;    /* Near/Far Side/Average */
    llDataParaTypeInteger   nR;      /* Number of layer line data */

	llDataParaTypeReal     Z;   
	llDataParaTypeInteger iZ;
	llDataParaTypeReal     RMin; /* Radial R Info */
	llDataParaTypeInteger iRMin;
	llDataParaTypeReal     RMax;
	llDataParaTypeInteger iRMax;
	llDataParaTypeReal    delBR;
	llDataParaTypeReal    Fmax;  /* Fmax */
    long dummy;
} oneLLData;

typedef struct llData {
    llDataMode            mode;
    llDataParaTypeInteger llMax;
    llDataParaTypeInteger nRMax;
    llDataParaTypeReal    truePitch;
    llDataParaTypeReal    Weight;
    llDataParaTypeReal    rScale;
	llDataPole            Pole;
	llDataParaTypeReal    Side;
	llDataParaTypeInteger RRInfoSet;
	llDataParaTypeInteger FmaxSet;
	llDataParaTypeInteger RValueSet;
	llDataParaTypeInteger ZValueSet;
    oneLLData* LL;
} llData;

typedef struct llDataBoth {
	llData Nea;
	llData Far;
} llDataBoth;

typedef struct llDataAttributes {
    llDataMode            mode;
    llDataParaTypeInteger llMax;
    llDataParaTypeInteger nRMax;
    llDataParaTypeReal    truePitch;
    llDataParaTypeReal    Weight;
    llDataParaTypeReal    rScale;
	llDataPole            Pole;
	llDataParaTypeReal    Side;
    oneLLData* LL;
} llDataAttributes;

/* in llDataIntensityInformationGet.c */
typedef struct onelllDataIntensityInformation {
	int LL;
	int n;
	int l;
	int flagI;
	double I;
	int flagPeak;
	double Peak;
} onelllDataIntensityInformation;

typedef struct lllDataIntensityInformation {
	onelllDataIntensityInformation* onedata;
    llDataParaTypeInteger llMax;
} lllDataIntensityInformation;

/* struct end */


/* prototype begin */
#ifdef __cplusplus
extern "C" {
#endif

/* in llDataRead.c */
extern void llDataFileRead(FILE* fpt, llData* ll, llDataParaTypeInteger* status);
extern void llDataFileReadFollowingllData(FILE* fpt, llData* ll, llData* Ref, llDataParaTypeInteger* status);
extern void llDataFileReadFollowingAttributes(FILE* fpt, llData* ll, llDataAttributes* attr, llDataParaTypeInteger* status);

/* in llDataWrite.c */
extern void llDataFileWrite(FILE* fpt, llData* ll, llDataParaTypeInteger* status);

/* in llDataInit.c */
extern void llDataInit(llData* ll);
extern void llDataInitWithReference(llData* ll, llData* ref);
extern void llDataInitWithReference2(llData* ll, llData* ref, int side);
extern void llDataHeaderInit(llData* ll);
extern void llDataDataInit(llData* ll);
extern void llDataFree(llData* ll);
extern void llDataHeaderFree(llData* ll);
extern void llDataDataFree(llData* ll);

/* in llDataInfo.c */
extern void llDataInfoPrint(FILE* fpt, llData* ll, long WhichLayer, long WhatInfo);
extern void llDataInfoPrintUsage(FILE* fpt);

/* in llDataUtil.c */
extern void llDataRValueSet(llData* dst, int mode);
extern void llDataFmaxSet(llData* dst, int mode);
extern void llDataZValueSet(llData* dst, int mode);

extern llDataParaTypeInteger* llDataTableBetweenTwollDataCreate(llData* ll1, llData* ll2, int mode);

extern inline llDataParaTypeReal nearSidePhaseGet(llDataParaTypeReal phase, 
    llDataParaTypeInteger nn, 
    llDataParaTypeInteger side, 
    llDataParaTypeInteger pole);
extern inline llDataParaTypeReal farSidePhaseGet(llDataParaTypeReal phase, 
    llDataParaTypeInteger nn, 
    llDataParaTypeInteger side, 
    llDataParaTypeInteger pole);
extern void lllDataAttributeCopy(llData* ll1, llData* ll2);
extern void lllDataHeaderCopy(llData* ll1, llData* ll2);
extern void lllDataCopy(llData* ll1, llData* ll2);
extern void lllDataClear(llData* ll1);
extern void lllDataMul(llData* ll1, llData* ll2);
extern void lllDataPoleSet(llData* ll1, llDataPole pole);
extern void lllDataSideSet(llData* ll1, llDataParaTypeInteger Side);
extern void lllDataMultiplyReal(llData* ll1, llDataParaTypeReal f);
extern void lllDataDevidedByReal(llData* ll1, llDataParaTypeReal f);

/* in lllDataAdd.c */
extern void lllDataAdd(llData* ll1, llData* ll2);
extern void lllDataAdd2(llData* ll, llData* ll1, llData* ll2);

/* in lllDataAvgTo */
extern void lllDataAvgTo(llData* dst, llData* src, llDataParaTypeInteger Side);
extern void lllDataAvgToNea(llData* nea, llData* avg);
extern void lllDataAvgToFar(llData* far, llData* avg);

/* lllDataWeightSet.c */
extern void lllDataWeightSet(FILE* fpt, llData* ll, llDataParaTypeReal w, long mode); 
					/* FILE FORMAT 
					   nn nl weight
					   ............
					   Mode 0: llData.LL[].Weight = 0 without Definition 
					*/

/* llDataGet.c */
extern inline long llDataValueGet(llData* ll, long l, double R, double* re, double *im);
extern inline long llDataValueGet2(llData* ll, long nn, long nl, double R, double* re, double *im);
extern long llDataLayerNumberGet(llData* ll, long n, long l);
extern long llDataNLNumberGet(llData* ll);

/* llDataSet.c */
extern void llDataFandPHISet(llData* ll);
extern void llDataReAndImSet(llData* ll);
extern void llDataRRSet(llData* ll);
extern void llDataRRInfoSet(llData* ll);
extern void llDataAttributesSet2(llData* dst, llData* src);

/* llDataCheck.c */
extern long llDataSizeCheck(llData* ll1, llData* ll2, char* message);

/* in llDataIntensityInformationGet.c */
extern void lllDataIntensityInformationGet(llData* in, lllDataIntensityInformation* data, int mode);

/* in llDataError.h */
extern void llDataError(char* s);
extern void llDataErrorMessage(void);

#ifdef __cplusplus
};
#endif

/* prototype end */

#endif /* LL_DATA_H */ 
