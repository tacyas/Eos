#ifndef MRCIMAGEABNORMALVALUEREMOVE_H
#define MRCIMAGEABNORMALVALUEREMOVE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageAbnormalValueRemoveInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutParams;
    char* OutParams;
    FILE* fptOutParams;
    
    long flagcutValue;
    float cutValue;
    
    long flagUnsignedMax;
    float UnsignedMax;
    
    long flagUnsignedHalf;
    float UnsignedHalf;
    
    long flagThreshold;
    float Threshold;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagPattern;
    long Pattern;
    
    long flagmode;
    long mode;
    
} mrcImageAbnormalValueRemoveInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageAbnormalValueRemoveInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageAbnormalValueRemoveInfo* info);
extern void init1(mrcImageAbnormalValueRemoveInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEABNORMALVALUEREMOVE_H */
