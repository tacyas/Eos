#ifndef COMMONLINESSEARCHBYVOTING_H
#define COMMONLINESSEARCHBYVOTING_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct commonLinesSearchByVotingInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagInC;
    char* InC;
    FILE* fptInC;
    
    long flagInCC;
    char* InCC;
    FILE* fptInCC;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutA;
    char* OutA;
    FILE* fptOutA;
    
    long flagOutDR;
    char* OutDR;
    FILE* fptOutDR;
    
    long flagOutDRA;
    char* OutDRA;
    FILE* fptOutDRA;
    
    long flagOutPH;
    char* OutPH;
    FILE* fptOutPH;
    
    long flagen;
    long en;
    
    long flagth;
    long th;
    
    long histgramCreateFlag;

    long extendVotingFlag;

    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} commonLinesSearchByVotingInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(commonLinesSearchByVotingInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(commonLinesSearchByVotingInfo* info);
extern void init1(commonLinesSearchByVotingInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* COMMONLINESSEARCHBYVOTING_H */
