#ifndef CTFDETERMINATIONBYBAYES_H
#define CTFDETERMINATIONBYBAYES_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct ctfDeterminationByBayesInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagIn2;
    char* In2;
    FILE* fptIn2;
    
    long flagIn3;
    char* In3;
    FILE* fptIn3;
    
    long flagIn4;
    char** In4;
    char* In4List;
    FILE** fptIn4;
    FILE* fptIn4List;
    
    long flagnumDistribution;
    long numDistribution;
    
    long flagnumLikelihood;
    long numLikelihood;
    
    long flagrmax;
    float rmax;
    
    long flagrintermediate;
    float rintermediate;
    
    long flagrfirstpeak;
    float rfirstpeak;
    
    long flagrmin;
    float rmin;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
    long flagMTFmode;
    long MTFmode;
    
    long flagAinmode;
    long Ainmode;
    
    long flagIntensitymode;
    long Intensitymode;
    
} ctfDeterminationByBayesInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(ctfDeterminationByBayesInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(ctfDeterminationByBayesInfo* info);
extern void init1(ctfDeterminationByBayesInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* CTFDETERMINATIONBYBAYES_H */
