#ifndef MRC2GIF_H
#define MRC2GIF_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrc2gifInfo {
    long flagRedirect;

    long flaginFile;
    char* inFile;
    FILE* fptinFile;
    
    long flagoutFile;
    char* outFile;
    FILE* fptoutFile;
    
    long flagHigh;
    float High;
    
    long flagLow;
    float Low;
    
    long Inverse;

    long flagZ;
    long Z;
    
    long flagformat;
    char* format;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrc2gifInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrc2gifInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrc2gifInfo* info);
extern void init1(mrc2gifInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRC2GIF_H */
