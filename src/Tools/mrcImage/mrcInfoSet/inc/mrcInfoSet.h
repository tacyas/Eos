#ifndef MRCINFOSET_H
#define MRCINFOSET_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcInfoSetInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagLengthx;
    float Lengthx;
    
    long flagLengthy;
    float Lengthy;
    
    long flagLengthz;
    float Lengthz;
    
    long Fixed;

    long Interactive;

    long flagmode;
    long mode;
    
} mrcInfoSetInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcInfoSetInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcInfoSetInfo* info);
extern void init1(mrcInfoSetInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCINFOSET_H */
