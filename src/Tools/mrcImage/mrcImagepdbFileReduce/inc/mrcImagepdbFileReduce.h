#ifndef MRCIMAGEPDBFILEREDUCE_H
#define MRCIMAGEPDBFILEREDUCE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImagepdbFileReduceInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagPdb;
    char* Pdb;
    FILE* fptPdb;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagTh;
    float Th;
    
    long flagR;
    float R;
    
    long flagValue;
    float Value;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagITh;
    float ITh;
    
    long flagmode;
    long mode;
    
} mrcImagepdbFileReduceInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImagepdbFileReduceInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImagepdbFileReduceInfo* info);
extern void init1(mrcImagepdbFileReduceInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEPDBFILEREDUCE_H */
