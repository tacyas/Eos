#ifndef MRC2TIFF_H
#define MRC2TIFF_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrc2tiffInfo {
    long flagRedirect;

    long flaginFile;
    char* inFile;
    FILE* fptinFile;
    
    long flagoutFile;
    char* outFile;
    FILE* fptoutFile;
    
    long flagHigh;
    float High;
    
    long flagLow;
    float Low;
    
    long Inverse;

    long raw;

    long flagOffset;
    float Offset;
    
    long flagZ;
    long Z;
    
    long flagResolution;
    float Resolution;
    
    long flagResolutionX;
    float ResolutionX;
    
    long flagResolutionY;
    float ResolutionY;
    
    long flagResolutionZ;
    float ResolutionZ;
    
    long flagformat;
    char* format;
    
    long flagcolorMode;
    long colorMode;
    
    long flagcolorRangeMin;
    float colorRangeMin;
    
    long flagcolorRangeMax;
    float colorRangeMax;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagMode;
    long Mode;
    
    long flagmode;
    long mode;
    
} mrc2tiffInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrc2tiffInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrc2tiffInfo* info);
extern void init1(mrc2tiffInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRC2TIFF_H */
