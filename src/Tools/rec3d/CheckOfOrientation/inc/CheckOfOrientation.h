#ifndef CHECKOFORIENTATION_H
#define CHECKOFORIENTATION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct CheckOfOrientationInfo {
    long flagRedirect;

    long flagInList;
    char** InList;
    char* InListList;
    FILE** fptInList;
    FILE* fptInListList;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutV;
    char* OutV;
    FILE* fptOutV;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} CheckOfOrientationInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(CheckOfOrientationInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(CheckOfOrientationInfo* info);
extern void init1(CheckOfOrientationInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* CHECKOFORIENTATION_H */
