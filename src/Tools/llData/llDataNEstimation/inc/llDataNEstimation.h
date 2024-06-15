#ifndef LLDATANESTIMATION_H
#define LLDATANESTIMATION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct llDataNEstimationInfo {
    long flagRedirect;

    long flagr;
    float r;
    
    long flagR;
    float R;
    
    long flagxstep;
    float xstep;
    
    long flagWidth;
    float Width;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} llDataNEstimationInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(llDataNEstimationInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(llDataNEstimationInfo* info);
extern void init1(llDataNEstimationInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* LLDATANESTIMATION_H */
