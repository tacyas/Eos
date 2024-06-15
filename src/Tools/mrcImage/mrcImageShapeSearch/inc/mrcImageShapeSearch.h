#ifndef MRCIMAGESHAPESEARCH_H
#define MRCIMAGESHAPESEARCH_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageShapeSearchInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagShape;
    char* Shape;
    FILE* fptShape;
    
    long flagnCube;
    long nCube;
    
    long Refine;

    long flagminR;
    long minR;
    
    long flagmaxR;
    long maxR;
    
    long flagdelR;
    long delR;
    
    long flagminL;
    long minL;
    
    long flagmaxL;
    long maxL;
    
    long flagdelL;
    long delL;
    
    long flagminPhi;
    float minPhi;
    
    long flagmaxPhi;
    float maxPhi;
    
    long flagdelPhi;
    float delPhi;
    
    long flagminTheta;
    float minTheta;
    
    long flagmaxTheta;
    float maxTheta;
    
    long flagdelTheta;
    float delTheta;
    
    long flagminPsi;
    float minPsi;
    
    long flagmaxPsi;
    float maxPsi;
    
    long flagdelPsi;
    float delPsi;
    
    long flagthresZscore;
    float thresZscore;
    
    long flaginterpMode;
    long interpMode;
    
    long flagOVMode;
    long OVMode;
    
    long flagOutVectorBILD;
    char* OutVectorBILD;
    FILE* fptOutVectorBILD;
    
    long flagOutVector;
    char* OutVector;
    
    long flagArrowR1;
    float ArrowR1;
    
    long flagArrowR2;
    float ArrowR2;
    
    long flagArrowRho;
    float ArrowRho;
    
    long flagZoomVector;
    float ZoomVector;
    
    long flagArrowColorDisk0;
    float ArrowColorDisk0;
    
    long flagArrowColorDisk1;
    float ArrowColorDisk1;
    
    long flagArrowColorDisk2;
    float ArrowColorDisk2;
    
    long flagArrowColorSylinder0;
    float ArrowColorSylinder0;
    
    long flagArrowColorSylinder1;
    float ArrowColorSylinder1;
    
    long flagArrowColorSylinder2;
    float ArrowColorSylinder2;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageShapeSearchInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageShapeSearchInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageShapeSearchInfo* info);
extern void init1(mrcImageShapeSearchInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGESHAPESEARCH_H */
