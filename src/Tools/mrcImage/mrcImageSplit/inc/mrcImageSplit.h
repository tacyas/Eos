#ifndef MRCIMAGESPLIT_H
#define MRCIMAGESPLIT_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageSplitInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    
    long flagSuffix;
    char* Suffix;
    
    long flagHeight;
    long Height;
    
    long flagWidth;
    long Width;
    
    long flagSection;
    long Section;
    
    long flagHeightA;
    long HeightA;
    
    long flagWidthA;
    long WidthA;
    
    long flagSectionA;
    long SectionA;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageSplitInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageSplitInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageSplitInfo* info);
extern void init1(mrcImageSplitInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGESPLIT_H */
