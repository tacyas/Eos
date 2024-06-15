#ifndef MRCIMAGE1DSHIFTAVERAGEBYANNEALING_H
#define MRCIMAGE1DSHIFTAVERAGEBYANNEALING_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImage1dShiftAverageByAnnealingInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagSignal;
    char* Signal;
    FILE* fptSignal;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagrange;
    long range;
    
    long flagdelta;
    float delta;
    
    long flagtemperature;
    float temperature;
    
    long flagiter;
    long iter;
    
    long flageps;
    float eps;
    
    long flagtol;
    float tol;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
    long flagmode2;
    long mode2;
    
} mrcImage1dShiftAverageByAnnealingInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImage1dShiftAverageByAnnealingInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImage1dShiftAverageByAnnealingInfo* info);
extern void init1(mrcImage1dShiftAverageByAnnealingInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGE1DSHIFTAVERAGEBYANNEALING_H */
