#ifndef CTFMULTIFUNCTION_H
#define CTFMULTIFUNCTION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct ctfMultiFunctionInfo {
    long flagRedirect;

    long flagIn;
    char** In;
    char* InList;
    FILE** fptIn;
    FILE* fptInList;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagRmax;
    float Rmax;
    
    long flagdR;
    float dR;
    
    long flagAin;
    float Ain;
    
    long flagctfMode;
    long ctfMode;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} ctfMultiFunctionInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(ctfMultiFunctionInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(ctfMultiFunctionInfo* info);
extern void init1(ctfMultiFunctionInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* CTFMULTIFUNCTION_H */
