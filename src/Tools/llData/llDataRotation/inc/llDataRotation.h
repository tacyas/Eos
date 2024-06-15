#ifndef LLDATAROTATION_H
#define LLDATAROTATION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct llDataRotationInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagphi;
    float phi;
    
    long flagz;
    float z;
    
    long flagPole;
    long Pole;
    
    long flagtruePitch;
    float truePitch;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} llDataRotationInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(llDataRotationInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(llDataRotationInfo* info);
extern void init1(llDataRotationInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* LLDATAROTATION_H */
