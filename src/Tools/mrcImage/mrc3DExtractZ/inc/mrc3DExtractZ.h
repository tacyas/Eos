#ifndef MRC3DEXTRACTZ_H
#define MRC3DEXTRACTZ_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrc3DExtractZInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagZB;
    long ZB;
    
    long flagZT;
    long ZT;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrc3DExtractZInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrc3DExtractZInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrc3DExtractZInfo* info);
extern void init1(mrc3DExtractZInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRC3DEXTRACTZ_H */
