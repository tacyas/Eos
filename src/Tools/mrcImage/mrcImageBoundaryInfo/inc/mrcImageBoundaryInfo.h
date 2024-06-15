#ifndef MRCIMAGEBOUNDARYINFO_H
#define MRCIMAGEBOUNDARYINFO_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageBoundaryInfoInfo {
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
    
} mrcImageBoundaryInfoInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageBoundaryInfoInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageBoundaryInfoInfo* info);
extern void init1(mrcImageBoundaryInfoInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEBOUNDARYINFO_H */
