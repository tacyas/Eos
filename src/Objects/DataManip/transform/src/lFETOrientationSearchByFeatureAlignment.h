/*
# lFETOrientationSearchByFeatureAlignment.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lFETOrientationSearchByFeatureAlignment.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "genUtil.h"
#include "Memory.h"
#include "File.h"
#include "eosString.h"
#include "mrcImage.h"
#include "Array.h"
//#include "../../mrcImage/src/lmrcSinogramFET.h"
#include "lmrcSinogramFET.h"
#include "Matrix3D.h"
#include "lFETmapOrientationSearchBySimultaneousFitting.h"
#define SphereDevNum 2100 

typedef struct lFETOrientationSearchByFeatureAlignmentInfo{
    FILE* In;
	FILE* In2;
    int flagInType; // 0:Sinogram 1:FET
	int flagIn2;
    FILE* Out;
	int ldn;
	double srl;
	int flagInA, flagOutA, flagOut2D, flagOutLOG;
	int itmax, devmax, mitmax, mdevmax;
	FILE* InA;
	FILE* OutA;
	FILE* Out2D;
	FILE* OutLOG;
    int mode;
}lFETOrientationSearchByFeatureAlignmentInfo;

typedef struct lFETFeatureAlignmentCoord{
	double x, y, z;
}lFETFeatureAlignmentCoord;

typedef struct lFETFeatureAlignmentFeature{
	double t, w, a, k;
}lFETFeatureAlignmentFeature;

/*typedef struct lFETFeatureAlignmentImageInfoClass{
	int max, min;
	int group;
}lFETFeatureAlignmentImageInfoClass;
*/								 

typedef struct lFETFeatureAlignmentSpherePointInfo{
	lFETFeatureAlignmentCoord self;
	lFETFeatureAlignmentFeature fets;
	lFETFeatureAlignmentFeature nfets;
	int nnum;
}lFETFeatureAlignmentSpherePointInfo;


typedef struct lFETFeatureAlignmentImageInfo{
    char imagename[256];
    lFETFeatureAlignmentFeature* fets;
    double lenmax;
    double lenmin;
	double lensum;
    int posmax;
    int posmin;
	int flagLX;
	double interAngle;
	lFETFeatureAlignmentCoord norm, base, yoys;
	//lFETFeatureAlignmentImageInfoClass group;
	lFETFeatureAlignmentSpherePointInfo* spt[2];
	int next;
}lFETFeatureAlignmentImageInfo;

typedef struct lFETFeatureAlignmentImageQSInfo{
	lFETFeatureAlignmentFeature** corset;
	int** cset;
	int* lxseries;
	int* nseries;
	int seed;
	int num;
}lFETFeatureAlignmentImageQSInfo;

typedef struct lFETFeatureAlignmentSphereSquareInfo{
	lFETFeatureAlignmentSpherePointInfo** sq;
	int center;
}lFETFeatureAlignmentSphereSquareInfo;

typedef struct lFETFeatureAlignmentSphereInfo{
	lFETFeatureAlignmentSphereSquareInfo sq6[2][6];
	int curSwitch;
	int mode;
}lFETFeatureAlignmentSphereInfo;
									   
typedef struct lFETFeatureAlignmentInfo{
    lFETFeatureAlignmentImageInfo* images;
    int imagey;
    int imagenum;
    double llong;
    double lmiddle;
	double lmiddles;
    double lshort;
	int ldn;
	double srl;
	double corave;
	FILE* OutLOG;
	//int groupnum[9];
	//int groups[9];
	int seedImage, smallImage;
	lFETFeatureAlignmentSphereInfo sph;
	//lFETFeatureAlignmentSpherePointInfo* spt;
    int mode;
}lFETFeatureAlignmentInfo;

typedef struct lFETFeatureAlignment_multiselectInfo{
	lFETFeatureAlignmentImageInfo* images;
	double max;
}lFETFeatureAlignment_multiselectInfo;

typedef struct lFETFeatureAlignment_i11LMLXsInitInfo{
	int lmList[10];
	int lxList[10];
	int pos[10][10];
	//int rev[10][10];
	double cvalue[10];
	double cor[10][10][2]; 
}lFETFeatureAlignment_i11LMLXsInitInfo;

typedef struct lFETFeatureAlignment_i2LMsLXsInitInfo{
	int ser[2][5][10];
	int num[2];
}lFETFeatureAlignment_i2LMsLXsInitInfo;

