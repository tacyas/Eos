#ifndef MRC2DTO3DFORVARIATION_H
#define MRC2DTO3DFORVARIATION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrc2Dto3DforVariationInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrc2Dto3DforVariationInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrc2Dto3DforVariationInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrc2Dto3DforVariationInfo* info);
extern void init1(mrc2Dto3DforVariationInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRC2DTO3DFORVARIATION_H */
