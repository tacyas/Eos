#ifndef MRCSINOGRAMFET_H
#define MRCSINOGRAMFET_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcSinogramFETInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutC;
    char* OutC;
    FILE* fptOutC;
    
    long flagsm;
    long sm;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcSinogramFETInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcSinogramFETInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcSinogramFETInfo* info);
extern void init1(mrcSinogramFETInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCSINOGRAMFET_H */
