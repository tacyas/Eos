#ifndef MRCIMAGESSINOGRAMCORRELATION_H
#define MRCIMAGESSINOGRAMCORRELATION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImagesSinogramCorrelationInfo {
    long flagRedirect;

    long flagIn;
    char** In;
    char* InList;
    FILE** fptIn;
    FILE* fptInList;
    
    long flagOutHeader;
    char* OutHeader;
    
    long flagRd;
    char* Rd;
    
    long flagNd;
    char* Nd;
    
    long flagD1d;
    char* D1d;
    
    long flagD2d;
    char* D2d;
    
    long flagLd;
    char* Ld;
    
    long flagCorrelationExtension;
    char* CorrelationExtension;
    
    long flagListExtension;
    char* ListExtension;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
    long flagNmode;
    long Nmode;
    
    long flagD1mode;
    long D1mode;
    
    long flagD2mode;
    long D2mode;
    
    long flagLmode;
    long Lmode;
    
    long flagLengthThresholdMode;
    long LengthThresholdMode;
    
    long flagLengthThresholdRatio;
    float LengthThresholdRatio;
    
    long flagCM;
    long CM;
    
} mrcImagesSinogramCorrelationInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImagesSinogramCorrelationInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImagesSinogramCorrelationInfo* info);
extern void init1(mrcImagesSinogramCorrelationInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGESSINOGRAMCORRELATION_H */
