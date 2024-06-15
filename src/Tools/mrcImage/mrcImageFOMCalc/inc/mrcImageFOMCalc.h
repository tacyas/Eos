#ifndef MRCIMAGEFOMCALC_H
#define MRCIMAGEFOMCALC_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageFOMCalcInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagWeight;
    float Weight;
    
    long flagInList;
    char** InList;
    char* InListList;
    FILE** fptInList;
    FILE* fptInListList;
    
    long flagRef;
    char* Ref;
    FILE* fptRef;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagRmin;
    float Rmin;
    
    long flagRmax;
    float Rmax;
    
    long flagdR;
    float dR;
    
    long flagnSector;
    long nSector;
    
    long flagdAlpha;
    float dAlpha;
    
    long flagXMax;
    float XMax;
    
    long AutoScale;

    long flagAASRMax;
    float AASRMax;
    
    long RScale;

    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageFOMCalcInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageFOMCalcInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageFOMCalcInfo* info);
extern void init1(mrcImageFOMCalcInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEFOMCALC_H */
