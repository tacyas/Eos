/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageCorrelation.h ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageCorrelation.h 
#%Z% Attention
#%Z%
*/

#ifndef MRC_CORRELATION_H
#define MRC_CORRELATION_H


#include "mrcImage.h"
#include "PVM.h"
#include "lmrcImageSSDA.h"

/* struct begin */
typedef enum lmrcImageAutoRotationCorrelationMethod {
	lmrcImageAutoRotationCorrelationMethodRotationAndCorrelation     = 0,
	lmrcImageAutoRotationCorrelationMethodRotationAndCorrelationSSDA = 1,
	lmrcImageAutoRotationCorrelationMethodRotationalFunction         = 2
} lmrcImageAutoRotationCorrelationMethod;

typedef struct lmrcImageAutoRotationCorrelationInfo {
/* Input */
	int iter; /* iteration */
	int nRot; /* Rotation */  
	lmrcImageAutoRotationCorrelationMethod Method; /* Correlation Method */

	int flagRestrictionArea;
	float thetaMin;
	float thetaMax;

	int flagShiftRange;
	float shiftMinX;
	float shiftMinY;
	float shiftMaxX;
	float shiftMaxY;

	int   flagXshiftOnly;
	int   flagNoShift;

	int flagMagnification;
	float MagMin;
	float MagMax;
	float MagStep;

/* Control */

/* Output */
	float max; //
	float maxTheta; //
	mrcImageParaTypeRealCoord maxP;
	mrcImageInformation corInfo;
	lmrcImageSSDAInfo SSDAInfo;
	float EuclidDistance; 
	float LinearCorrelation;

} lmrcImageAutoRotationCorrelationInfo;

typedef struct lmrcImageCorrelationRefinementInfo {
	mrcImageParaTypeRealCoord shift; 
	mrcImageParaTypeRealCoord step; 
	mrcImageParaTypeRealCoord range; 
	mrcImageInformation corInfo;
	int mode;
} lmrcImageCorrelationRefinementInfo;

typedef enum lmrcImageAutoRotationCorrelationForManyReferencesRotationOrder {
	 lmrcImageAutoRotationCorrelationForManyReferencesStackOrderRot1Rot2Rot3=0,
	 lmrcImageAutoRotationCorrelationForManyReferencesStackOrderRot3Rot2Rot1=1
}  lmrcImageAutoRotationCorrelationForManyReferencesStackOrder;

typedef enum lmrcImageAutoRotationCorrelationForManyReferencesRefinementMode {
	 lmrcImageAutoRotationCorrelationForManyReferencesRefinementModeLinear  =0,
	 lmrcImageAutoRotationCorrelationForManyReferencesRefinementModeSetMode =1
}  lmrcImageAutoRotationCorrelationForManyReferencesRefinementMode;

typedef struct lmrcImageAutoRotationCorrelationForManyReferencesInfo {
    int    nRot1;           /* Image Number in Ref*/
    int    nRot1Step;       /* Coarse Step in Fitting */
    double nRot1AreaMin;    /* Min: Rotation Area in Fitting */
    double nRot1AreaMax;    /* Max: Rotation Area in Fitting */
    double nRot1AreaStep;   /* Step: Rotation Area in Fitting */
	double nRot1Delta;      /* Delta: Rotation Interval of Ref */
	double nRot1Start;      /* Start: Rotation Interval of Ref */

    int    nRot2;
    int    nRot2Step;
    double nRot2AreaMin;
    double nRot2AreaMax;
    double nRot2AreaStep;
	double nRot2Delta;
	double nRot2Start;

    int    nRot3;
    int    nRot3Step;
    double nRot3AreaMin;
    double nRot3AreaMax;
    double nRot3AreaStep;
	double nRot3Delta;
	double nRot3Start;

    int mode;

	lmrcImageAutoRotationCorrelationForManyReferencesStackOrder StackOrder;
	lmrcImageAutoRotationCorrelationForManyReferencesRefinementMode RefinementMode;

    char* In;
    FILE* fptOutASC; /* a file pointer for logging */
    char* Out;
    mrcImage out;

	/* for Linear Correlation */	
    char* corFile;
    mrcImage cor;
    char* fitFile;
    mrcImage fittedMap;

	/* for Set mode correlation */ 
    char* corFile2;
    mrcImage cor2;
    char* fitFile2;
    mrcImage fittedMap2;

} lmrcImageAutoRotationCorrelationForManyReferencesInfo;

#ifdef PVM
	
typedef struct lmrcImageCorrelationPVMInfo {
	int* tids;
	int  numTask;
} lmrcImageCorrelationPVMInfo;

#endif
/* struct end */

/* prototype begin */
extern void lmrcImageAutoRotationCorrelation(mrcImage* out, mrcImage* cor, mrcImage* in, mrcImage* ref, lmrcImageAutoRotationCorrelationInfo* linfo, int mode);
extern void lmrcImageAutoRotationCorrelationRotationalCrossCorrelationFunction(mrcImage* out, mrcImage* cor, mrcImage* in, mrcImage* ref, lmrcImageAutoRotationCorrelationInfo* linfo, int mode);
extern double lmrcImageLinearCorrelation(mrcImage* in1, mrcImage* in2, long mode);
extern void lmrcImageLinearCorrelation2(double* cor, mrcImage* in1, mrcImage* in2, long mode);
extern void lmrcImageCorrelation(mrcImage* cor, mrcImage* in, mrcImage* ref, long mode);
extern double lmrcImageEuclidDistanceCalc(mrcImage* in1, mrcImage* in2, int mode); 
extern void lmrcImageEuclidDistanceCalc2(double* cor, mrcImage* in1, mrcImage* in2, int mode); 
extern void lmrcImageCorrelationRefinement(mrcImage* cor, mrcImage* shift, mrcImage* in, mrcImage* ref, lmrcImageCorrelationRefinementInfo* info, long mode);


#ifdef PVM
extern void lmrcImageCorrelationServerStart(lmrcImageCorrelationPVMInfo* linfo, FILE* fpt, int numTask);
extern void lmrcImageCorrelationServerEnd(lmrcImageCorrelationPVMInfo linfo);

extern void lmrcImageCorrelationPVMStart(mrcImage* in, mrcImage* ref, lmrcImageAutoRotationCorrelationInfo* linfo, int tid, long mode);
extern void lmrcImageCorrelationPVMEnd(mrcImage* out, mrcImage* cor, lmrcImageAutoRotationCorrelationInfo* linfo, int tid, long mode);

extern void lmrcImageCorrelationServer();

extern void lmrcImageAutoRotationCorrelationInfoSendByPVM(lmrcImageAutoRotationCorrelationInfo* linfo, int tid, long mode);
extern void lmrcImageAutoRotationCorrelationInfoRecieveByPVM(lmrcImageAutoRotationCorrelationInfo* linfo, int tid, long mode);

#endif


extern void lmrcImageAutoRotationCorretionForManyReferences(mrcImage* in, mrcImage* ref,
    lmrcImageAutoRotationCorrelationForManyReferencesInfo* info,
    lmrcImageAutoRotationCorrelationInfo* linfo,
    int mode);
/* prototype end */

#endif

