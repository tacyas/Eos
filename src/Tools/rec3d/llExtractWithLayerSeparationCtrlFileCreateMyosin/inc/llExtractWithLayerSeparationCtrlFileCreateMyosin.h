#ifndef LLEXTRACTWITHLAYERSEPARATIONCTRLFILECREATEMYOSIN_H
#define LLEXTRACTWITHLAYERSEPARATIONCTRLFILECREATEMYOSIN_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct llExtractWithLayerSeparationCtrlFileCreateMyosinInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagY;
    float Y;
    
    long flagmode;
    long mode;
    
} llExtractWithLayerSeparationCtrlFileCreateMyosinInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(llExtractWithLayerSeparationCtrlFileCreateMyosinInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(llExtractWithLayerSeparationCtrlFileCreateMyosinInfo* info);
extern void init1(llExtractWithLayerSeparationCtrlFileCreateMyosinInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* LLEXTRACTWITHLAYERSEPARATIONCTRLFILECREATEMYOSIN_H */
