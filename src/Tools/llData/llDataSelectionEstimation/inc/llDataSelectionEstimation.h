#ifndef LLDATASELECTIONESTIMATION_H
#define LLDATASELECTIONESTIMATION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct llDataSelectionEstimationInfo {
    long flagRedirect;

    long flagN1;
    float N1;
    
    long flagL1;
    float L1;
    
    long flagN2;
    float N2;
    
    long flagL2;
    float L2;
    
    long flagtmax;
    float tmax;
    
    long flagumax;
    float umax;
    
    long flagr;
    float r;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} llDataSelectionEstimationInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(llDataSelectionEstimationInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(llDataSelectionEstimationInfo* info);
extern void init1(llDataSelectionEstimationInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* LLDATASELECTIONESTIMATION_H */
