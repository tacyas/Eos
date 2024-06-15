#ifndef TIFF2MRC_H
#define TIFF2MRC_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct tiff2mrcInfo {
    long flagRedirect;

    long flaginFile;
    char* inFile;
    FILE* fptinFile;
    
    long flagoutFile;
    char* outFile;
    FILE* fptoutFile;
    
    long flagResolution;
    float Resolution;
    
    long flagResolutionX;
    float ResolutionX;
    
    long flagResolutionY;
    float ResolutionY;
    
    long flagResolutionZ;
    float ResolutionZ;
    
    long flagtime;
    float time;
    
    long flagdirnum;
    long dirnum;
    
    long Inverse;

    long Signed;

    long flagOffset;
    float Offset;
    
    long flagMax;
    float Max;
    
    long flagMin;
    float Min;
    
    long flagrealMin;
    float realMin;
    
    long flagrealMax;
    float realMax;
    
    long flagrealMaxBit;
    float realMaxBit;
    
    long flagsinFile;
    char* sinFile;
    FILE* fptsinFile;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagShrink;
    long Shrink;
    
    long flagMode;
    long Mode;
    
    long flagmode;
    long mode;
    
} tiff2mrcInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(tiff2mrcInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(tiff2mrcInfo* info);
extern void init1(tiff2mrcInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* TIFF2MRC_H */
