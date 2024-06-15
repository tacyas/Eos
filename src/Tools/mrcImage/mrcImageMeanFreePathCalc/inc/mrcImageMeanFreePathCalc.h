#ifndef MRCIMAGEMEANFREEPATHCALC_H
#define MRCIMAGEMEANFREEPATHCALC_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageMeanFreePathCalcInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutWhiteAll;
    char* OutWhiteAll;
    FILE* fptOutWhiteAll;
    
    long flagOutWhite;
    char* OutWhite;
    FILE* fptOutWhite;
    
    long flagOutBlackAll;
    char* OutBlackAll;
    FILE* fptOutBlackAll;
    
    long flagOutBlack;
    char* OutBlack;
    FILE* fptOutBlack;
    
    long flagOutWhiteEdge;
    char* OutWhiteEdge;
    FILE* fptOutWhiteEdge;
    
    long flagOutBlackEdge;
    char* OutBlackEdge;
    FILE* fptOutBlackEdge;
    
    long flagDirection;
    char* Direction;
    
    long flagLineThicknessX;
    float LineThicknessX;
    
    long flagLineThicknessY;
    float LineThicknessY;
    
    long flagLineMode;
    long LineMode;
    
    long flagLineShape;
    long LineShape;
    
    long flagdeltaPhi;
    float deltaPhi;
    
    long flagdeltaTheta;
    float deltaTheta;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageMeanFreePathCalcInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageMeanFreePathCalcInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageMeanFreePathCalcInfo* info);
extern void init1(mrcImageMeanFreePathCalcInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEMEANFREEPATHCALC_H */
