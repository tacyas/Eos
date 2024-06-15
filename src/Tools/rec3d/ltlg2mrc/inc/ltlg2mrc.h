#ifndef LTLG2MRC_H
#define LTLG2MRC_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct ltlg2mrcInfo {
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
    
    long flagTitle;
    char* Title;
    
    long flagdelta;
    float delta;
    
    long flagRepeatDistance;
    float RepeatDistance;
    
    long flagrMax;
    float rMax;
    
    long flagphiStart;
    float phiStart;
    
    long flagzMin;
    float zMin;
    
    long flagzMax;
    float zMax;
    
    long flagdeltaz;
    float deltaz;
    
    long flagWeightOf0thLayer;
    float WeightOf0thLayer;
    
    long flagLayer;
    char* Layer;
    FILE* fptLayer;
    
    long f99;

    long flagCUT;
    float CUT;
    
    long flagMean;
    float Mean;
    
    long flagSigma;
    float Sigma;
    
    long Inverse;

    long notInteractive;

    long AntiPole;

    long flagmode;
    long mode;
    
} ltlg2mrcInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(ltlg2mrcInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(ltlg2mrcInfo* info);
extern void init1(ltlg2mrcInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* LTLG2MRC_H */
