#ifndef CRYSTALGETRECIPROCALLATTICE_H
#define CRYSTALGETRECIPROCALLATTICE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct crystalGetReciprocalLatticeInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagax;
    float ax;
    
    long flagay;
    float ay;
    
    long flagaz;
    float az;
    
    long flagbx;
    float bx;
    
    long flagby;
    float by;
    
    long flagbz;
    float bz;
    
    long flagcx;
    float cx;
    
    long flagcy;
    float cy;
    
    long flagcz;
    float cz;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} crystalGetReciprocalLatticeInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(crystalGetReciprocalLatticeInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(crystalGetReciprocalLatticeInfo* info);
extern void init1(crystalGetReciprocalLatticeInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* CRYSTALGETRECIPROCALLATTICE_H */
