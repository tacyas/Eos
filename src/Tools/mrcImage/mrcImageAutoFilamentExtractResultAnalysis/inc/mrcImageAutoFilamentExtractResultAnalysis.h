#ifndef MRCIMAGEAUTOFILAMENTEXTRACTRESULTANALYSIS_H
#define MRCIMAGEAUTOFILAMENTEXTRACTRESULTANALYSIS_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageAutoFilamentExtractResultAnalysisInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagtruePitch;
    float truePitch;
    
    long flagPixelSize;
    float PixelSize;
    
    long flagdeltadY;
    float deltadY;
    
    long flagy;
    long y;
    
    long flagmag;
    float mag;
    
    long flagmode;
    long mode;
    
} mrcImageAutoFilamentExtractResultAnalysisInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageAutoFilamentExtractResultAnalysisInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageAutoFilamentExtractResultAnalysisInfo* info);
extern void init1(mrcImageAutoFilamentExtractResultAnalysisInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEAUTOFILAMENTEXTRACTRESULTANALYSIS_H */
