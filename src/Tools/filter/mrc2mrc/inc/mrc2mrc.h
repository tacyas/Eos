#ifndef MRC2MRC_H
#define MRC2MRC_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrc2mrcInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagInType;
    char* InType;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutType;
    char* OutType;
    
    long flagLenX;
    float LenX;
    
    long flagLenY;
    float LenY;
    
    long flagLenZ;
    float LenZ;
    
    long flagMx;
    long Mx;
    
    long flagMy;
    long My;
    
    long flagMz;
    long Mz;
    
    long flagStat;

    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrc2mrcInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrc2mrcInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrc2mrcInfo* info);
extern void init1(mrc2mrcInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRC2MRC_H */
