#ifndef MRCFFTCTFCOMPENSATION_H
#define MRCFFTCTFCOMPENSATION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcFFTCTFCompensationInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagCTFIn;
    char* CTFIn;
    FILE* fptCTFIn;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcFFTCTFCompensationInfo;
extern void argCheck(mrcFFTCTFCompensationInfo* info, int argc, char* avgv[]);
extern void init0(mrcFFTCTFCompensationInfo* info);
extern void init1(mrcFFTCTFCompensationInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#endif /* MRCFFTCTFCOMPENSATION_H */
