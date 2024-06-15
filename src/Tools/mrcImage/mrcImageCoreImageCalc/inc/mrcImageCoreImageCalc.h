#ifndef MRCIMAGECOREIMAGECALC_H
#define MRCIMAGECOREIMAGECALC_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageCoreImageCalcInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagEL;
    float EL;
    
    long flagBG;
    char** BG;
    char* BGList;
    FILE** fptBG;
    FILE* fptBGList;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutBG;
    char* OutBG;
    FILE* fptOutBG;
    
    long flagOutChi;
    char* OutChi;
    FILE* fptOutChi;
    
    long flagA1;
    float A1;
    
    long flagA2;
    float A2;
    
    long flagA3;
    float A3;
    
    long flagLimitA3Min;
    float LimitA3Min;
    
    long flagLimitA3Max;
    float LimitA3Max;
    
    long flagBaseEELS;
    float BaseEELS;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageCoreImageCalcInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageCoreImageCalcInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageCoreImageCalcInfo* info);
extern void init1(mrcImageCoreImageCalcInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGECOREIMAGECALC_H */
