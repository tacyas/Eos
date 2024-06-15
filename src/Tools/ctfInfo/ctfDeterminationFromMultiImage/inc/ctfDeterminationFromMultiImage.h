#ifndef CTFDETERMINATIONFROMMULTIIMAGE_H
#define CTFDETERMINATIONFROMMULTIIMAGE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct ctfDeterminationFromMultiImageInfo {
    long flagRedirect;

    long flagIn;
    char** In;
    char* InList;
    FILE** fptIn;
    FILE* fptInList;
    
    long flagIn2;
    char** In2;
    char* In2List;
    FILE** fptIn2;
    FILE* fptIn2List;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOut2;
    char* Out2;
    
    long flagMolecEnv;
    float MolecEnv;
    
    long flagMolecEnvFile;
    char* MolecEnvFile;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} ctfDeterminationFromMultiImageInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(ctfDeterminationFromMultiImageInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(ctfDeterminationFromMultiImageInfo* info);
extern void init1(ctfDeterminationFromMultiImageInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* CTFDETERMINATIONFROMMULTIIMAGE_H */
