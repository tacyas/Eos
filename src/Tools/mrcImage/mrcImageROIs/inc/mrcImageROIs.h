#ifndef MRCIMAGEROIS_H
#define MRCIMAGEROIS_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageROIsInfo {
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
    
    long flagShrink;
    long Shrink;
    
    long flagWidth;
    float Width;
    
    long flagHeight;
    float Height;
    
    long NonPeriodic;

    long flagPadMode;
    long PadMode;
    
    long flagMode;
    long Mode;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageROIsInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageROIsInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageROIsInfo* info);
extern void init1(mrcImageROIsInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEROIS_H */
