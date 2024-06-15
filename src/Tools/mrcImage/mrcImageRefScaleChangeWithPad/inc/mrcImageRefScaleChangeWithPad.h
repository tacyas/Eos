#ifndef MRCIMAGEREFSCALECHANGEWITHPAD_H
#define MRCIMAGEREFSCALECHANGEWITHPAD_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageRefScaleChangeWithPadInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagRef;
    char* Ref;
    FILE* fptRef;
    
    long flagwidth;
    float width;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageRefScaleChangeWithPadInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageRefScaleChangeWithPadInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageRefScaleChangeWithPadInfo* info);
extern void init1(mrcImageRefScaleChangeWithPadInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEREFSCALECHANGEWITHPAD_H */
