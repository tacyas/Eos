#ifndef LLDATARESCALING_H
#define LLDATARESCALING_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct llDataRescalingInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagrScale;
    float rScale;
    
    long flagdelBR;
    float delBR;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} llDataRescalingInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(llDataRescalingInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(llDataRescalingInfo* info);
extern void init1(llDataRescalingInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* LLDATARESCALING_H */
