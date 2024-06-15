#ifndef EOSPOINTICP_H
#define EOSPOINTICP_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct eosPointICPInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagInType;
    long InType;
    
    long flagInMat;
    char* InMat;
    FILE* fptInMat;
    
    long flagRef;
    char* Ref;
    FILE* fptRef;
    
    long flagRefType;
    long RefType;
    
    long flagRefMat;
    char* RefMat;
    FILE* fptRefMat;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutType;
    long OutType;
    
    long flagEAMode;
    char* EAMode;
    
    long flagRatio;
    float Ratio;
    
    long flagIterationLimit;
    long IterationLimit;
    
    long flagPattern;
    long Pattern;
    
    long flagScoreThreshold;
    float ScoreThreshold;
    
    long flagOmit;
    float Omit;
    
    long flagPickup;
    float Pickup;
    
    long flagflag2D;
    long flag2D;
    
    long flagDebug;
    long Debug;
    
    long flagmode;
    long mode;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
} eosPointICPInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(eosPointICPInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(eosPointICPInfo* info);
extern void init1(eosPointICPInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* EOSPOINTICP_H */
