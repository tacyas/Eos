#ifndef MRCIMAGEPERIMETERCALC_H
#define MRCIMAGEPERIMETERCALC_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImagePerimeterCalcInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutArea;
    char* OutArea;
    FILE* fptOutArea;
    
    long flagOutChainCode;
    char* OutChainCode;
    FILE* fptOutChainCode;
    
    long flagOutLabel;
    char* OutLabel;
    FILE* fptOutLabel;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImagePerimeterCalcInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImagePerimeterCalcInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImagePerimeterCalcInfo* info);
extern void init1(mrcImagePerimeterCalcInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEPERIMETERCALC_H */
