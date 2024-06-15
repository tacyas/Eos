#ifndef MRCIMAGEFTEST_H
#define MRCIMAGEFTEST_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageFTestInfo {
    long flagRedirect;

    long flagIn;
    char** In;
    char* InList;
    FILE** fptIn;
    FILE* fptInList;
    
    long flagRef;
    char** Ref;
    char* RefList;
    FILE** fptRef;
    FILE* fptRefList;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutF;
    char* OutF;
    FILE* fptOutF;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageFTestInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageFTestInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageFTestInfo* info);
extern void init1(mrcImageFTestInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEFTEST_H */
