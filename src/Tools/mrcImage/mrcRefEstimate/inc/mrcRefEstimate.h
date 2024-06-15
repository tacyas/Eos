#ifndef MRCREFESTIMATE_H
#define MRCREFESTIMATE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcRefEstimateInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
} mrcRefEstimateInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcRefEstimateInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcRefEstimateInfo* info);
extern void init1(mrcRefEstimateInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCREFESTIMATE_H */
