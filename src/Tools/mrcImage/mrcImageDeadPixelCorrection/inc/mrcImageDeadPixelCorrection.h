#ifndef MRCIMAGEDEADPIXELCORRECTION_H
#define MRCIMAGEDEADPIXELCORRECTION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageDeadPixelCorrectionInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagDp;
    char* Dp;
    FILE* fptDp;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageDeadPixelCorrectionInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageDeadPixelCorrectionInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageDeadPixelCorrectionInfo* info);
extern void init1(mrcImageDeadPixelCorrectionInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEDEADPIXELCORRECTION_H */
