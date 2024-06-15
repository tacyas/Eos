#ifndef MRCIMAGE1DSHIFTBYCORRELATION_H
#define MRCIMAGE1DSHIFTBYCORRELATION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImage1dShiftByCorrelationInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagRef;
    char* Ref;
    FILE* fptRef;
    
    long flagrange;
    long range;
    
    long flagSignal;
    char* Signal;
    FILE* fptSignal;
    
    long flagdelta;
    float delta;
    
    long normalize;

    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImage1dShiftByCorrelationInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImage1dShiftByCorrelationInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImage1dShiftByCorrelationInfo* info);
extern void init1(mrcImage1dShiftByCorrelationInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGE1DSHIFTBYCORRELATION_H */
