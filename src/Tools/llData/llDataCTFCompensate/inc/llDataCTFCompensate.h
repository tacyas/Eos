#ifndef LLDATACTFCOMPENSATE_H
#define LLDATACTFCOMPENSATE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct llDataCTFCompensateInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagIn1;
    char* In1;
    FILE* fptIn1;
    
    long flagIn2;
    char* In2;
    FILE* fptIn2;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagtruePitch;
    float truePitch;
    
    long flagmode;
    long mode;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
} llDataCTFCompensateInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(llDataCTFCompensateInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(llDataCTFCompensateInfo* info);
extern void init1(llDataCTFCompensateInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* LLDATACTFCOMPENSATE_H */
