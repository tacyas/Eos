#ifndef MRCIMAGESTREAMLINE_H
#define MRCIMAGESTREAMLINE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageStreamLineInfo {
    long flagRedirect;

    long flagIn2x;
    char* In2x;
    FILE* fptIn2x;
    
    long flagIn2y;
    char* In2y;
    FILE* fptIn2y;
    
    long flagIn3x;
    char* In3x;
    FILE* fptIn3x;
    
    long flagIn3y;
    char* In3y;
    FILE* fptIn3y;
    
    long flagIn3z;
    char* In3z;
    FILE* fptIn3z;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutPixel;
    char* OutPixel;
    FILE* fptOutPixel;
    
    long flagOutBILD;
    char* OutBILD;
    FILE* fptOutBILD;
    
    long flagNumFrame;
    long NumFrame;
    
    long flagdt;
    float dt;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageStreamLineInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageStreamLineInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageStreamLineInfo* info);
extern void init1(mrcImageStreamLineInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGESTREAMLINE_H */
