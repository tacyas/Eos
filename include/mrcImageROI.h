#ifndef MRCIMAGEROI_H
#define MRCIMAGEROI_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageROIInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagblx;
    float blx;
    
    long flagbly;
    float bly;
    
    long flagbrx;
    float brx;
    
    long flagbry;
    float bry;
    
    long flagtrx;
    float trx;
    
    long flagtry;
    float try;
    
    long flagtlx;
    float tlx;
    
    long flagtly;
    float tly;
    
    long flagWidthBeforeExpansion;
    float WidthBeforeExpansion;
    
    long flagHeightBeforeExpansion;
    float HeightBeforeExpansion;
    
    long flagAngle;
    float Angle;
    
    long flagWidthAfterExpansion;
    float WidthAfterExpansion;
    
    long flagHeightAfterExpansion;
    float HeightAfterExpansion;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageROIInfo;
extern void argCheck(mrcImageROIInfo* info, int argc, char* avgv[]);
extern void init0(mrcImageROIInfo* info);
extern void init1(mrcImageROIInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#endif /* MRCIMAGEROI_H */