typedef struct lFETFeatureAlignment_i1LssInitInfo{
	lFETFeatureAlignmentImageInfo* images[10];
	int** angle[10];
	int** nums[10];
	int** max;
}lFETFeatureAlignment_i1LssInitInfo;

typedef struct lFETFeatureAlignment_initmSelecterInfo{
	int mode;
	FILE* InA;
	int itmax,devmax,mitmax,mdevmax;
	lFETFeatureAlignmentInfo* faInfo;
	lFETFeatureAlignment_multiselectInfo multi;
	lFETFeatureAlignment_i11LMLXsInitInfo i11LMLXs;
	lFETFeatureAlignment_i2LMsLXsInitInfo i2LMsLXs;
	lFETFeatureAlignment_i1LssInitInfo i1Lss;
}lFETFeatureAlignment_initmSelecterInfo;
			
extern void lFETOrientationSearchByFeatureAlignment(lFETOrientationSearchByFeatureAlignmentInfo in, int mode);
extern void lFETFeatureAlignmentSphereInit(lFETFeatureAlignmentSphereInfo* sph, int mode);
extern void lFETFeatureAlignmentSphereDevide(lFETFeatureAlignmentSphereInfo* sph);
extern void lFETFeatureAlignmentSphereDegenerate(lFETFeatureAlignmentSphereInfo* sph);
extern void lFETFeatureAlignmentSphereRandDisturb(lFETFeatureAlignmentSphereInfo* sph);
extern void lFETFeatureAlignmentSphereFeatureSet(lFETFeatureAlignmentInfo* info);
extern int lFETFeatureAlignmentSphereRefGenerate(lFETFeatureAlignmentInfo* in, lFETFeatureAlignmentImageInfo* out);
extern void lFETFeatureAlignmentInitSet_i2PCA(lFETFeatureAlignmentInfo* info);
extern void lFETFeatureAlignmentInitSet_i1L(lFETFeatureAlignmentInfo* info);
extern void lFETFeatureAlignmentInitSet_i1Ls(lFETFeatureAlignmentInfo* info, int target);
extern void lFETFeatureAlignmentInitPreSet_i1Lss(lFETFeatureAlignmentInfo* info, lFETFeatureAlignment_i1LssInitInfo* out, int target);
extern void lFETFeatureAlignmentInitSet_i1Lss(lFETFeatureAlignmentInfo* info, lFETFeatureAlignment_i1LssInitInfo* out, int mode);
extern void lFETFeatureAlignmentInitPreSet_i2LMsLXs(lFETFeatureAlignmentInfo* info, lFETFeatureAlignment_i2LMsLXsInitInfo* initInfo);
extern void lFETFeatureAlignmentInitSet_i2LMsLXs(lFETFeatureAlignmentInfo* info, lFETFeatureAlignment_i2LMsLXsInitInfo* initInfo, int targetM, int targetS);
extern void lFETFeatureAlignmentInitSet_i2LM(lFETFeatureAlignmentInfo* info);
extern void lFETFeatureAlignmentInitSet_i21LMLX(lFETFeatureAlignmentInfo* info);
extern void lFETFeatureAlignmentInitSet_random(lFETFeatureAlignmentInfo* info);
extern void lFETFeatureAlignmentInitSet_i2LXs(lFETFeatureAlignmentInfo* info, int target);
extern void lFETFeatureAlignmentInitPreSet_i11LMLXs(lFETFeatureAlignmentInfo* info, lFETFeatureAlignment_i11LMLXsInitInfo* out);
extern void lFETFeatureAlignmentInitSet_i11LMLXs(lFETFeatureAlignmentInfo* info, lFETFeatureAlignment_i11LMLXsInitInfo* initInfo, int target);
extern void lFETFAfeatureAdd(lFETFeatureAlignmentFeature* b, lFETFeatureAlignmentFeature* a);
extern void lFETFAfeaturecpy1(lFETFeatureAlignmentFeature* b, double* a);
extern double lFETFAcalcCoordDistance(lFETFeatureAlignmentCoord a, lFETFeatureAlignmentCoord b);
extern lFETFeatureAlignmentCoord lFETFAcalcCoordSum(lFETFeatureAlignmentCoord a, lFETFeatureAlignmentCoord b, lFETFeatureAlignmentCoord c, lFETFeatureAlignmentCoord d);
extern void lFATFAcoordcpy2(lFETFeatureAlignmentCoord* a, double* b, int mode);
extern void lFETFAcoordcpy1(lFETFeatureAlignmentCoord* b, double* a, int mode);
extern void lFETFAvectorProduct1(double* a, double* b, double* ans);
