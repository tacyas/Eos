#ifndef LLDATASEPARATE_H
#define LLDATASEPARATE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct llDataSeparateInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagSepNea;
    char* SepNea;
    FILE* fptSepNea;
    
    long flagSepFar;
    char* SepFar;
    FILE* fptSepFar;
    
    long flagMixNea;
    char* MixNea;
    FILE* fptMixNea;
    
    long flagMixFar;
    char* MixFar;
    FILE* fptMixFar;
    
    long flagdelRInv;
    float delRInv;
    
    long flagtruePitch;
    float truePitch;
    
    long flagrMax;
    float rMax;
    
    long flagRMax;
    float RMax;
    
    long flagxShift;
    float xShift;
    
    long flagLog;
    char* Log;
    FILE* fptLog;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} llDataSeparateInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(llDataSeparateInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(llDataSeparateInfo* info);
extern void init1(llDataSeparateInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* LLDATASEPARATE_H */
