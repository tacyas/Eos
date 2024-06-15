#ifndef MRCIMAGEFILTERINGBYFILE_H
#define MRCIMAGEFILTERINGBYFILE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageFilteringbyFileInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagFilter;
    char* Filter;
    FILE* fptFilter;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageFilteringbyFileInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageFilteringbyFileInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageFilteringbyFileInfo* info);
extern void init1(mrcImageFilteringbyFileInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEFILTERINGBYFILE_H */
