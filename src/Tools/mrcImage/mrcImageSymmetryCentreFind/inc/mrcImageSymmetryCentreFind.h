#ifndef MRCIMAGESYMMETRYCENTREFIND_H
#define MRCIMAGESYMMETRYCENTREFIND_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageSymmetryCentreFindInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOut2;
    char* Out2;
    FILE* fptOut2;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageSymmetryCentreFindInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageSymmetryCentreFindInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageSymmetryCentreFindInfo* info);
extern void init1(mrcImageSymmetryCentreFindInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGESYMMETRYCENTREFIND_H */
