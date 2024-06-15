#ifndef MRCIMAGENOISEREDUCTIONBYRELAXATION_H
#define MRCIMAGENOISEREDUCTIONBYRELAXATION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageNoiseReductionByRelaxationInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagNlab;
    long Nlab;
    
    long flagmax;
    long max;
    
    long flagmin;
    long min;
    
    long flagmode1;
    long mode1;
    
    long flagmode2;
    long mode2;
    
    long flagmode3;
    long mode3;
    
    long flagomode;
    long omode;
    
    long flagtimes;
    long times;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageNoiseReductionByRelaxationInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageNoiseReductionByRelaxationInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageNoiseReductionByRelaxationInfo* info);
extern void init1(mrcImageNoiseReductionByRelaxationInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGENOISEREDUCTIONBYRELAXATION_H */
