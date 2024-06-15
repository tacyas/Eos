#ifndef MRCIMAGECORRELATIONWITHCTFCOMPENSATION_H
#define MRCIMAGECORRELATIONWITHCTFCOMPENSATION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageCorrelationWithCTFCompensationInfo {
    long flagRedirect;

    long flagIn;
    char** In;
    char* InList;
    FILE** fptIn;
    FILE* fptInList;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagSinWinRmin;
    float SinWinRmin;
    
    long flagSinWinRmax;
    float SinWinRmax;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageCorrelationWithCTFCompensationInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageCorrelationWithCTFCompensationInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageCorrelationWithCTFCompensationInfo* info);
extern void init1(mrcImageCorrelationWithCTFCompensationInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGECORRELATIONWITHCTFCOMPENSATION_H */
