#ifndef STEREODISPLAY_H
#define STEREODISPLAY_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct StereoDisplayInfo {
    long flagRedirect;

    long flagInl;
    char* Inl;
    FILE* fptInl;
    
    long flagInr;
    char* Inr;
    FILE* fptInr;
    
    long flagIn;
    char** In;
    char* InList;
    FILE** fptIn;
    FILE* fptInList;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} StereoDisplayInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(StereoDisplayInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(StereoDisplayInfo* info);
extern void init1(StereoDisplayInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* STEREODISPLAY_H */
