#ifndef MRCIMAGETWOIMAGETEST_H
#define MRCIMAGETWOIMAGETEST_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageTwoImageTestInfo {
    long flagRedirect;

    long flagIn1;
    char** In1;
    char* In1List;
    FILE** fptIn1;
    FILE* fptIn1List;
    
    long flagIn2;
    char** In2;
    char* In2List;
    FILE** fptIn2;
    FILE* fptIn2List;
    
    long flagtTest;
    char* tTest;
    FILE* fpttTest;
    
    long flagFTest;
    char* FTest;
    FILE* fptFTest;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageTwoImageTestInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageTwoImageTestInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageTwoImageTestInfo* info);
extern void init1(mrcImageTwoImageTestInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGETWOIMAGETEST_H */
