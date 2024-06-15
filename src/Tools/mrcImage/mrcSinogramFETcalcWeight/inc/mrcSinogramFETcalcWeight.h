#ifndef MRCSINOGRAMFETCALCWEIGHT_H
#define MRCSINOGRAMFETCALCWEIGHT_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcSinogramFETcalcWeightInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagInC;
    char* InC;
    FILE* fptInC;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcSinogramFETcalcWeightInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcSinogramFETcalcWeightInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcSinogramFETcalcWeightInfo* info);
extern void init1(mrcSinogramFETcalcWeightInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCSINOGRAMFETCALCWEIGHT_H */
