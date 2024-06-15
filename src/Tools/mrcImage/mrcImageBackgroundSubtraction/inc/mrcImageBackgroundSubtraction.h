#ifndef MRCIMAGEBACKGROUNDSUBTRACTION_H
#define MRCIMAGEBACKGROUNDSUBTRACTION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageBackgroundSubtractionInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagwidthX;
    float widthX;
    
    long flagwidthY;
    float widthY;
    
    long flagwidthZ;
    float widthZ;
    
    long flagedgeX;
    float edgeX;
    
    long flagedgeY;
    float edgeY;
    
    long flagedgeZ;
    float edgeZ;
    
    long flagTrim;
    float Trim;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageBackgroundSubtractionInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageBackgroundSubtractionInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageBackgroundSubtractionInfo* info);
extern void init1(mrcImageBackgroundSubtractionInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEBACKGROUNDSUBTRACTION_H */
