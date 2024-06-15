#ifndef MRCIMAGEHEADERCHANGE_H
#define MRCIMAGEHEADERCHANGE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageHeaderChangeInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagr;
    float r;
    
    long flagLx;
    float Lx;
    
    long flagLy;
    float Ly;
    
    long flagLz;
    float Lz;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageHeaderChangeInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageHeaderChangeInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageHeaderChangeInfo* info);
extern void init1(mrcImageHeaderChangeInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEHEADERCHANGE_H */
