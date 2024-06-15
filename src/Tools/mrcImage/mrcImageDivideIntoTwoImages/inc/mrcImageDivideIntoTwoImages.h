#ifndef MRCIMAGEDIVIDEINTOTWOIMAGES_H
#define MRCIMAGEDIVIDEINTOTWOIMAGES_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageDivideIntoTwoImagesInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut1;
    char* Out1;
    FILE* fptOut1;
    
    long flagOut2;
    char* Out2;
    FILE* fptOut2;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageDivideIntoTwoImagesInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageDivideIntoTwoImagesInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageDivideIntoTwoImagesInfo* info);
extern void init1(mrcImageDivideIntoTwoImagesInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEDIVIDEINTOTWOIMAGES_H */
