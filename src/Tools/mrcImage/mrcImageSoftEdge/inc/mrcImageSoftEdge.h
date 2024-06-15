#ifndef MRCIMAGESOFTEDGE_H
#define MRCIMAGESOFTEDGE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageSoftEdgeInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagwidth;
    float width;
    
    long flagenvelop;
    long envelop;
    
    long flagmode;
    long mode;
    
} mrcImageSoftEdgeInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageSoftEdgeInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageSoftEdgeInfo* info);
extern void init1(mrcImageSoftEdgeInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGESOFTEDGE_H */
