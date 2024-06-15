#ifndef MRCREFCORESTIMATE_H
#define MRCREFCORESTIMATE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcRefCorEstimateInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcRefCorEstimateInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcRefCorEstimateInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcRefCorEstimateInfo* info);
extern void init1(mrcRefCorEstimateInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCREFCORESTIMATE_H */
