#ifndef TILTINFODETERMINE_H
#define TILTINFODETERMINE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct tiltInfoDetermineInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagdefocus;
    char* defocus;
    FILE* fptdefocus;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
    long flagmag;
    float mag;
    
} tiltInfoDetermineInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(tiltInfoDetermineInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(tiltInfoDetermineInfo* info);
extern void init1(tiltInfoDetermineInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* TILTINFODETERMINE_H */
