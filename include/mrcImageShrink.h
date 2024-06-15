#ifndef MRCIMAGESHRINK_H
#define MRCIMAGESHRINK_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageShrinkInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagS;
    float S;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageShrinkInfo;
extern void argCheck(mrcImageShrinkInfo* info, int argc, char* avgv[]);
extern void init0(mrcImageShrinkInfo* info);
extern void init1(mrcImageShrinkInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#endif /* MRCIMAGESHRINK_H */
