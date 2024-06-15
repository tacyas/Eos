#ifndef LLEXTRACTWITHLAYERSEPARATIONCTRLFILECREATE_H
#define LLEXTRACTWITHLAYERSEPARATIONCTRLFILECREATE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct llExtractWithLayerSeparationCtrlFileCreateInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagTurn;
    long Turn;
    
    long flagUnit;
    long Unit;
    
    long flagnHelix;
    long nHelix;
    
    long flagdY;
    long dY;
    
    long flagtruePitch;
    long truePitch;
    
    long flagrMax;
    float rMax;
    
    long flagRMax;
    float RMax;
    
    long flagRZMax;
    float RZMax;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} llExtractWithLayerSeparationCtrlFileCreateInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(llExtractWithLayerSeparationCtrlFileCreateInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(llExtractWithLayerSeparationCtrlFileCreateInfo* info);
extern void init1(llExtractWithLayerSeparationCtrlFileCreateInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* LLEXTRACTWITHLAYERSEPARATIONCTRLFILECREATE_H */
