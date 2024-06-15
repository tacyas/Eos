#ifndef RAW2MRC_H
#define RAW2MRC_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct raw2mrcInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagNx;
    long Nx;
    
    long flagNy;
    long Ny;
    
    long flagNz;
    long Nz;
    
    long flagOffset;
    long Offset;
    
    long flagDataType;
    long DataType;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} raw2mrcInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(raw2mrcInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(raw2mrcInfo* info);
extern void init1(raw2mrcInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* RAW2MRC_H */
