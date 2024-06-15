#ifndef ENERGYTRANSFERMODELRESULTCHECK_H
#define ENERGYTRANSFERMODELRESULTCHECK_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct energyTransferModelResultCheckInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagInResHead;
    char* InResHead;
    
    long flagInResTail;
    long InResTail;
    
    long flagNeg;
    float Neg;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} energyTransferModelResultCheckInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(energyTransferModelResultCheckInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(energyTransferModelResultCheckInfo* info);
extern void init1(energyTransferModelResultCheckInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* ENERGYTRANSFERMODELRESULTCHECK_H */
