#ifndef MRC2FLD_H
#define MRC2FLD_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrc2fldInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagshiftx;
    float shiftx;
    
    long flagshifty;
    float shifty;
    
    long flagshiftz;
    float shiftz;
    
    long I;

    long RadiusCylindrical;

    long flagMag;
    float Mag;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrc2fldInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrc2fldInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrc2fldInfo* info);
extern void init1(mrc2fldInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRC2FLD_H */
