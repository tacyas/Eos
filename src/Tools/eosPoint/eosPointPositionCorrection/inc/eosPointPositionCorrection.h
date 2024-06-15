#ifndef EOSPOINTPOSITIONCORRECTION_H
#define EOSPOINTPOSITIONCORRECTION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct eosPointPositionCorrectionInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagInType;
    long InType;
    
    long flagN;
    long N;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutType;
    long OutType;
    
    long flagOutDelta;
    char* OutDelta;
    FILE* fptOutDelta;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} eosPointPositionCorrectionInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(eosPointPositionCorrectionInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(eosPointPositionCorrectionInfo* info);
extern void init1(eosPointPositionCorrectionInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* EOSPOINTPOSITIONCORRECTION_H */
