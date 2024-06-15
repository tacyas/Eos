#ifndef CTFDETERMINE_H
#define CTFDETERMINE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct ctfDetermineInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagDefocus;
    float Defocus;
    
    long flagCs;
    float Cs;
    
    long flagCc;
    float Cc;
    
    long flagdE;
    float dE;
    
    long flagAc;
    float Ac;
    
    long flagCutLow;
    float CutLow;
    
    long flagCutHigh;
    float CutHigh;
    
    long flagI0;
    float I0;
    
    long flagratioOfAmpToPhase;
    float ratioOfAmpToPhase;
    
    long flagAi;
    float Ai;
    
    long flagBofMTF;
    float BofMTF;
    
    long flagBofVibration;
    float BofVibration;
    
    long flagMagnification;
    float Magnification;
    
    long flagWhiteNoise;
    float WhiteNoise;
    
    long flagWhiteNoise2;
    float WhiteNoise2;
    
    long flagMolcEnv;
    float MolcEnv;
    
    long flagMolcEnvTable;
    char* MolcEnvTable;
    FILE* fptMolcEnvTable;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
    long flagmin;
    float min;
    
    long flagmax;
    float max;
    
    long flagstep;
    float step;
    
    long flagdegree;
    long degree;
    
    long flagsection;
    long section;
    
} ctfDetermineInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(ctfDetermineInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(ctfDetermineInfo* info);
extern void init1(ctfDetermineInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* CTFDETERMINE_H */
