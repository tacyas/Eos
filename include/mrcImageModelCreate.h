#ifndef MRCIMAGEMODELCREATE_H
#define MRCIMAGEMODELCREATE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageModelCreateInfo {
    long flagRedirect;

    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagnx;
    long nx;
    
    long flagny;
    long ny;
    
    long flagnz;
    long nz;
    
    long flagr;
    long r;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageModelCreateInfo;
extern void argCheck(mrcImageModelCreateInfo* info, int argc, char* avgv[]);
extern void init0(mrcImageModelCreateInfo* info);
extern void init1(mrcImageModelCreateInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#endif /* MRCIMAGEMODELCREATE_H */
