#ifndef MRCIMAGEHOLEFILLING_H
#define MRCIMAGEHOLEFILLING_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageHoleFillingInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagNeighbor;
    long Neighbor;
    
    long flagBlackArea;
    char* BlackArea;
    FILE* fptBlackArea;
    
    long flagBlackLabel;
    char* BlackLabel;
    FILE* fptBlackLabel;
    
    long flagBlack;
    char* Black;
    FILE* fptBlack;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageHoleFillingInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageHoleFillingInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageHoleFillingInfo* info);
extern void init1(mrcImageHoleFillingInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEHOLEFILLING_H */
