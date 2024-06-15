#ifndef MRCIMAGEUNBENTROI_H
#define MRCIMAGEUNBENTROI_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageUnbentROIInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagroiLine;
    float* roiLine;
    
    long flagx;
    float x;
    
    long flagy;
    float y;
    
    long flagWidth;
    float Width;
    
    long flagHeight;
    float Height;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageUnbentROIInfo;
extern void argCheck(mrcImageUnbentROIInfo* info, int argc, char* avgv[]);
extern void init0(mrcImageUnbentROIInfo* info);
extern void init1(mrcImageUnbentROIInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#endif /* MRCIMAGEUNBENTROI_H */
