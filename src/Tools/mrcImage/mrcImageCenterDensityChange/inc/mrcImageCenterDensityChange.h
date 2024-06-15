#ifndef MRCIMAGECENTERDENSITYCHANGE_H
#define MRCIMAGECENTERDENSITYCHANGE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageCenterDensityChangeInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagrmin;
    float rmin;
    
    long flagrmax;
    float rmax;
    
    long flagratio;
    float ratio;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
    long flagradiusMode;
    long radiusMode;
    
} mrcImageCenterDensityChangeInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageCenterDensityChangeInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageCenterDensityChangeInfo* info);
extern void init1(mrcImageCenterDensityChangeInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGECENTERDENSITYCHANGE_H */
