#ifndef DCDDISTANCEATOMBETWEENATOM_H
#define DCDDISTANCEATOMBETWEENATOM_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct dcdDistanceAtomBetweenAtomInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} dcdDistanceAtomBetweenAtomInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(dcdDistanceAtomBetweenAtomInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(dcdDistanceAtomBetweenAtomInfo* info);
extern void init1(dcdDistanceAtomBetweenAtomInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* DCDDISTANCEATOMBETWEENATOM_H */
