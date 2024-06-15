#ifndef MRCSINOGRAMFETREFERREDCORRELATION_H
#define MRCSINOGRAMFETREFERREDCORRELATION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcSinogramFETreferredCorrelationInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagInR;
    char* InR;
    FILE* fptInR;
    
    long flagInE;
    char* InE;
    FILE* fptInE;
    
    long flagNM;
    long NM;
    
    long flagOM;
    long OM;
    
    long flagTN;
    long TN;
    
    long flagRR;
    long RR;
    
    long flagWEIGHT;
    char* WEIGHT;
    FILE* fptWEIGHT;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcSinogramFETreferredCorrelationInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcSinogramFETreferredCorrelationInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcSinogramFETreferredCorrelationInfo* info);
extern void init1(mrcSinogramFETreferredCorrelationInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCSINOGRAMFETREFERREDCORRELATION_H */
