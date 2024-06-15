#ifndef MRCIMAGE3DSYMMETRYFIND_H
#define MRCIMAGE3DSYMMETRYFIND_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImage3DSymmetryFindInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagAvg;
    char* Avg;
    FILE* fptAvg;
    
    long flagISGN;
    long ISGN;
    
    long flagRotMode;
    char* RotMode;
    
    long flagminRot1;
    float minRot1;
    
    long flagmaxRot1;
    float maxRot1;
    
    long flagdRot1;
    float dRot1;
    
    long flagminRot2;
    float minRot2;
    
    long flagmaxRot2;
    float maxRot2;
    
    long flagdRot2;
    float dRot2;
    
    long flagdCos;
    long dCos;
    
    long flagcorMode;
    long corMode;
    
    long flagOffsetMode;
    long OffsetMode;
    
    long flagInterpolationMode;
    long InterpolationMode;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImage3DSymmetryFindInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImage3DSymmetryFindInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImage3DSymmetryFindInfo* info);
extern void init1(mrcImage3DSymmetryFindInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGE3DSYMMETRYFIND_H */
