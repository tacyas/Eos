#ifndef CTFFUNCTION_H
#define CTFFUNCTION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct ctfFunctionInfo {
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
    
    long flagpvm;
    long pvm;
    
    long flagpvmList;
    char* pvmList;
    FILE* fptpvmList;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} ctfFunctionInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(ctfFunctionInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(ctfFunctionInfo* info);
extern void init1(ctfFunctionInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* CTFFUNCTION_H */
