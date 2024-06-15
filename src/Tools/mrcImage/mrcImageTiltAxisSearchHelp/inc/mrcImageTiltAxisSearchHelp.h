#ifndef MRCIMAGETILTAXISSEARCHHELP_H
#define MRCIMAGETILTAXISSEARCHHELP_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageTiltAxisSearchHelpInfo {
    long flagRedirect;

    long flagInList;
    char** InList;
    char* InListList;
    FILE** fptInList;
    FILE* fptInListList;
    
    long flagOut1D;
    char* Out1D;
    FILE* fptOut1D;
    
    long flagOut1DEnlarged;
    char* Out1DEnlarged;
    FILE* fptOut1DEnlarged;
    
    long flagOut2D;
    char* Out2D;
    FILE* fptOut2D;
    
    long flagOriginX;
    float OriginX;
    
    long flagOriginY;
    float OriginY;
    
    long flagOriginZ;
    float OriginZ;
    
    long flagAxisAngleYaw;
    float AxisAngleYaw;
    
    long flagAxisAnglePitch;
    float AxisAnglePitch;
    
    long flagRmin;
    float Rmin;
    
    long flagRmax;
    float Rmax;
    
    long flagInterpolationMode;
    long InterpolationMode;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageTiltAxisSearchHelpInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageTiltAxisSearchHelpInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageTiltAxisSearchHelpInfo* info);
extern void init1(mrcImageTiltAxisSearchHelpInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGETILTAXISSEARCHHELP_H */
