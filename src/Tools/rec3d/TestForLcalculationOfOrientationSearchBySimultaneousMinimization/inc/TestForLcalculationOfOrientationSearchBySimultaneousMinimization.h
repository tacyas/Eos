#ifndef TESTFORLCALCULATIONOFORIENTATIONSEARCHBYSIMULTANEOUSMINIMIZATION_H
#define TESTFORLCALCULATIONOFORIENTATIONSEARCHBYSIMULTANEOUSMINIMIZATION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct TestForLcalculationOfOrientationSearchBySimultaneousMinimizationInfo {
    long flagRedirect;

    long flagIn;
    char** In;
    char* InList;
    FILE** fptIn;
    FILE* fptInList;
    
    long flagiid;
    char* iid;
    FILE* fptiid;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
    long flagmode2;
    long mode2;
    
    long flagdtheta;
    long dtheta;
    
    long flagdpsi;
    long dpsi;
    
    long flagep;
    long ep;
    
    long flagmodeL;
    long modeL;
    
    long flagmodeTA;
    long modeTA;
    
    long flagLog;
    char* Log;
    FILE* fptLog;
    
    long flagLog2;
    char* Log2;
    FILE* fptLog2;
    
    long flagm2;
    char* m2;
    FILE* fptm2;
    
    long flagm3;
    char* m3;
    FILE* fptm3;
    
} TestForLcalculationOfOrientationSearchBySimultaneousMinimizationInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(TestForLcalculationOfOrientationSearchBySimultaneousMinimizationInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(TestForLcalculationOfOrientationSearchBySimultaneousMinimizationInfo* info);
extern void init1(TestForLcalculationOfOrientationSearchBySimultaneousMinimizationInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* TESTFORLCALCULATIONOFORIENTATIONSEARCHBYSIMULTANEOUSMINIMIZATION_H */
