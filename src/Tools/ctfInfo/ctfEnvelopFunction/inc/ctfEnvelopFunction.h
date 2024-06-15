#ifndef CTFENVELOPFUNCTION_H
#define CTFENVELOPFUNCTION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct ctfEnvelopFunctionInfo {
    long flagRedirect;

    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagRmax;
    float Rmax;
    
    long flagdR;
    float dR;
    
    long flagkV;
    float kV;
    
    long flagCs;
    float Cs;
    
    long flagDefocus;
    float Defocus;
    
    long flagAoverP;
    float AoverP;
    
    long flagAin;
    float Ain;
    
    long flagctfMode;
    long ctfMode;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} ctfEnvelopFunctionInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(ctfEnvelopFunctionInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(ctfEnvelopFunctionInfo* info);
extern void init1(ctfEnvelopFunctionInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* CTFENVELOPFUNCTION_H */
