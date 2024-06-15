#ifndef MRCIMAGESERIESINFOPERPIXEL_H
#define MRCIMAGESERIESINFOPERPIXEL_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageSeriesInfoPerPixelInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagX;
    float X;
    
    long flagY;
    float Y;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageSeriesInfoPerPixelInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageSeriesInfoPerPixelInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageSeriesInfoPerPixelInfo* info);
extern void init1(mrcImageSeriesInfoPerPixelInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGESERIESINFOPERPIXEL_H */
