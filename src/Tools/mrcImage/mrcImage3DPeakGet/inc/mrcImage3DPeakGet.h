#ifndef MRCIMAGE3DPEAKGET_H
#define MRCIMAGE3DPEAKGET_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImage3DPeakGetInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagInfo;
    char* Info;
    FILE* fptInfo;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImage3DPeakGetInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImage3DPeakGetInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImage3DPeakGetInfo* info);
extern void init1(mrcImage3DPeakGetInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGE3DPEAKGET_H */
