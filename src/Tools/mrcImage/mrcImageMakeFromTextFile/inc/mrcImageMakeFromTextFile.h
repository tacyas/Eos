#ifndef MRCIMAGEMAKEFROMTEXTFILE_H
#define MRCIMAGEMAKEFROMTEXTFILE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageMakeFromTextFileInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagnx;
    long nx;
    
    long flagny;
    long ny;
    
    long flagnz;
    long nz;
    
    long flagd;
    float d;
    
    long flagv;
    float v;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageMakeFromTextFileInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageMakeFromTextFileInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageMakeFromTextFileInfo* info);
extern void init1(mrcImageMakeFromTextFileInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEMAKEFROMTEXTFILE_H */
