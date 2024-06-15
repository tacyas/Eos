#ifndef HF2000SPECIMENPOSITION_H
#define HF2000SPECIMENPOSITION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct hf2000SpecimenPositionInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagtty;
    char* tty;
    
    long flagSpeed;
    long Speed;
    
    long flagposX;
    float posX;
    
    long flagposY;
    float posY;
    
    long flagInteractive;
    long Interactive;
    
    long flagHost;
    char* Host;
    
    long flagPort;
    long Port;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} hf2000SpecimenPositionInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(hf2000SpecimenPositionInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(hf2000SpecimenPositionInfo* info);
extern void init1(hf2000SpecimenPositionInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* HF2000SPECIMENPOSITION_H */
