#ifndef MOI2MRC_H
#define MOI2MRC_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct moi2mrcInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagMag;
    float Mag;
    
    long flagMag2;
    float Mag2;
    
    long flagADUperE;
    float ADUperE;
    
    long flagInfo;
    long Info;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} moi2mrcInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(moi2mrcInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(moi2mrcInfo* info);
extern void init1(moi2mrcInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MOI2MRC_H */
