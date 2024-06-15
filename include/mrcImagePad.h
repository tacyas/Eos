#ifndef MRCIMAGEPAD_H
#define MRCIMAGEPAD_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImagePadInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagWidth;
    long Width;
    
    long flagHeight;
    long Height;
    
    long flagValue;
    float Value;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImagePadInfo;
extern void argCheck(mrcImagePadInfo* info, int argc, char* avgv[]);
extern void init0(mrcImagePadInfo* info);
extern void init1(mrcImagePadInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#endif /* MRCIMAGEPAD_H */
