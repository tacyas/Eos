#ifndef MRCIMAGEPATTERSONFUNCTIONCALC_H
#define MRCIMAGEPATTERSONFUNCTIONCALC_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImagePattersonFunctionCalcInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutPat;
    char* OutPat;
    FILE* fptOutPat;
    
    long flagOutGuinier;
    char* OutGuinier;
    FILE* fptOutGuinier;
    
    long flagOutGuinierPlot;
    char* OutGuinierPlot;
    FILE* fptOutGuinierPlot;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImagePattersonFunctionCalcInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImagePattersonFunctionCalcInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImagePattersonFunctionCalcInfo* info);
extern void init1(mrcImagePattersonFunctionCalcInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEPATTERSONFUNCTIONCALC_H */
