#ifndef IMAGESVIEW_H
#define IMAGESVIEW_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct imagesViewInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    
    long flagOut;
    char* Out;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} imagesViewInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(imagesViewInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(imagesViewInfo* info);
extern void init1(imagesViewInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* IMAGESVIEW_H */
