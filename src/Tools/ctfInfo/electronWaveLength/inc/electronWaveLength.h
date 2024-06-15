#ifndef ELECTRONWAVELENGTH_H
#define ELECTRONWAVELENGTH_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct electronWaveLengthInfo {
    long flagRedirect;

    long flagkV;
    float kV;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} electronWaveLengthInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(electronWaveLengthInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(electronWaveLengthInfo* info);
extern void init1(electronWaveLengthInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* ELECTRONWAVELENGTH_H */