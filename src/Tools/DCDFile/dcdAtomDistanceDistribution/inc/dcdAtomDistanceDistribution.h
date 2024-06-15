#ifndef DCDATOMDISTANCEDISTRIBUTION_H
#define DCDATOMDISTANCEDISTRIBUTION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct dcdAtomDistanceDistributionInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutMRC;
    char* OutMRC;
    FILE* fptOutMRC;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} dcdAtomDistanceDistributionInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(dcdAtomDistanceDistributionInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(dcdAtomDistanceDistributionInfo* info);
extern void init1(dcdAtomDistanceDistributionInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* DCDATOMDISTANCEDISTRIBUTION_H */
